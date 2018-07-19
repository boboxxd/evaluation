#ifndef COMPANYSTRINGMAP_H
#define COMPANYSTRINGMAP_H

#include <QObject>
#include <QSettings>

class CompanyStringMap : public QObject
{
    Q_OBJECT
public: 
    CompanyStringMap(QObject *parent = nullptr);
    ~CompanyStringMap();
    void init();
    QString Name(const QString& id);
signals:

public slots:
protected:

private:
    QSettings *setting;
    static CompanyStringMap *map;
};

#endif // COMPANYSTRINGMAP_H
