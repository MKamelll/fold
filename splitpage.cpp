#include "splitpage.hpp"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <podofo/podofo.h>
#include <QApplication>
#include <QThread>
#include <QLabel>

SplitPage::SplitPage(QWidget *parent) : QWidget(parent) {
    addFilesBtn = new QPushButton("Add", this);
    doSplitBtn = new QPushButton("Split", this);
    doSplitBtn->setDisabled(true);
    backToHomeBtn = new QPushButton("Home", this);
    fileList = new QListWidget(this);
    layout = new QVBoxLayout(this);
    fromSpinBox = new QSpinBox(this);
    toSpinBox = new QSpinBox(this);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(doSplitBtn);
    hbox->addStretch(1);
    hbox->addWidget(backToHomeBtn);
    hbox->addWidget(addFilesBtn);

    toSpinBox->setValue(1);
    toSpinBox->setMinimum(1);
    fromSpinBox->setValue(1);
    fromSpinBox->setMinimum(1);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(new QLabel("From"));
    hbox2->addWidget(fromSpinBox);
    hbox2->addStretch(1);
    hbox2->addWidget(new QLabel("To"));
    hbox2->addWidget(toSpinBox);

    connect(fileList->model(), &QAbstractItemModel::rowsInserted,
            [=]() { doSplitBtn->setEnabled(fileList->count() > 0); });

    setLayout(layout);

    layout->addWidget(fileList);
    layout->addLayout(hbox2);
    layout->addLayout(hbox);

    connect(addFilesBtn, &QPushButton::clicked, this, [=]() {
        QString file = QFileDialog::getOpenFileName(
            this, "Select A File", QDir::homePath(), "PDF Files (*.pdf)");

        if (file.isEmpty())
            return;

        fileList->clear();
        fileList->addItem(file);
        fileList->setCurrentRow(0);
    });

    connect(backToHomeBtn, &QPushButton::clicked, this, [=]() {
        fileList->clear();
        emit navToHome();
    });

    connect(doSplitBtn, &QPushButton::clicked, this, &SplitPage::splitFile);
}

void SplitPage::splitFile() {
    QString outputName = QFileDialog::getSaveFileName(
        this, "Save Splitted File", QDir::homePath(), "PDF Files (*.pdf)");

    if (outputName.isEmpty())
        return;

    if (!outputName.endsWith(".pdf", Qt::CaseInsensitive))
        outputName.append(".pdf");

    size_t fromPage = fromSpinBox->value();
    size_t toPage = toSpinBox->value();
    PoDoFo::PdfMemDocument src;
    auto fileName = fileList->item(0)->text().toStdString();
    src.Load(fileName);

    if (toPage > src.GetPages().GetCount()) {
        QMessageBox::information(
            this, "Info", "Range Is Out Of The Document Available Page Count");
        return;
    }

    progress = new QProgressDialog("Spliting The File", "Cancel", fromPage,
                                   toPage, this);
    progress->setWindowModality(Qt::WindowModal);
    progress->setMinimumSize(400, 200);
    progress->setAutoClose(false);
    progress->setAutoReset(false);
    progress->show();

    PoDoFo::PdfMemDocument out;
    for (size_t i = fromPage - 1; i < toPage; i++) {
        out.GetPages().AppendDocumentPages(src, i, 1);
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
