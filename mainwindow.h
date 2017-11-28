#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QStandardItemModel>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QStackedWidget>
#include <QComboBox>

#include <QSortFilterProxyModel>

#include <QWidget>


#include "downloader.h"
#include "insertdialog.h"
#include "tablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( TableModel *t, QWidget *parent = 0);
    ~MainWindow();

    void populateContactsTable();



private slots:
    void on_pushButtonAddNew_pressed();

    void onTableClicked(const QModelIndex &);
    void on_backToPage_clicked();

    void on_deleteButton_clicked();
    void noConnectionDialog();


//    void on_pushButton_clicked();

    void onTagFilterChanged(int);


signals:

private:
    Ui::MainWindow *ui;

    QModelIndex indx;
    TableModel *tabmodel;
    QStringList lowattr;
    QStringList clickedData;
    QButtonGroup *group;
    QButtonGroup *tagSearchGroup;


    void initDatabase();


};

#endif // MAINWINDOW_H
