#include "sortfilterproxymodel.h"

SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void SortFilterProxyModel::setFilterTagList(QStringList lst){
    filterTagList=lst;
}


//overridden method to allow full-text search as requested.
bool SortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const{
    //qDebug()<<filterTagList;

    bool accepted = true;

    if(!filterTagList.isEmpty()){
        accepted = false;
        QModelIndex index6 = sourceModel()->index(sourceRow, 6, sourceParent);
        for(int i=0; i<filterTagList.length();i++){
            //qDebug()<<sourceModel()->data(index6).toString();
            if(filterTagList.at(i)==(sourceModel()->data(index6).toString())){
                accepted = true;
                break;
            }
        }

//        return filterRegExp(1).exactMatch(sourceModel()->data(index6).toString())
//                ||filterRegExp(2).exactMatch(sourceModel()->data(index6).toString());
//        //return sourceModel()->data(index6).toString().contains(filterRegExp());
    }
    if(!filterRegExp().isEmpty()){
    QModelIndex index0 = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex index1 = sourceModel()->index(sourceRow, 2, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 3, sourceParent);
    QModelIndex index3 = sourceModel()->index(sourceRow, 4, sourceParent);
    QModelIndex index4 = sourceModel()->index(sourceRow, 5, sourceParent);


    return (sourceModel()->data(index0).toString().contains(filterRegExp())
            || sourceModel()->data(index1).toString().contains(filterRegExp())
            || sourceModel()->data(index2).toString().contains(filterRegExp())
            || sourceModel()->data(index3).toString().contains(filterRegExp())
            || sourceModel()->data(index4).toString().contains(filterRegExp())) & accepted;
    }
    return accepted;
}

