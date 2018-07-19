#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "resultdialog.h"
#include <QAction>
#include "evaluatetask.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void initUI();
    void SaveandShow();
signals:
    void txt(const QString& txt);
public slots:
    void showResultDialog();
    void onXmlEditChanged(const QString& txt);
    void onResultEditChanged(const QString& txt);
    void onXmlEditClicked();
    void onResultEditClicked();
    void onStartBtn();


private:
    Ui::Widget *ui;
    ResultDialog *resultdialog;
    EvaluateTask *task;

    QString valueiou;

    QString company;
    QString currenttype;
    QString inputresulttxt;
    QString xmlpath;
};



#endif // WIDGET_H
