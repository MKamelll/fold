#pragma once
#include <poppler-qt6.h>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressDialog>
#include <QListWidget>

class DeletePage : public QWidget {
    Q_OBJECT

public:
    DeletePage(QWidget *parent = nullptr);

signals:
    void navToHome();

private slots:
    void deletePages();

private:
    QImage renderThumbnail(Poppler::Document *doc, int pageIndex,
                           int width = 300);

    QVBoxLayout *layout;
    QPushButton *addFileBtn;
    QPushButton *doDeleteBtn;
    QPushButton *backToHomeBtn;
    QProgressDialog *progress;
    QListWidget *fileList;
    QString filePath;
};
