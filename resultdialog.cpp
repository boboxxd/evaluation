#include "resultdialog.h"
#include "ui_resultdialog.h"
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <QMessageBox>
#include <QDir>
#include "resultpraser.h"
ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
}

ResultDialog::~ResultDialog()
{
    qDebug()<<"ResultDialog deleted!";
    delete ui;
}

void ResultDialog::initUI()
{
    map = new CompanyStringMap(this);
    typemap =new TypeStringMap(this);
    setWindowTitle(QString("%1--%2 识别结果").arg(map->Name(companyname)).arg(typemap->Name(type)));
    ui->companyNameLabel->setText(QString("%1--%2 识别结果").arg(map->Name(companyname)).arg(typemap->Name(type)));
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("评分时间：yyyy-MM-dd hh:mm:ss dddd");
    ui->timelabel->setText(str);

    fillresult(QString("./%1_%2_result_%3_result.ini").arg(companyname).arg(type).arg(type));

}

void ResultDialog::fillresult(const QString &file)
{
    ResultPraser *parser = new ResultPraser(file);
    ui->apedit->setText(parser->getAp());
    ui->redit->setText(parser->getR());
    ui->pedit->setText(parser->getP());
    ui->iouedit->setText(parser->getIOU());
    ui->missedit->setText(parser->getMissRate());
    ui->erroredit->setText(parser->getErrorRate());
    ui->valueedit->setText(parser->getScore());
}

void ResultDialog::grapScreen(const QString &filename,QPixmap pix)
{


    if(!pix.save(filename,"png"))
    {
        qDebug()<<"save widget screen failed";
    }
}

void ResultDialog::grapPNG()
{
    QDir dir(map->Name(companyname));
    if(!dir.exists())
    {
        dir.mkpath(map->Name(companyname)+"/output/");
    }

    fillresult(QString("./%1_%2_result_%3_result.ini").arg(companyname).arg(type).arg(type));
update();
    pngpath = map->Name(companyname)+"/"+map->Name(companyname)+tr("/output/");
    pngpath += map->Name(companyname)+"_"+typemap->Name(type);
    pngpath += "评分结果.png";
    qDebug()<<"filePath"<<pngpath;
    QPixmap p = this->grab(this->rect());
    grapScreen(pngpath,p);
}

void ResultDialog::showResultPNG()
{
    if(QFile(pngpath).exists())
    {
        static QLabel  label;
        label.setWindowTitle(QString("%1--%2 识别结果").arg(map->Name(companyname)).arg(typemap->Name(type)));
        label.setPixmap(QPixmap(pngpath).scaled(this->width(),this->height(),Qt::KeepAspectRatio));
        label.show();
    }else{
        QMessageBox::information(NULL, tr("提示"), tr("目前还没结果生成，请先开始评分！"), QMessageBox::Yes);
    }
}

void ResultDialog::onrecieveResulttxtname(const QString &txt)
{
    resultfilename = txt;
    if(!resultfilename.isEmpty())
    {
        QString tmptxt=QFileInfo(resultfilename).baseName();
        companyname = tmptxt.split('_')[0];
        type = tmptxt.split('_')[1];
        initUI();
    }
}
