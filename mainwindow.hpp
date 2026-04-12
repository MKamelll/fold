#pragma once
#include "common.hpp"
#include "mergepage.hpp"
#include "splitpage.hpp"
#include "homepage.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    HomePage *homePage;
    MergePage *mergePage;
    SplitPage *splitPage;
    QWidget *extractTextPage;
    QStackedWidget *stack;
};
