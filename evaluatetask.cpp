#include "evaluatetask.h"
#include <QDebug>
EvaluateTask::EvaluateTask(QStringList list,QObject *parent)
    :m_arglist(list),QObject(parent)
{
    process =new QProcess(this);
    isfinished =false;
    connect(process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),this,&EvaluateTask::Finished);
}

EvaluateTask::~EvaluateTask()
{
    delete process;
}

void EvaluateTask::run()
{
    qDebug()<<"task run";
    process->start("./Python27/python",m_arglist);
}

bool EvaluateTask::isFinished()
{

        return isfinished;
}

void EvaluateTask::Finished(int exitcode, QProcess::ExitStatus status)
{
    qDebug()<<"EvaluateTask::Finished";
    isfinished = true;
}
