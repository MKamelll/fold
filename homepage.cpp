#include "homepage.hpp"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    grid = new QGridLayout(this);
    setLayout(grid);

    mergeBtn = new QPushButton("Merge PDFs", this);
    splitBtn = new QPushButton("Split PDF", this);
    reorderBtn = new QPushButton("Reorder PDF", this);

    grid->addWidget(mergeBtn, 0, 0);
    grid->addWidget(splitBtn, 0, 1);
    grid->addWidget(reorderBtn, 0, 2);

    connect(mergeBtn, &QPushButton::clicked, this,
            [=]() { emit mergeOperation(); });

    connect(splitBtn, &QPushButton::clicked, this,
            [=]() { emit splitOperation(); });

    connect(reorderBtn, &QPushButton::clicked, this,
            [=]() { emit reorderOperation(); });
}
