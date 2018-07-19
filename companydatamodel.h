#ifndef COMPANYDATAMODEL_H
#define COMPANYDATAMODEL_H

#include <QWidget>
#include <QMap>
#include <QAbstractListModel>

class CompanyDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CompanyDataModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;  //返回模型的行数
    QVariant data(const QModelIndex &index, int role) const;    //返回模型的数据项
    //可以在树和表格视图的表头显示一些内容
    QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;
signals:

public slots:

private:
    QMap<QString,float> map;
};

#endif // COMPANYDATAMODEL_H
