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
    QPushButton *reorderBtn;
    QGridLayout *grid;
};
