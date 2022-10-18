#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QUrl>

class Downloader;
class QLineEdit;
class QPushButton;
class QProgressBar;
class Download : public QWidget {
Q_OBJECT

private:
    Downloader* dl;
    QLineEdit* txt;
    QPushButton* pb;
    QProgressBar* bar;
    void showPic(const QString&);

public:
    Download(QWidget* wgt = 0);

private slots:
    void slotSearch();
    void slotError();
    void slotDone(const QUrl&, const QByteArray&);
    void slotDownloadProgress(qint64, qint64);
};
#endif // MAINWINDOW_H
