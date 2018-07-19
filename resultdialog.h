#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include "companystringmap.h"
#include "typestringmap.h"
namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = 0);
    ~ResultDialog();
    void initUI();
    void fillresult(const QString& file);
    void grapScreen(const QString &filename,QPixmap pix);
    void grapPNG();
    void showResultPNG();
public slots:
   void onrecieveResulttxtname(const QString&);
private:
    Ui::ResultDialog *ui;
    QString resultfilename;
    QString companyname;
    QString type;
    CompanyStringMap *map;
    TypeStringMap *typemap;
    QString pngpath;
};

#endif // RESULTDIALOG_H
