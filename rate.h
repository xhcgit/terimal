#ifndef RATE_H
#define RATE_H

#include <QWidget>
#include <QPainter>
#include <QPicture>
#include "Nmea.h"

namespace Ui {
class rate;
}

class rate : public QWidget
{
    Q_OBJECT

public:
    explicit rate(QWidget *parent = 0);
    ~rate();
    double getRate();
public slots:
    void setRate(nmeaGPVTG GPVTG);

private:
    Ui::rate *ui;
    void drawRateDial(QPainter* painter, int L);
    void drawRatePointer(QPainter* painter, int L, double rate);
    double nowRate;    //km/h
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // RATE_H
