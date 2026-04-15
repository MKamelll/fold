#pragma once
#include <QWidget>
#include <poppler-qt6.h>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressDialog>
#include <QListWidget>

class ReorderPage : public QWidget {
    Q_OBJECT
public:
    ReorderPage(QWidget *parent = nullptr);
    QImage renderThumbnail(Poppler::Document *doc, int pageIndex,
                           int width = 300);

signals:
    void navToHome();

private slots:
    void reorderFile();

private:
    QVBoxLayout *layout;
    QPushButton *addFilesBtn;
    QPushButton *doReorderBtn;
    QPushButton *backToHomeBtn;
    QProgressDialog *progress;
    QListWidget *fileList;
    QString filePath;
};
