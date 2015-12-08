#ifndef POSITION_H
#define POSITION_H

#include <QWidget>
#include <QPainter>
#include "Nmea.h"
#include "satmessage.h"

namespace Ui {
class position;
}

class position : public QWidget
{
    Q_OBJECT

public:
    explicit position(QWidget *parent = 0);
    ~position();

private:
    void drawDial(QPainter* painter);
    void drawsatellites(QPainter *painter, int satelliteNum, double elevation, double azimuth, QColor color, GPSWorkMode type);
    satMessage gpsMessage;
    satMessage bdMessage;
    Ui::position *ui;
    int standLen;
protected:
    void paintEvent(QPaintEvent *event);
public slots:
    void recGpsSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate);
    void recBdSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate);
};

#endif // POSITION_H
