#pragma once

#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupHomePage();
    void setUpMergePage();
    ~MainWindow();

private slots:
    void mergeFiles();

private:
    QWidget *homePage;
    QWidget *mergePage;
    QWidget *splitPage;
    QWidget *extractTextPage;
    QPushButton *mergeBtn;
    QPushButton *splitBtn;
    QPushButton *compressBtn;
    QPushButton *editBtn;
    QPushButton *signBtn;
    QPushButton *convertBtn;
    QPushButton *fromImagesBtn;
    QPushButton *extractImagesBtn;
    QPushButton *lockBtn;
    QPushButton *unLockBtn;
    QPushButton *rotatePagesBtn;
    QPushButton *removePagesBtn;
    QPushButton *printBtn;
    QPushButton *extractTextBtn;
    QPushButton *addFilesBtn;
    QPushButton *removeFilesBtn;
    QPushButton *doMergeBtn;
    QPushButton *backToHomeBtn;
    QStackedWidget *stack;
    QListWidget *fileList;
};
