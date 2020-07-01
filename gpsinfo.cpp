#include "gpsinfo.h"
#include "adbpath.h"

GpsInfo::GpsInfo()
{
    this->gps = new GpsData;
    connect(this->mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(GpsInfoStdOut()));
    connect(this->mProcess, SIGNAL(readyReadStandardError()), this, SLOT(GpsInfoStdErr()));
    //StartCmd();
}
GpsInfo::~GpsInfo()
{
    if(this->gps != nullptr)
    {
        delete this->gps;
    }
    this->gps = nullptr;
}

void GpsInfo::StartCmd()
{
    QStringList options_gps;
    options_gps << "logcat";
    options_gps << "-s";
    options_gps << "u-blox";

    this->ExeCmd(GetAdbPath(), options_gps);
}


void GpsInfo::GpsInfoStdOut()
{
    QString data,str;
    QStringList list;

    int tmp;
    while (this->mProcess->canReadLine()) {
        data = this->mProcess->readLine();
        //qDebug() << data;

        if(data.contains("RMC"))
        {
            tmp = data.indexOf("RMC,");
            str=data.mid(tmp);
            qDebug() << "str" << str;
            list = str.split(',');
            if(list.isEmpty() || list.length() < 6)
                continue;
            //qDebug() << "str" << list << "gps->status:" << list.length();
            this->gps->status = list[2];
            this->gps->lat = list[3];
            this->gps->ew = list[4];
            this->gps->lng = list[5];
            this->gps->ns = list[6];

            emit onHaveGpsInfo(this->gps, str);
        }
    }
}

void GpsInfo::GpsInfoStdErr()
{

}

