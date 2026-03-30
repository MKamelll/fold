#include "mainwindow.hpp"
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QSizePolicy>

#include "pdf.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  Pdf pdf;

  setWindowTitle("fold");
  resize(860, 640);
  QWidget *central = new QWidget;
  QGridLayout *layout = new QGridLayout;
  setCentralWidget(central);
  central->setLayout(layout);
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

  connect(mergeBtn, &QPushButton::clicked, this, &MainWindow::openFiles);
}

void MainWindow::openFiles() {

  QStringList files = QFileDialog::getOpenFileNames(
      this, "Select Files", QDir::homePath(), "PDF Files (*.pdf)");
}

MainWindow::~MainWindow() {}
