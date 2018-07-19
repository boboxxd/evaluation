#include "resultpraser.h"
#include "QMessageBox"
#include <QFile>
ResultPraser::ResultPraser(const QString& filename,QObject *parent) : QObject(parent)
{
    setting = new QSettings(filename,QSettings::IniFormat,this);
    setting->setIniCodec("UTF-8");
    if(!QFile(filename).exists())
    {
        //QMessageBox::information(NULL, tr("提示"), QString("未找到%1").arg(filename), QMessageBox::Yes);
        return;
    }
}

ResultPraser::~ResultPraser()
{
    delete setting;
}

QString ResultPraser::getAp()
{
    return setting->value("AP").toString();
}

QString ResultPraser::getR()
{
    return setting->value("R").toString();
}

QString  ResultPraser::getP()
{
    return setting->value("P").toString();
}

QString ResultPraser::getIOU()
{
    return setting->value("IoU").toString();
}

QString ResultPraser::getMissRate()
{
    return setting->value("miss_rate").toString();
}

QString ResultPraser::getErrorRate()
{
    return setting->value("error_rate").toString();
}

QString ResultPraser::getScore()
{
    return setting->value("score").toString();
}
