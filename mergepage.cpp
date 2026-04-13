#include "mergepage.hpp"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <podofo/podofo.h>
#include <QApplication>
#include <QThread>

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

    outputName.push_back(".pdf");

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
