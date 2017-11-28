#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(TableModel *t, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    tabmodel = t;
    t->setUi(ui);


    //Set stylesheet for remaining part of ui
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        ui->stackedWidget->setStyleSheet(ts.readAll());
        ui->groupBoxTagSearch->setStyleSheet(ts.readAll());
        ui->tableInventory->setStyleSheet(ts.readAll());
        ui->filterEdit->setStyleSheet(ts.readAll());
        ui->pushButtonAddNew->setStyleSheet(ts.readAll());
    }

    populateContactsTable();
    initDatabase();

    //Filter table of contacts
    QObject::connect(ui->filterEdit, SIGNAL(textChanged(QString)), tabmodel, SLOT(onfilterchanged()));
    //select from tableInventory to get data
    QObject::connect(ui->tableInventory, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
    //no connection to internet dialog
    QObject::connect(tabmodel, SIGNAL(noConnection()), this, SLOT(noConnectionDialog()));

    QObject::connect(tagSearchGroup, SIGNAL(buttonClicked(int)), this, SLOT(onTagFilterChanged(int)));


}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::populateContactsTable(){   
    ui->tableInventory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableInventory->setAlternatingRowColors(true);
    ui->tableInventory->verticalHeader()->setVisible(false);
    ui->tableInventory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableInventory->setSortingEnabled(true);
    ui->tableInventory->setFocusPolicy(Qt::NoFocus);
    QList<QRadioButton *> allButtons = ui->groupBox->findChildren<QRadioButton *>();
    group = new QButtonGroup;
    qDebug() <<allButtons.size();
    for(int i=0; i<allButtons.size(); i++){
        group->addButton(allButtons[i], i);
    }
    QList<QCheckBox *> tagButtons = ui->groupBoxTagSearch->findChildren<QCheckBox *>();
    tagSearchGroup = new QButtonGroup;
    tagSearchGroup->setExclusive(false);
    for(int i=0; i<tagButtons.size(); i++){
        tagSearchGroup->addButton(tagButtons[i], i);
    }

}

void MainWindow::onTableClicked(const QModelIndex &index){

    QStringList tags;
    tags << "school" << "so" <<"work"<<"relatives"<<"friend";

    ui->stackedWidget->setCurrentIndex(1);
    if (index.isValid()) {
        clickedData = tabmodel->getRow(index);
        ui->textEditName1->setText(clickedData.at(1));
        ui->textEditSurname1->setText(clickedData.at(2));
        ui->textEditPhone1->setText(clickedData.at(3));
        ui->textEditEmail1->setText(clickedData.at(4));
        ui->textEditNotes1->setText(clickedData.at(5));
        qDebug()<<"clicked";

        qDebug()<<clickedData.at(6);
        switch(tags.indexOf(clickedData.at(6))) {
        case 0:  ui->radioSchool->setChecked(true); break;
        case 1:  ui->radioSO->setChecked(true); break;
        case 2:  ui->radioWork->setChecked(true); break;
        case 3:  ui->radioRelative->setChecked(true); break;
        case 4:  ui->radioFriend->setChecked(true); break;
        default: ui->radioOthers->setChecked(true);
            break;
        }
    }
}


void MainWindow::on_pushButtonAddNew_pressed(){

    InsertDialog dialog(tabmodel);
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        dialog.setStyleSheet(ts.readAll());
    }
    dialog.exec();
    ui->filterEdit->setFocus();
}

//asks the model to get the data
void MainWindow::initDatabase(){
    tabmodel->download();
}

//triggered by the back-button in one contact visualization mode. Even if you changed nothing we update the model
void MainWindow::on_backToPage_clicked()
{
    //    QString oldData = modelinv->index(indx.row(),1).data().toString() + modelinv->index(indx.row(),2).data().toString();
    //    QString newData = ui->textEditName->toPlainText()+ui->textEditSurname->toPlainText();
    //    if(newData.compare(oldData)!=0){
    //        qDebug()<<"somethingchanged()";

    //    }
    QStringList updatedData;
    updatedData.append(clickedData.at(0));
    updatedData.append(ui->textEditName1->text());
    updatedData.append(ui->textEditSurname1->text());
    updatedData.append(ui->textEditPhone1->text());
    updatedData.append(ui->textEditEmail1->text());
    updatedData.append(ui->textEditNotes1->text());
    qDebug()<<group->checkedButton()->text();
    updatedData.append(group->checkedButton()->text());

    tabmodel->update(updatedData);
    ui->stackedWidget->setCurrentIndex(0);

}
//triggered by the delete-button in one contact visualization mode. Asks the model to delete the contact
void MainWindow::on_deleteButton_clicked()
{
    tabmodel->deleteContact(clickedData.at(0));
    ui->stackedWidget->setCurrentIndex(0);
}
//promped dialog on fail to connect to the internet
void MainWindow::noConnectionDialog()
{
    qDebug()<<"No Connection!!";
    QMessageBox::critical(this, "Info", "You are NOT connected to internet");
}



//void MainWindow::on_pushButton_clicked()
//{
//    QString t = ui->lineEdit->text();
//    tabmodel->filterTag(t);

//}

void MainWindow::onTagFilterChanged(int ch)
{

    QList<QAbstractButton*> buttons = tagSearchGroup->buttons();
    QStringList checked;
    for(int i=0; i<buttons.size(); i++){
        if(buttons.at(i)->isChecked()){
            qDebug()<<"1";
            checked.append(buttons.at(i)->text());
        }
    }
    qDebug()<<checked;
//    for(int i = 0; i<checked.size();i++){
//        qDebug()<<checked.at(i);

//    }
    //qDebug()<<tagSearchGroup->checkedButton()->text();

    tabmodel->filterTag(checked);
    checked.clear();

}
