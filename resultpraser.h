#ifndef RESULTPRASER_H
#define RESULTPRASER_H

#include <QObject>
#include <QSettings>
class ResultPraser : public QObject
{
    Q_OBJECT
public:
    explicit ResultPraser(const QString& filename,QObject *parent = nullptr);
    ~ResultPraser();
signals:

public slots:
public:
    QString getAp();
    QString getR();
    QString  getP();
    QString getIOU();
    QString getMissRate();
    QString getErrorRate();
    QString getScore();
private:
    QSettings *setting;

};

#endif // RESULTPRASER_H
