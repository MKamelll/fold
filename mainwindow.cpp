#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("fold");
    resize(480, 240);
    stack = new QStackedWidget(this);

    setCentralWidget(stack);

    homePage = new HomePage(this);
    mergePage = new MergePage(this);
    splitPage = new SplitPage(this);
    extractTextPage = new QWidget;

    stack->addWidget(homePage);
    stack->addWidget(mergePage);
    stack->addWidget(splitPage);
    stack->addWidget(extractTextPage);

    stack->setCurrentWidget(homePage);
    connect(homePage, &HomePage::mergeOperation, this,
            [=]() { stack->setCurrentWidget(mergePage); });

    connect(mergePage, &MergePage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(splitPage, &SplitPage::navToHome, this,
            [=]() { stack->setCurrentWidget(homePage); });

    connect(homePage, &HomePage::splitOperation, this,
            [=]() { stack->setCurrentWidget(splitPage); });
}

MainWindow::~MainWindow() {}
