#ifndef UTCTIME_H
#define UTCTIME_H

#include <QWidget>
#include <QPainter>
#include <QPicture>
#include "Nmea.h"

namespace Ui {
class utcTime;
}

class utcTime : public QWidget
{
    Q_OBJECT

public:
    explicit utcTime(QWidget *parent = 0);
    ~utcTime();

    void setSecond(int secondValue);
    void setMinute(int minuteValue);
    void setHour(int hourValue);
    int getSecond();
    int getMinute();
    int getHour();

public slots:
    void setDataValue(nmeaGPRMC GPRMC);

private:
    void drawTimeDial(QPainter* painter);
    void drawSecPointer(QPainter* painter);
    void drawminPointer(QPainter* painter);
    void drawhourPointer(QPainter* painter);
    Ui::utcTime *ui;
    int second;
    int minute;
    int hour;
    int standLen;
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // UTCTIME_H
