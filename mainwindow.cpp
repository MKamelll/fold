#include "mainwindow.hpp"
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "pdf.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    Pdf pdf;

    setWindowTitle("fold");
    resize(860, 640);
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    homePage = new QWidget;
    mergePage = new QWidget;
    splitPage = new QWidget;
    extractTextPage = new QWidget;

    stack->addWidget(homePage);
    stack->addWidget(mergePage);
    stack->addWidget(splitPage);
    stack->addWidget(extractTextPage);

    setupHomePage();
    setUpMergePage();
    stack->setCurrentWidget(homePage);
}

void MainWindow::switchToMergePage() { stack->setCurrentWidget(mergePage); }

void MainWindow::setupHomePage() {
    QGridLayout *layout = new QGridLayout;
    homePage->setLayout(layout);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);

    QPushButton *mergeBtn = new QPushButton("Merge PDFs", this);
    QPushButton *splitBtn = new QPushButton("Split PDFs", this);
    QPushButton *extractTextBtn = new QPushButton("Extract Text", this);

    for (auto *btn : {mergeBtn, splitBtn, extractTextBtn}) {
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    layout->addWidget(mergeBtn, 0, 0);
    layout->addWidget(splitBtn, 0, 1);
    layout->addWidget(extractTextBtn, 1, 0);

    connect(mergeBtn, &QPushButton::clicked, this,
            &MainWindow::switchToMergePage);
}

void MainWindow::setUpMergePage() {
    QPushButton *add_files = new QPushButton("Add Files", this);
    QVBoxLayout *layout = new QVBoxLayout;
    mergePage->setLayout(layout);
    layout->addWidget(add_files);
    layout->setAlignment(Qt::AlignCenter);
    connect(add_files, &QPushButton::clicked, this, &MainWindow::openFiles);
}

void MainWindow::openFiles() {
    QStringList files = QFileDialog::getOpenFileNames(
        this, "Select Files", QDir::homePath(), "PDF Files (*.pdf)");
}

MainWindow::~MainWindow() {}
