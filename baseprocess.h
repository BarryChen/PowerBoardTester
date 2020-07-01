#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QProcess>
#include <QDebug>

class BaseProcess : public QObject
{
    Q_OBJECT
public:
    BaseProcess();
    ~BaseProcess();

    QProcess *mProcess;
    void ExeCmd(QString cmdline, QStringList opt);
    void StopCmd();

signals:
    void onExeCmdError();

private:
    void killProcess();

};

#endif // PROCESS_H
