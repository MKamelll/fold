#pragma once

#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QGridLayout>
#include <QProgressDialog>
#include <QSpinBox>
#include <QGroupBox>

class SplitPage : public QWidget {
    Q_OBJECT
public:
    SplitPage(QWidget *parent = nullptr);

signals:
    void navToHome();

private:
    QVBoxLayout *layout;
    QPushButton *addFilesBtn;
    QPushButton *doSplitBtn;
    QPushButton *removeFilesBtn;
    QPushButton *backToHomeBtn;
    QSpinBox *spinBox;
    QProgressDialog *progress;
    QListWidget *fileList;
};

class HomePage : public QWidget {
    Q_OBJECT
public:
    HomePage(QWidget *parent = nullptr);

signals:
    void mergeOperation();
    void splitOperation();

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

class MergePage : public QWidget {
    Q_OBJECT

public:
    MergePage(QWidget *parent = nullptr);

signals:
    void navToHome();

private slots:
    void mergeFiles();

private:
    QVBoxLayout *layout;
    QPushButton *addFilesBtn;
    QPushButton *removeFilesBtn;
    QPushButton *doMergeBtn;
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
    QWidget *extractTextPage;
    QStackedWidget *stack;
};
