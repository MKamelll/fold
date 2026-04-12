#pragma once
#include "common.hpp"

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
