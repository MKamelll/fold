#include "reorderpage.hpp"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <podofo/podofo.h>
#include <QApplication>
#include <QThread>

ReorderPage::ReorderPage(QWidget *parent) : QWidget(parent) {
    addFilesBtn = new QPushButton("Add", this);
    doReorderBtn = new QPushButton("Reorder", this);
    doReorderBtn->setDisabled(true);
    backToHomeBtn = new QPushButton("Home", this);
    fileList = new QListWidget(this);
    layout = new QVBoxLayout(this);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(doReorderBtn);
    hbox->addStretch(1);
    hbox->addWidget(backToHomeBtn);
    hbox->addWidget(addFilesBtn);

    connect(fileList->model(), &QAbstractItemModel::rowsInserted,
            [=]() { doReorderBtn->setEnabled(fileList->count() > 0); });

    setLayout(layout);

    layout->addWidget(fileList);
    layout->addLayout(hbox);

    fileList->setViewMode(QListWidget::ListMode);
    fileList->setIconSize(QSize(120, 160));
    fileList->setSpacing(8);
    fileList->setAutoScroll(true);
    fileList->setAutoScrollMargin(20);
    fileList->setDragDropMode(QAbstractItemView::InternalMove);
    fileList->setDefaultDropAction(Qt::MoveAction);

    connect(addFilesBtn, &QPushButton::clicked, this, [=]() {
        filePath = QFileDialog::getOpenFileName(
            this, "Select A File", QDir::homePath(), "PDF Files (*.pdf)");

        if (filePath.isEmpty())
            return;

        fileList->clear();
        auto doc = Poppler::Document::load(filePath);

        for (int i = 0; i < doc->numPages(); i++) {
            QImage img = renderThumbnail(doc.get(), i);
            QListWidgetItem *item = new QListWidgetItem;
            item->setIcon(QIcon(QPixmap::fromImage(img)));
            item->setText(QString::asprintf("Page %d", i + 1));
            item->setData(Qt::UserRole, i);
            fileList->addItem(item);
        }
    });

    connect(backToHomeBtn, &QPushButton::clicked, this, [=]() {
        fileList->clear();
        emit navToHome();
    });

    connect(doReorderBtn, &QPushButton::clicked, this,
            &ReorderPage::reorderFile);
}

QImage ReorderPage::renderThumbnail(Poppler::Document *doc, int pageIndex,
                                    int width) {
    if (!doc || doc->isLocked()) {
        QMessageBox::information(this, "Info", "Couldn't load the document");
    }

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

void ReorderPage::reorderFile() {
    QString outputName = QFileDialog::getSaveFileName(
        this, "Save Merged PDF", QDir::homePath(), "PDF Files (*.pdf)");

    if (outputName.isEmpty())
        return;

    if (!outputName.endsWith(".pdf", Qt::CaseInsensitive))
        outputName.append(".pdf");

    auto pageNum = fileList->count();
    progress =
        new QProgressDialog("Reordering File", "Cancel", 0, pageNum, this);
    progress->setWindowModality(Qt::WindowModal);
    progress->setMinimumSize(400, 200);
    progress->setAutoClose(false);
    progress->setAutoReset(false);
    progress->show();

    PoDoFo::PdfMemDocument out;
    PoDoFo::PdfMemDocument src;
    src.Load(filePath.toStdString());

    for (int i = 0; i < pageNum; i++) {
        int pageIndex = fileList->item(i)->data(Qt::UserRole).toInt();
        out.GetPages().AppendDocumentPages(src, pageIndex, 1);

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
