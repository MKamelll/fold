#pragma once
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

class HomePage : public QWidget {
    Q_OBJECT
public:
    HomePage(QWidget *parent = nullptr);

signals:
    void mergeOperation();
    void splitOperation();
    void reorderOperation();
    void deleteOperation();

private:
    QToolButton *mergeBtn;
    QToolButton *splitBtn;
    QToolButton *reorderBtn;
    QToolButton *deleteBtn;
    QGridLayout *grid;
};
