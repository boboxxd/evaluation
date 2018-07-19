#include "companystringmap.h"
#include <QFile>
CompanyStringMap::CompanyStringMap(QObject *parent) : QObject(parent)
{
    setting = new QSettings("./companystringmap.ini",QSettings::IniFormat,this);
    setting->setIniCodec("UTF-8");
    if(!QFile("./companystringmap.ini").exists())
    {
        init();
    }
}

CompanyStringMap::~CompanyStringMap()
{
    delete setting;
}

void CompanyStringMap::init()
{
    for(int i=0;i<5;i++)
    {
        setting->setValue(QString("ID%1/NAME").arg(i),"");
    }
}

QString CompanyStringMap::Name(const QString& id)
{
    return setting->value(id+"/NAME").toString();
}

