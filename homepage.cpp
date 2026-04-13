#include "homepage.hpp"
#include "awesome.hpp"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    grid = new QGridLayout(this);
    setLayout(grid);

    mergeBtn = new QToolButton(this);
    mergeBtn->setIcon(
        Awesome::instance()->icon(fa::fa_solid, fa::fa_layer_group));
    mergeBtn->setText("Merge PDFs");
    mergeBtn->setIconSize(QSize(50, 50));
    mergeBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    splitBtn = new QToolButton(this);
    splitBtn->setIcon(
        Awesome::instance()->icon(fa::fa_solid, fa::fa_object_ungroup));
    splitBtn->setIconSize(QSize(50, 50));
    splitBtn->setText("Split PDF");
    splitBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    reorderBtn = new QToolButton(this);
    reorderBtn->setIcon(
        Awesome::instance()->icon(fa::fa_solid, fa::fa_list_ol));
    reorderBtn->setIconSize(QSize(50, 50));
    reorderBtn->setText("Reorder PDF");
    reorderBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    grid->addWidget(mergeBtn, 0, 0);
    grid->addWidget(splitBtn, 0, 1);
    grid->addWidget(reorderBtn, 0, 2);

    connect(mergeBtn, &QToolButton::clicked, this,
            [=]() { emit mergeOperation(); });

    connect(splitBtn, &QToolButton::clicked, this,
            [=]() { emit splitOperation(); });

    connect(reorderBtn, &QToolButton::clicked, this,
            [=]() { emit reorderOperation(); });
}
