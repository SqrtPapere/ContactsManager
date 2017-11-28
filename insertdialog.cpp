#include "insertdialog.h"
#include "ui_insertdialog.h"

InsertDialog::InsertDialog(TableModel *t, QWidget *parent) : QDialog(parent), ui(new Ui::InsertDialog){
    ui->setupUi(this);
    tm = t;
    head = tm->getAttr();
}

InsertDialog::~InsertDialog(){
    delete ui;
}

//method to capitalize first letter of string
QString InsertDialog::toCamelCase(const QString& s){
    QStringList parts = s.split(' ', QString::SkipEmptyParts);
    for (int i = 0; i < parts.size(); ++i)
        parts[i].replace(0, 1, parts[i][0].toUpper());

    return parts.join(" ");
}

//in the insert dialog, the user fill the new contact data. Then the model is asked for an insert
void InsertDialog::on_buttonBox_accepted(){
    QString name = toCamelCase(ui->textEditName1->text());
    QString surname = toCamelCase(ui->textEditSurname1->text());
    QString email = ui->textEditEmail1->text();
    QString note = ui->textEditNotes1->text();
    QString phone = ui->textEditPhone1->text();
    QString tag = "others";

    QStringList newData;
    newData.append(name);
    newData.append(surname);
    newData.append(phone);
    newData.append(email);
    newData.append(note);
    newData.append(tag);
    qDebug()<<newData;
    if(phone.isEmpty()){
        QMessageBox::critical(this, "Info", "Put at least a telephone number!");
    }
    tm->insert(newData);
}

