#include "mainwindow.h"
#include "tablemodel.h"
#include <QApplication>
#include <QFile>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    //Model
    TableModel *h = new TableModel();

    //Delegate/Controller
    MainWindow w(h);

    //set the stylesheet for mainwindow
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        w.setStyleSheet(ts.readAll());
    }


    w.show();

    return a.exec();
    delete h;
}
