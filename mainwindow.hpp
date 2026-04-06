#pragma once

#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QGridLayout>

class HomePage : public QWidget {
    Q_OBJECT
public:
    HomePage(QWidget *parent = nullptr);

signals:
    void mergeOperation();

private:
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
    QGridLayout *grid;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setUpMergePage();
    ~MainWindow();

private slots:
    void mergeFiles();

private:
    HomePage *homePage;
    QWidget *mergePage;
    QWidget *splitPage;
    QWidget *extractTextPage;
    QPushButton *addFilesBtn;
    QPushButton *removeFilesBtn;
    QPushButton *doMergeBtn;
    QPushButton *backToHomeBtn;
    QStackedWidget *stack;
    QListWidget *fileList;
};
