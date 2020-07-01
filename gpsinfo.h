#ifndef GPSINFO_H
#define GPSINFO_H
#include "baseprocess.h"

class GpsData
{
public:
    QString status;//Status, V = Navigation receiver warning, A = Data valid,
    QString lat;//Latitude (degrees & minutes),
    QString ns;//North/South indicator
    QString lng;//Longitude (degrees & minutes),
    QString ew;//East/West indicator
};

class GpsInfo : public BaseProcess
{

    Q_OBJECT
public:
    GpsInfo();
    ~GpsInfo();
    void StartCmd();

private:
    GpsData *gps;
//    QString mAdbPath;

private slots:
    void GpsInfoStdOut();
    void GpsInfoStdErr();

signals:
    void onHaveGpsInfo(GpsData *data, QString str);

//public slots:
//    void AdbPathChanged(QString path);
};

#endif // GPSINFO_H
