#include <QtNetwork>
#include "down_img.h"

Downloader::Downloader(QObject* pobj/*=0*/) : QObject(pobj)
{
    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)),this,SLOT(slotFinished(QNetworkReply*)));
}

void Downloader::download(const QUrl& url)
{
    QNetworkRequest request(url);
    QNetworkReply* nr = nam->get(request);
    connect(nr, SIGNAL(downloadProgress(qint64, qint64)),this, SIGNAL(downloadProgress(qint64, qint64)));
}

void Downloader::slotFinished(QNetworkReply* nr)
{
    if (nr->error() != QNetworkReply::NoError)
    {
        emit error();
    }
    else
    {
        emit done(nr->url(), nr->readAll());
    }
    nr->deleteLater();
}
