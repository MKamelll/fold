#include "homepage.hpp"

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

    connect(editBtn, &QPushButton::clicked, this, [=]() {
        QMessageBox::information(this, "Info", "Editing Is Not Supported Yet");
    });

    connect(signBtn, &QPushButton::clicked, this, [=]() {
        QMessageBox::information(this, "Info", "Signing Is Not Supported Yet");
    });
}
