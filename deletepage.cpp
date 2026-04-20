#include "deletepage.hpp"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <podofo/podofo.h>
#include <QApplication>
#include <QThread>

DeletePage::DeletePage(QWidget *parent) : QWidget(parent) {
    addFileBtn = new QPushButton("Add", this);
    doDeleteBtn = new QPushButton("Delete", this);
    doDeleteBtn->setDisabled(true);
    backToHomeBtn = new QPushButton("Home", this);
    fileList = new QListWidget(this);
    layout = new QVBoxLayout(this);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(doDeleteBtn);
    hbox->addStretch(1);
    hbox->addWidget(backToHomeBtn);
    hbox->addWidget(addFileBtn);

    connect(fileList->model(), &QAbstractItemModel::rowsInserted,
            [=]() { doDeleteBtn->setEnabled(fileList->count() > 0); });

    connect(fileList->model(), &QAbstractItemModel::rowsRemoved,
            [=]() { doDeleteBtn->setEnabled(fileList->count() > 0); });

    setLayout(layout);

    layout->addWidget(fileList);
    layout->addLayout(hbox);

    fileList->setViewMode(QListWidget::ListMode);
    fileList->setIconSize(QSize(120, 160));
    fileList->setSpacing(8);

    connect(addFileBtn, &QPushButton::clicked, this, [=]() {
        filePath = QFileDialog::getOpenFileName(
            this, "Select A File", QDir::homePath(), "PDF Files (*.pdf)");

        if (filePath.isEmpty())
            return;

        fileList->clear();
        auto doc = Poppler::Document::load(filePath);
        if (!doc || doc->numPages() <= 0 || doc->isLocked())
            return;

        for (int i = 0; i < doc->numPages(); i++) {
            QImage img = renderThumbnail(doc.get(), i);
            QListWidgetItem *item = new QListWidgetItem;
            item->setIcon(QIcon(QPixmap::fromImage(img)));
            item->setText(QString::asprintf("Page %d", i + 1));
            item->setCheckState(Qt::Unchecked);
            fileList->addItem(item);
        }
    });

    connect(backToHomeBtn, &QPushButton::clicked, this, [=]() {
        fileList->clear();
        emit navToHome();
    });

    connect(doDeleteBtn, &QPushButton::clicked, this, &DeletePage::deletePages);
}

void DeletePage::deletePages() {
    QString outputName = QFileDialog::getSaveFileName(
        this, "Save Edited PDF", QDir::homePath(), "PDF Files (*.pdf)");

    if (outputName.isEmpty())
        return;

    if (!outputName.endsWith(".pdf", Qt::CaseInsensitive))
        outputName.append(".pdf");

    QList<int> pagesToInclude;
    for (int i = 0; i < fileList->count(); i++) {
        if (fileList->item(i)->checkState() == Qt::Unchecked) {
            pagesToInclude.append(i);
        }
    }

    PoDoFo::PdfMemDocument src;
    src.Load(filePath.toStdString());

    progress = new QProgressDialog("Deleting Pages", "Cancel", 0,
                                   pagesToInclude.size(), this);
    progress->setWindowModality(Qt::WindowModal);
    progress->setMinimumSize(400, 200);
    progress->setAutoClose(false);
    progress->setAutoReset(false);
    progress->show();

    PoDoFo::PdfMemDocument out;

    for (int i = 0; i < pagesToInclude.size(); i++) {
        out.GetPages().AppendDocumentPages(src, pagesToInclude[i], 1);

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

QImage DeletePage::renderThumbnail(Poppler::Document *doc, int pageIndex,
                                   int width) {

    doc->setRenderHint(Poppler::Document::Antialiasing);
    doc->setRenderHint(Poppler::Document::TextAntialiasing);

    auto page = doc->page(pageIndex);
    if (!page) {
        QMessageBox::information(
            this, "Info",
            QString::asprintf("Couldn't render page with index '%d'",
                              pageIndex));
    }

    auto scale = width / page->pageSizeF().width();
    return page->renderToImage(72 * scale, 72 * scale);
}
