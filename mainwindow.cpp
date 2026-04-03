#include "mainwindow.hpp"
#include "pdf.hpp"
#include <QFileDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QStackedWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    Pdf pdf;

    setWindowTitle("fold");
    resize(480, 240);
    stack = new QStackedWidget(this);

    setCentralWidget(stack);

    homePage = new QWidget;
    mergePage = new QWidget;
    splitPage = new QWidget;
    extractTextPage = new QWidget;

    stack->addWidget(homePage);
    stack->addWidget(mergePage);
    stack->addWidget(splitPage);
    stack->addWidget(extractTextPage);

    backToHomeBtn = new QPushButton("Home", this);
    connect(backToHomeBtn, &QPushButton::clicked, this,
            [=]() { stack->setCurrentWidget(homePage); });

    setupHomePage();
    setUpMergePage();
    stack->setCurrentWidget(homePage);
}

void MainWindow::setupHomePage() {
    QGridLayout *grid = new QGridLayout;
    homePage->setLayout(grid);

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
            [=]() { stack->setCurrentWidget(mergePage); });
}

void MainWindow::setUpMergePage() {
    addFilesBtn = new QPushButton("Add", this);
    removeFilesBtn = new QPushButton("Del", this);
    mergeFilesBtn = new QPushButton("Merge", this);
    mergeFilesBtn->setDisabled(true);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(mergeFilesBtn);
    hbox->addStretch(1);
    hbox->addWidget(backToHomeBtn);
    hbox->addWidget(addFilesBtn);
    hbox->addWidget(removeFilesBtn);

    QVBoxLayout *layout = new QVBoxLayout;
    fileList = new QListWidget;

    connect(fileList->model(), &QAbstractItemModel::rowsInserted,
            [=]() { mergeFilesBtn->setEnabled(fileList->count() > 0); });

    connect(fileList->model(), &QAbstractItemModel::rowsRemoved,
            [=]() { mergeFilesBtn->setEnabled(fileList->count() > 0); });

    mergePage->setLayout(layout);

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
}

void MainWindow::mergeFiles() {}

MainWindow::~MainWindow() {}
