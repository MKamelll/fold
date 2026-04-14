#pragma once
#include "mergepage.hpp"
#include "splitpage.hpp"
#include "homepage.hpp"
#include "reorderpage.hpp"

#include <QStackedWidget>
#include <QMainWindow>
#include <poppler-qt6.h>

class DeletePage : public QWidget {
    Q_OBJECT

public:
    DeletePage(QWidget *parent = nullptr);

signals:
    void navToHome();

private slots:
    void deletePages();

private:
    QVBoxLayout *layout;
    QPushButton *addFileBtn;
    QPushButton *doDeleteBtn;
    QPushButton *backToHomeBtn;
    QProgressDialog *progress;
    QListWidget *fileList;
};

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
