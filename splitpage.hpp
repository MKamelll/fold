#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QProgressDialog>
#include <QListWidget>

class SplitPage : public QWidget {
    Q_OBJECT
public:
    SplitPage(QWidget *parent = nullptr);

signals:
    void navToHome();

private slots:
    void splitFile();

private:
    QVBoxLayout *layout;
    QPushButton *addFilesBtn;
    QPushButton *doSplitBtn;
    QPushButton *backToHomeBtn;
    QSpinBox *toSpinBox;
    QSpinBox *fromSpinBox;
    QProgressDialog *progress;
    QListWidget *fileList;
};
