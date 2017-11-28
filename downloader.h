#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QtNetwork>
#include <QMessageBox>



class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

    void doDownload(QNetworkRequest req);
    void doInsert(QNetworkRequest req, QUrlQuery postData);
    void doUpdate(QNetworkRequest req, QUrlQuery postData);
    void doDelete(QNetworkRequest req, QUrlQuery postData);

    QJsonArray getJs();

signals:
    void jsonfinished();
    void insertfinished();
    void insfinished();
    void updfinished();
    void delfinished();

    void noConnection();

public slots:
    void downloadFinished (QNetworkReply *reply);
    void insertfinished(QNetworkReply *reply);
    void uploadFinished(QNetworkReply *reply);
    void deleteFinished(QNetworkReply *reply);


public:

private:
   QNetworkAccessManager *managerDw;
   QNetworkAccessManager *managerIns;
   QNetworkAccessManager *managerUpd;
   QNetworkAccessManager *managerDel;

   QNetworkRequest req;
   QJsonArray jsa;
};

#endif // DOWNLOADER_H
