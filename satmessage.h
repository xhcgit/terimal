#ifndef SATMESSAGE_H
#define SATMESSAGE_H

#include "Nmea.h"
#include <QVector>


class satMessage : public QObject
{
    Q_OBJECT
public:
    satMessage();
    ~satMessage();
    void clearBox();

public:
    GPSWorkMode type;    //卫星类型
    QVector<int> satelliteNum;    //卫星号
    QVector<int> elevation;    //仰角
    QVector<int> azimuth;    //方位角
    QVector<int> snr;    //信噪比
    QVector<bool> locateFlag;    //卫星是否用来定位

public slots:
    void setGpsSatMessage(nmeaGPGSA GPGSA, QVector<nmeaGPGSV> GPGSV);
    void setBdSatMessage(nmeaGPGSA BDGSA, QVector<nmeaGPGSV> BDGSV);

signals:
    void sendGpsSatMessage(QVector<int> satelliteNum, QVector<int> elevation,
                           QVector<int> azimuth, QVector<int> snr, QVector<bool> locateFlag);
    void sendBdSatMessage(QVector<int> satelliteNum, QVector<int> elevation,
                          QVector<int> azimuth, QVector<int> snr, QVector<bool> locateFlag);
};

#endif // SATMESSAGE_H
