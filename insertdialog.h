#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QString>
#include <QStringList>
#include "tablemodel.h"

namespace Ui {
class InsertDialog;
}

class InsertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertDialog(TableModel *t, QWidget *parent = 0);
    ~InsertDialog();
    QString toCamelCase(const QString& s);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::InsertDialog *ui;
    QStringList head;
    TableModel *tm;
};

#endif // INSERTDIALOG_H
