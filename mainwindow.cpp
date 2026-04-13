#include "mainwindow.hpp"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <podofo/podofo.h>
#include <QApplication>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("fold");
    resize(480, 240);
    stack = new QStackedWidget(this);

    setCentralWidget(stack);

    homePage = new HomePage(this);
    mergePage = new MergePage(this);
    splitPage = new SplitPage(this);
    reorderPage = new ReorderPage(this);

    stack->addWidget(homePage);
    stack->addWidget(mergePage);
    stack->addWidget(splitPage);
    stack->addWidget(reorderPage);

    stack->setCurrentWidget(homePage);
    connect(homePage, &HomePage::mergeOperation, this,
            [=]() { stack->setCurrentWidget(mergePage); });

    connect(mergePage, &MergePage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(splitPage, &SplitPage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(reorderPage, &ReorderPage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(homePage, &HomePage::splitOperation, this,
            [=]() { stack->setCurrentWidget(splitPage); });

    connect(homePage, &HomePage::reorderOperation, this,
            [=]() { stack->setCurrentWidget(reorderPage); });
}

MainWindow::~MainWindow() {}
