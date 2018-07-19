#ifndef TYPESTRINGMAP_H
#define TYPESTRINGMAP_H

#include <QObject>
#include <QSettings>
class TypeStringMap : public QObject
{
    Q_OBJECT
public:
    explicit TypeStringMap(QObject *parent = nullptr);
    void init();
    QString Name(const QString &id);
signals:

public slots:
private:
    QSettings *setting;
};

#endif // TYPESTRINGMAP_H
