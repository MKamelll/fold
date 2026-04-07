#include "mainwindow.hpp"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <podofo/podofo.h>
#include <QThread>
#include <QApplication>

SplitPage::SplitPage(QWidget *parent) : QWidget(parent) {
    addFilesBtn = new QPushButton("Add", this);
    removeFilesBtn = new QPushButton("Del", this);
    doSplitBtn = new QPushButton("Split", this);
    doSplitBtn->setDisabled(true);
    backToHomeBtn = new QPushButton("Home", this);
    fileList = new QListWidget(this);
    layout = new QVBoxLayout(this);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(doSplitBtn);
    hbox->addStretch(1);
    hbox->addWidget(backToHomeBtn);
    hbox->addWidget(addFilesBtn);
    hbox->addWidget(removeFilesBtn);

    connect(fileList->model(), &QAbstractItemModel::rowsInserted,
            [=]() { doSplitBtn->setEnabled(fileList->count() > 0); });

    connect(fileList->model(), &QAbstractItemModel::rowsRemoved,
            [=]() { doSplitBtn->setEnabled(fileList->count() > 0); });

    setLayout(layout);

    layout->addWidget(fileList);
    layout->addLayout(hbox);

    connect(addFilesBtn, &QPushButton::clicked, this, [=]() {
        QStringList files = QFileDialog::getOpenFileNames(
            this, "Select Files", QDir::homePath(), "PDF Files (*.pdf)");

        for (auto &file : files) {
            fileList->addItem(file);
        }
        fileList->setDragDropMode(QAbstractItemView::InternalMove);
        fileList->setDefaultDropAction(Qt::MoveAction);
    });

    connect(removeFilesBtn, &QPushButton::clicked, this,
            [=]() { delete fileList->takeItem(fileList->currentRow()); });

    connect(backToHomeBtn, &QPushButton::clicked, this, [=]() {
        fileList->clear();
        emit navToHome();
    });
}

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    grid = new QGridLayout(this);
    setLayout(grid);

    mergeBtn = new QPushButton("Merge PDFs", this);
    splitBtn = new QPushButton("Split PDF", this);
    editBtn = new QPushButton("Edit PDF", this);
    signBtn = new QPushButton("Sign PDF", this);
    convertBtn = new QPushButton("Convert PDF", this);
    fromImagesBtn = new QPushButton("Images to PDF", this);
    extractImagesBtn = new QPushButton("Extract images from PDF", this);
    lockBtn = new QPushButton("Lock PDF", this);
    unLockBtn = new QPushButton("Unlock PDF", this);
    rotatePagesBtn = new QPushButton("Rotate pages in PDF", this);
    removePagesBtn = new QPushButton("Remove pages from PDF", this);
    printBtn = new QPushButton("Print PDF", this);
    compressBtn = new QPushButton("Compress PDF", this);
    extractTextBtn = new QPushButton("Extract Text", this);

    grid->addWidget(mergeBtn, 0, 0);
    grid->addWidget(splitBtn, 0, 1);
    grid->addWidget(editBtn, 0, 2);

    grid->addWidget(signBtn, 1, 0);
    grid->addWidget(convertBtn, 1, 1);
    grid->addWidget(fromImagesBtn, 1, 2);

    grid->addWidget(extractImagesBtn, 2, 0);
    grid->addWidget(lockBtn, 2, 1);
    grid->addWidget(unLockBtn, 2, 2);

    grid->addWidget(rotatePagesBtn, 3, 0);
    grid->addWidget(removePagesBtn, 3, 1);
    grid->addWidget(printBtn, 3, 2);

    grid->addWidget(compressBtn, 4, 0);
    grid->addWidget(extractTextBtn, 4, 1);

    connect(mergeBtn, &QPushButton::clicked, this,
            [=]() { emit mergeOperation(); });

    connect(splitBtn, &QPushButton::clicked, this,
            [=]() { emit splitOperation(); });
}

MergePage::MergePage(QWidget *parent) : QWidget(parent) {
    addFilesBtn = new QPushButton("Add", this);
    removeFilesBtn = new QPushButton("Del", this);
    doMergeBtn = new QPushButton("Merge", this);
    doMergeBtn->setDisabled(true);
    backToHomeBtn = new QPushButton("Home", this);
    fileList = new QListWidget(this);
    layout = new QVBoxLayout(this);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(doMergeBtn);
    hbox->addStretch(1);
    hbox->addWidget(backToHomeBtn);
    hbox->addWidget(addFilesBtn);
    hbox->addWidget(removeFilesBtn);

    connect(fileList->model(), &QAbstractItemModel::rowsInserted,
            [=]() { doMergeBtn->setEnabled(fileList->count() > 0); });

    connect(fileList->model(), &QAbstractItemModel::rowsRemoved,
            [=]() { doMergeBtn->setEnabled(fileList->count() > 0); });

    setLayout(layout);

    layout->addWidget(fileList);
    layout->addLayout(hbox);

    connect(addFilesBtn, &QPushButton::clicked, this, [=]() {
        QStringList files = QFileDialog::getOpenFileNames(
            this, "Select Files", QDir::homePath(), "PDF Files (*.pdf)");

        for (auto &file : files) {
            fileList->addItem(file);
        }
        fileList->setDragDropMode(QAbstractItemView::InternalMove);
        fileList->setDefaultDropAction(Qt::MoveAction);
    });

    connect(removeFilesBtn, &QPushButton::clicked, this,
            [=]() { delete fileList->takeItem(fileList->currentRow()); });

    connect(backToHomeBtn, &QPushButton::clicked, this, [=]() {
        fileList->clear();
        emit navToHome();
    });

    connect(doMergeBtn, &QPushButton::clicked, this, &MergePage::mergeFiles);
}

void MergePage::mergeFiles() {
    QString outputName = QFileDialog::getSaveFileName(
        this, "Save Merged PDF", QDir::homePath(), "PDF Files (*.pdf)");

    if (outputName.isEmpty())
        return;

    auto fileNums = fileList->count();
    progress =
        new QProgressDialog("Merging Files", "Cancel", 0, fileNums, this);
    progress->setWindowModality(Qt::WindowModal);
    progress->setMinimumSize(400, 200);
    progress->setAutoClose(false);
    progress->setAutoReset(false);
    progress->show();

    PoDoFo::PdfMemDocument out;

    for (int i = 0; i < fileNums; i++) {
        PoDoFo::PdfMemDocument src;
        auto fileName = fileList->item(i)->text().toStdString();
        src.Load(fileName);
        out.GetPages().AppendDocumentPages(src);

        if (progress->wasCanceled())
            break;

        progress->setValue(i + 1);
        QApplication::processEvents();
        QThread::msleep(1000);
    }

    if (!progress->wasCanceled()) {
        out.Save(outputName.toStdString());
        progress->setLabelText("Completed!");
        progress->setCancelButtonText("Close");
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("fold");
    resize(480, 240);
    stack = new QStackedWidget(this);

    setCentralWidget(stack);

    homePage = new HomePage(this);
    mergePage = new MergePage(this);
    splitPage = new SplitPage(this);
    extractTextPage = new QWidget;

    stack->addWidget(homePage);
    stack->addWidget(mergePage);
    stack->addWidget(splitPage);
    stack->addWidget(extractTextPage);

    stack->setCurrentWidget(homePage);
    connect(homePage, &HomePage::mergeOperation, this,
            [=]() { stack->setCurrentWidget(mergePage); });

    connect(mergePage, &MergePage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(splitPage, &SplitPage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(homePage, &HomePage::splitOperation, this,
            [=]() { stack->setCurrentWidget(splitPage); });
}

MainWindow::~MainWindow() {}
