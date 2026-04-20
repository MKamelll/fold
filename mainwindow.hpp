#pragma once
#include "mergepage.hpp"
#include "splitpage.hpp"
#include "homepage.hpp"
#include "reorderpage.hpp"
#include "deletepage.hpp"

#include <QStackedWidget>
#include <QMainWindow>
#include <poppler-qt6.h>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    HomePage *homePage;
    MergePage *mergePage;
    SplitPage *splitPage;
    ReorderPage *reorderPage;
    DeletePage *deletePage;
    QStackedWidget *stack;
};
