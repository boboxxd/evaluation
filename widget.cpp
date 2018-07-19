#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <companydatamodel.h>
#include <QTimer>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <QThread>
void generategtPath(const QString& gtpath)
{
    QFile f("gtxml.txt");
    if(f.exists())
        f.remove();
    qDebug()<<"gtxml.txt"<<f.exists();
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream txtOutput(&f);

    QDir dir(gtpath);
    QStringList filter;
    filter<<"*.xml";
    QStringList xmllist=dir.entryList(filter);
    for(auto i=xmllist.begin();i!=xmllist.end();i++)
    {
        txtOutput<<QFileInfo(*i).baseName()<<'\n';
    }

    f.close();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    resultdialog = new ResultDialog();
    valueiou = "";
    company = "";
    currenttype = "";
    inputresulttxt = "";
    xmlpath = "";
    initUI();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUI()
{
    //setFixedSize(990, 648);
    ui->xmlEdit->setPlaceholderText(tr("标定文件目录"));
    ui->resultEdit->setPlaceholderText(tr("厂家结果文件"));
    CompanyDataModel *model=new CompanyDataModel(this);
    ui->typecomboBox->setModel(model);
    connect(ui->showReultBtn,&QPushButton::clicked,this,&Widget::showResultDialog);
    connect(ui->xmlBtn,&QPushButton::clicked,this,&Widget::onXmlEditClicked);
    connect(ui->resultBtn,&QPushButton::clicked,this,&Widget::onResultEditClicked);
    connect(ui->xmlEdit,&QLineEdit::textChanged,this,&Widget::onXmlEditChanged);
    connect(ui->resultEdit,&QLineEdit::textChanged,this,&Widget::onResultEditChanged);
    QLineEdit *iouedit =ui->ioulineEdit;
    connect(ui->typecomboBox->view(),&QAbstractItemView::pressed,\
            [this,iouedit,model](QModelIndex index){\
        valueiou = QString("%1").arg(model->data(index,Qt::UserRole).toFloat());\
        iouedit->setText(valueiou);\
        currenttype = model->data(index,Qt::DisplayRole).toString();\
    });
    connect(ui->startBtn,&QPushButton::clicked,this,&Widget::onStartBtn);
connect(this,&Widget::txt,this->resultdialog,&ResultDialog::onrecieveResulttxtname);
}



void Widget::showResultDialog()
{
    if(inputresulttxt.isEmpty())
    {
        QMessageBox::information(NULL, tr("提示"), tr("请先填写必要信息，注意格式！"), QMessageBox::Yes);
        return;
    }

    emit txt(inputresulttxt);
    resultdialog->showResultPNG();
    //resultdialog->exec();
}

void Widget::onXmlEditChanged(const QString& txt)
{
    setToolTip(txt);
}

void Widget::onResultEditChanged(const QString& txt)
{
    setToolTip(txt);

}

void Widget::onXmlEditClicked()
{
    xmlpath = QFileDialog::getExistingDirectory(this,tr("打开目录"),"");
    ui->xmlEdit->setText(xmlpath);

    //生成gt_path
    ui->textBrowser->append(QString("生成预标定的xml文件列表:%1").arg(xmlpath));
    generategtPath(xmlpath);
}

void Widget::onResultEditClicked()
{
    inputresulttxt = QFileDialog::getOpenFileName(this, tr("打开文件"), " ",  tr("*.txt"));
    ui->resultEdit->setText(inputresulttxt);
    if(!inputresulttxt.isEmpty())
    {
        QString tmptxt=QFileInfo(inputresulttxt).baseName();
        company = tmptxt.split('_')[0];
        currenttype = tmptxt.split('_')[1];
    }
    ui->textBrowser->append(QString("已导入厂商结果文件：%1").arg(inputresulttxt));
}

void Widget::onStartBtn()
{
    qDebug()<<"onStartBtn()";
    ui->textBrowser->append(QString("开始分析..."));
    if(inputresulttxt.isEmpty())
    {
        QMessageBox::information(NULL, tr("提示"), tr("请先填写必要信息，注意格式！"), QMessageBox::Yes);
        return;
    }
    emit txt(inputresulttxt);

  //----------------------------------------------------------
    qDebug()<<qApp->applicationDirPath();
   qDebug()<< "py exit"<<QFile ("evaluation/eval_recall_precision.py").exists();
    QStringList argvlist;
    argvlist<<"evaluation/eval_recall_precision.py"<<\
              "--result_list"<<inputresulttxt<<\
              "--iou_thres"<<valueiou<<\
              "--conf_thresh"<<QString("0.01")<<\
              "--gt_path"<<"gtxml.txt"<<\
              "--image_dir"<<xmlpath<<\
              "--type"<<currenttype;

    task = new EvaluateTask(argvlist,this);
    task->run();
    QThread::sleep(1);
    SaveandShow();

    delete task;

  //----------------------------------------------------------
}

void Widget::SaveandShow()
{

    //if(task->isFinished()){
        ui->textBrowser->append(QString("分析结束."));
        ui->textBrowser->append(QString("保存结果..."));
        ui->textBrowser->append(QString("---------------------------------------------------"));
        resultdialog->grapPNG();
        resultdialog->exec();
   // }

}


