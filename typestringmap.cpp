#include "typestringmap.h"
#include <QFile>
TypeStringMap::TypeStringMap(QObject *parent) : QObject(parent)
{
    setting = new QSettings("./typestringmap.ini",QSettings::IniFormat,this);
    setting->setIniCodec("UTF-8");
    if(!QFile("./typestringmap.ini").exists())
    {
        init();
    }
}

void TypeStringMap::init()
{
    setting->setValue("jueyuanzi","绝缘子");
    setting->setValue("daodixian","导地线");
    setting->setValue("xianjia","线夹、均压环");
    setting->setValue("fangzhenchui","防震锤");
    setting->setValue("xiaojingju","细小金具");
    setting->setValue("jichu","基础");
    setting->setValue("fushusheshi","附属设施");
    setting->setValue("yiwu","异物");
}

QString TypeStringMap::Name(const QString &id)
{
    return setting->value(id).toString();
}
