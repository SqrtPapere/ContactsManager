#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#define IP "<insert IP>"

#include <QObject>
#include "ui_mainwindow.h"
#include "downloader.h"
#include "sortfilterproxymodel.h"
#include <QStandardItemModel>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

class TableModel : public QObject
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr);

    void setUi(Ui::MainWindow *u);
    QStringList getRow(const QModelIndex &index);
    QStringList getAttr();

signals:
    void noConnection();

public slots:
    void downloadFinished();
    void onfilterchanged();
    void download();
    void insert(QStringList listData);
    void update(QStringList data);
    void deleteContact(QString id);
    void errorConnection();

    void filterTag(QStringList t);

private slots:



private:
    void Clear(void);
    Downloader *dwn;
    QStandardItemModel *modelcont;
    QStringList lowattr;
    Ui::MainWindow *ui;
    SortFilterProxyModel *filter;
    QString ip;
};

#endif // TABLEMODEL_H
