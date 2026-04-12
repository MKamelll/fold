#pragma once
#include "common.hpp"

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
