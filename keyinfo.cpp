#include "keyinfo.h"
#include "adbpath.h"

KeyInfo::KeyInfo()
{
    connect(this->mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(KeyInfoStdOut()));
    connect(this->mProcess, SIGNAL(readyReadStandardError()), this, SLOT(KeyInfoStdErr()));

}

void KeyInfo::StartCmd()
{
    QStringList options;
    options << "shell";
    options << "getevent -l";

    this->ExeCmd(GetAdbPath(), options);
}


void KeyInfo::KeyInfoStdOut()
{
    QString data,tmp;
    QString str_start = "/dev/input/event1: EV_KEY       ";
    QString key_start = "KEY_";

    while (this->mProcess->canReadLine()) {
        data = this->mProcess->readLine();
        if(data.contains(" UP"))
        {
            tmp = data.mid(str_start.size()).simplified().trimmed().remove(key_start);
            qDebug() << "str:" << tmp;
            if(tmp.contains("POWER")) {
                emit onKeyPress(KEYPRESS_PWR);
            } else if(tmp.contains("VOLUMEUP")) {
                emit onKeyPress(KEYPRESS_VUP);
            } else if(tmp.contains("VOLUMEDOWN")) {
                emit onKeyPress(KEYPRESS_VDOWN);
            }
        }
    }
}

void KeyInfo::KeyInfoStdErr()
{

}

