#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QObject(parent)
{
    dwn = new Downloader();

    lowattr << "id"<< "name" << "surname" << "phone"<<"email"<<"note"<<"tag";
    ip = IP;
    modelcont = new QStandardItemModel(0, lowattr.length());
    for(int i=0;i<lowattr.length();i++){
        modelcont->setHorizontalHeaderItem(i, new QStandardItem(QString(lowattr.at(i)).toUpper()));
    }

    filter = new SortFilterProxyModel(this);
    filter->setSourceModel(modelcont);
    QObject::connect(dwn, SIGNAL(jsonfinished()),this, SLOT(downloadFinished()));
    QObject::connect(dwn, SIGNAL(noConnection()),this, SLOT(errorConnection()));
    //every time a change is made to the db, we re-download all data
    QObject::connect(dwn, SIGNAL(insfinished()),this, SLOT(download()));
    QObject::connect(dwn, SIGNAL(updfinished()),this, SLOT(download()));
    QObject::connect(dwn, SIGNAL(delfinished()),this, SLOT(download()));

}


void TableModel::setUi(Ui::MainWindow *u){
    this->ui=u;
    ui->tableInventory->setModel(filter);
}

// remove all data from internal data structures, called every time before the download
void TableModel::Clear(void){
    modelcont->resetInternalData();
    modelcont->removeRows(0, modelcont->rowCount());
}

//download method that ask to the downloader object to doDownload
void TableModel::download(){
    QNetworkRequest request(QUrl("http://"+ip+"/download.php"));
    dwn->doDownload(request);
}

//update method that given the data of the user ask the downloader to update the db
void TableModel::update(QStringList data){
    QNetworkRequest request(QUrl("http://"+ip+"/update.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrlQuery postData;
    for(int k=0;k<data.length();k++){
        postData.addQueryItem(lowattr.at(k), data.at(k));
    }
    dwn->doUpdate(request, postData);
}

//delete method that given the id of an user ask the downloader to delete the user
void TableModel::deleteContact(QString id){
    QNetworkRequest request(QUrl("http://"+ip+"/delete.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrlQuery postData;
    postData.addQueryItem(lowattr.at(0), id);

    dwn->doDelete(request, postData);
}

//emit signal to ask mainwindow to show the error dialog of no internet
void TableModel::errorConnection(){
    emit noConnection();

}

void TableModel::filterTag(QStringList t)
{
    qDebug()<<t;
    filter->setFilterTagList(t);
    filter->setFilterRegExp("");


    //filter->setFilterKeyColumn(6);

}

//every time that the filter field content changes, we update the fltered result
void TableModel::onfilterchanged(){
    QRegExp rx(ui->filterEdit->text());
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    filter->setFilterRegExp(rx);
}

//when the downlader emits the jsonfinished signal, this method takes the json produced and use it to feed data to the model
void TableModel::downloadFinished(){
    Clear();
    QJsonArray j = dwn->getJs();
    int i=0;
    foreach (QJsonValue internobj, j) {
        foreach (QString s, lowattr) {
            modelcont->setItem(i,lowattr.indexOf(s), new QStandardItem(internobj.toObject().value(s).toString()));  //download from db
        }
        i++;
    }
    ui->tableInventory->setColumnHidden(0, true);  //hide the ID column from the view
    ui->tableInventory->setColumnHidden(6, true);  //hide the TAG column from the view

}

//returns a QStringList representing the row data at a index
QStringList TableModel::getRow(const QModelIndex &index){
    QStringList rowData;
    QModelIndex ind = filter->mapToSource(index);
    foreach (QString s, lowattr) {
        rowData.append(modelcont->index(ind.row(),lowattr.indexOf(s)).data().toString());
    }
    return rowData;
}

//prepare the request and send it to the downloader
void TableModel::insert(QStringList listData){

    QUrlQuery postData;
    for(int k=0;k<listData.length();k++){
        postData.addQueryItem(lowattr.at(k+1), listData.at(k));
    }

    QNetworkRequest request(QUrl("http://"+ip+"/insert.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    dwn->doInsert(request, postData);
}

QStringList TableModel::getAttr(){
    return lowattr;
}






