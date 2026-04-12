#pragma once
#include "common.hpp"

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
