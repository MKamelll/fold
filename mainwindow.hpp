#pragma once

#include <QMainWindow>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupHomePage();
    void setUpMergePage();
    ~MainWindow();

private slots:
    void switchToMergePage();
    void openFiles();

private:
    QWidget *homePage;
    QWidget *mergePage;
    QWidget *splitPage;
    QWidget *extractTextPage;
    QStackedWidget *stack;
};
