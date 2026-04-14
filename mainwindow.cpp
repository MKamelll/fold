#include "mainwindow.hpp"
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

    connect(addFileBtn, &QPushButton::clicked, this, [=]() {
        QStringList files = QFileDialog::getOpenFileNames(
            this, "Select Files", QDir::homePath(), "PDF Files (*.pdf)");

        for (auto &file : files) {
            fileList->addItem(file);
        }
        fileList->setDragDropMode(QAbstractItemView::InternalMove);
        fileList->setDefaultDropAction(Qt::MoveAction);
    });

    connect(backToHomeBtn, &QPushButton::clicked, this, [=]() {
        fileList->clear();
        emit navToHome();
    });

    connect(doDeleteBtn, &QPushButton::clicked, this, &DeletePage::deletePages);
}

void DeletePage::deletePages() {}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("fold");
    resize(480, 240);
    stack = new QStackedWidget(this);

    setCentralWidget(stack);

    homePage = new HomePage(this);
    mergePage = new MergePage(this);
    splitPage = new SplitPage(this);
    reorderPage = new ReorderPage(this);
    deletePage = new DeletePage(this);

    stack->addWidget(homePage);
    stack->addWidget(mergePage);
    stack->addWidget(splitPage);
    stack->addWidget(reorderPage);
    stack->addWidget(deletePage);

    stack->setCurrentWidget(homePage);
    connect(homePage, &HomePage::mergeOperation, this,
            [=]() { stack->setCurrentWidget(mergePage); });

    connect(mergePage, &MergePage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(splitPage, &SplitPage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(reorderPage, &ReorderPage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(deletePage, &DeletePage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(homePage, &HomePage::splitOperation, this,
            [=]() { stack->setCurrentWidget(splitPage); });

    connect(homePage, &HomePage::reorderOperation, this,
            [=]() { stack->setCurrentWidget(reorderPage); });

    connect(homePage, &HomePage::deleteOperation, this,
            [=]() { stack->setCurrentWidget(deletePage); });
}

MainWindow::~MainWindow() {}
