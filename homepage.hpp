#pragma once
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class HomePage : public QWidget {
    Q_OBJECT
public:
    HomePage(QWidget *parent = nullptr);

signals:
    void mergeOperation();
    void splitOperation();
    void reorderOperation();

private:
    QPushButton *mergeBtn;
    QPushButton *splitBtn;
    QPushButton *reorderBtn;
    QGridLayout *grid;
};
