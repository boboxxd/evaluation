#include "companydatamodel.h"

CompanyDataModel::CompanyDataModel(QObject *parent) : QAbstractListModel(parent)
{
    map.insert("-缺陷类别-",0);
    map.insert("导地线",0.3);
    map.insert("绝缘子",0.5);
    map.insert("线夹、均压环",0.5);
    map.insert("防震锤",0.5);
    map.insert("细小金具",0.3);
    map.insert("基础",0.5);
    map.insert("附属设施",0.5);
    map.insert("异物缺陷",0.5);
}

int CompanyDataModel::rowCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent)
    return map.count();      //返回item的个数
}

//获取索引项对应的数据
QVariant CompanyDataModel::data(const QModelIndex &index, int role) const
{
    if (! index.isValid())
        return QVariant();
    if (index.row() >= map.size())
        return QVariant();
    if (role == Qt::DisplayRole)
        return map.keys().at(index.row());
    if (role == Qt::UserRole)
        return map.values().at(index.row());
    else return QVariant();
}

//设置表头对应的数据
QVariant CompanyDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return QString("-缺陷类别-").arg(section); //表头显示的数据
    return  QVariant();
}
