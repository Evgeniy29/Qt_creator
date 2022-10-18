#include "mainwindow.h"

#include <QtWidgets>
#include "down_img.h"


Download::Download(QWidget* wgt) : QWidget(wgt)
{
    dl  = new Downloader(this);
    txt = new QLineEdit;
    pb = new QPushButton(tr("&Search"));
    bar  = new QProgressBar;

    QString strDownloadLink = "Input link";
    txt->setText(strDownloadLink);

    connect(pb, SIGNAL(clicked()), SLOT(slotSearch()));
    connect(dl, SIGNAL(downloadProgress(qint64, qint64)), this,  SLOT(slotDownloadProgress(qint64, qint64)));
    connect(dl, SIGNAL(done(const QUrl&, const QByteArray&)),this,  SLOT(slotDone(const QUrl&, const QByteArray&)));

    QGridLayout* pLayout = new QGridLayout;
    pLayout->addWidget(txt, 0, 0);
    pLayout->addWidget(pb, 0, 1);
    pLayout->addWidget(bar, 1, 0, 1, 0);
    setLayout(pLayout);
}

void Download::slotSearch()
{
    dl->download(QUrl(txt->text()));
}
void Download::slotDownloadProgress(qint64 nReceived, qint64 nTotal)
{
    if (nTotal <= 0) {
        slotError();
        return;
    }
    bar->setValue(100 * nReceived / nTotal);
}
void Download::slotDone(const QUrl& url, const QByteArray& ba)
{
    QString strFileName =
      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+ "/" + url.path().section('/', -1);
    QFile file(strFileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(ba);
        file.close();

        if (strFileName.endsWith(".jpg")|| strFileName.endsWith(".png"))
        {
            showPic(strFileName);
        }
    }
}

void Download::showPic(const QString& strFileName)
{
    QPixmap pix(strFileName);
    pix = pix.scaled(pix.size() / 2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QLabel* plbl = new QLabel;
    plbl->setPixmap(pix);
    plbl->setFixedSize(pix.size());
    plbl->show();
}

void Download::slotError()
{
    QMessageBox::critical(0,tr("Error_msg"),tr(" Error  download "));
}

