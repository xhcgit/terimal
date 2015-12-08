#ifndef SATELLITEDATA_H
#define SATELLITEDATA_H

#include <QWidget>
#include <QLabel>
#include "Nmea.h"
#include "satmessage.h"

namespace Ui {
class satelliteData;
}

class satelliteData : public QWidget
{
    Q_OBJECT

public:
    explicit satelliteData(QWidget *parent = 0);
    ~satelliteData();

private:
    Ui::satelliteData *ui;
    QVector<QLabel*> labelAll;
    satMessage gpsMessage;
    satMessage bdMessage;
    void initLabel();
    void updateLabel();
public slots:
    void recGga(const nmeaGPGGA &GGA);
    void recGSA(const nmeaGPGSA &GPGSA, const nmeaGPGSA &BDGSA);
    void recGpsSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate);
    void recBdSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate);
};

#endif // SATELLITEDATA_H
