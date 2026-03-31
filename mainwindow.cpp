#include "mainwindow.hpp"
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pdf.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    Pdf pdf;

    setWindowTitle("fold");
    resize(480, 240);
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
    QGridLayout *grid = new QGridLayout;
    homePage->setLayout(grid);
    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 0);
    grid->setColumnStretch(2, 1);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(20);
    QPushButton *mergeBtn = new QPushButton("Merge PDFs", this);
    QPushButton *splitBtn = new QPushButton("Split PDFs", this);
    QPushButton *extractTextBtn = new QPushButton("Extract Text", this);

    vbox->addWidget(mergeBtn);
    vbox->addWidget(splitBtn);
    vbox->addWidget(extractTextBtn);
    grid->addLayout(vbox, 0, 1);

    connect(mergeBtn, &QPushButton::clicked, this,
            &MainWindow::switchToMergePage);
}

void MainWindow::setUpMergePage() {
    QPushButton *addFiles = new QPushButton("Add Files", this);
    QVBoxLayout *layout = new QVBoxLayout;
    fileList = new QListWidget;
    mergePage->setLayout(layout);

    layout->addWidget(fileList);
    layout->addWidget(addFiles);

    connect(addFiles, &QPushButton::clicked, this, &MainWindow::openFiles);
}

void MainWindow::openFiles() {
    QStringList files = QFileDialog::getOpenFileNames(
        this, "Select Files", QDir::homePath(), "PDF Files (*.pdf)");

    for (auto &file : files) {
        fileList->addItem(file);
    }
    fileList->setDragDropMode(QAbstractItemView::InternalMove);
    fileList->setDefaultDropAction(Qt::MoveAction);
}

MainWindow::~MainWindow() {}
