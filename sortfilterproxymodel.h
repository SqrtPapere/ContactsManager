#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QDebug>

//created to override a method for filtering in each attribute
class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterProxyModel(QObject *parent = 0);
    bool tagsearch = false;
    void setFilterTagList(QStringList lst);
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;


private:

    QStringList filterTagList;
};
#endif // SORTFILTERPROXYMODEL_H
