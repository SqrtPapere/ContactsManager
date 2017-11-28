#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent){

    //Instanciate a NAM for each operation. o.w. finished signal would be mixed
    managerDw = new QNetworkAccessManager(this);
    managerIns = new QNetworkAccessManager(this);
    managerUpd = new QNetworkAccessManager(this);
    managerDel = new QNetworkAccessManager(this);

    connect(managerIns, SIGNAL(finished(QNetworkReply*)), this, SLOT(insertfinished(QNetworkReply*)));
    connect(managerDw, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
    connect(managerUpd, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadFinished(QNetworkReply*)));
    connect(managerDel, SIGNAL(finished(QNetworkReply*)), this, SLOT(deleteFinished(QNetworkReply*)));

}

QJsonArray Downloader::getJs(){
    return jsa;
}

void Downloader::doDownload(QNetworkRequest req){
    QNetworkReply *reply = managerDw->get(req);

}

void Downloader::doInsert(QNetworkRequest req, QUrlQuery postData){
    managerIns->post(req, postData.toString(QUrl::FullyEncoded).toUtf8());
}

void Downloader::doUpdate(QNetworkRequest req, QUrlQuery postData){
     managerUpd->post(req, postData.toString(QUrl::FullyEncoded).toUtf8());
}

void Downloader::doDelete(QNetworkRequest req, QUrlQuery postData){
    managerDel->post(req, postData.toString(QUrl::FullyEncoded).toUtf8());
}

void Downloader::insertfinished(QNetworkReply *reply){
    emit insfinished();
}

void Downloader::uploadFinished(QNetworkReply *reply){
    emit updfinished();
}

void Downloader::deleteFinished(QNetworkReply *reply){
    emit delfinished();
}

//checks for connection and then produce a json of the data retrieved
void Downloader::downloadFinished(QNetworkReply *reply){
    if(!reply->bytesAvailable()) emit noConnection();
    if(reply->error()){
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else{
        QString strReply = (QString)reply->readAll();
        strReply = strReply.simplified();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        jsa = jsonResponse.array();
    }
    reply->deleteLater();
    emit jsonfinished();

}


