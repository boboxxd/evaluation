#ifndef EVALUATETASK_H
#define EVALUATETASK_H

#include <QObject>
#include <QProcess>
class EvaluateTask : public QObject
{
    Q_OBJECT
public:
    explicit EvaluateTask(QStringList list,QObject *parent = nullptr);
    ~EvaluateTask();
    void run();
    bool isFinished();
signals:
public slots:
    void Finished(int exitcode,QProcess::ExitStatus status);
private:
    QStringList  m_arglist;
    QProcess *process;
    bool isfinished;
};

#endif // EVALUATETASK_H
