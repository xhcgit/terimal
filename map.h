#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include "Nmea.h"

namespace Ui {
class map;
}

class map : public QWidget
{
    Q_OBJECT

public:
    explicit map(QWidget *parent = 0);
    ~map();
    void drawPointAndRound(int x, int y, int width);
    void traslate(double Longitude, char flagLongitude, double Latitude, char flagLatitude);    //坐标转换

    void setLongitude(double Lon);    //设置经度
    void setLatitude(double Lat);    //设置纬度
    void setFlagLongitude(char flagLon);    //设置经度标志
    void setFlagLatitude(char flagLat);    //设置纬度标志

    double getLongitude();    //获取经度
    double getLatitude();    //获取纬度
    char getFlagLongitude();    //获取经度标志
    char getFlagLatitude();    //获取纬度标志
private:
    Ui::map *ui;
    double Longitude;    //经度
    char flagLongitude;    //经度标志
    double Latitude;    //纬度
    char flagLatitude;    //纬度标志
public slots:
    void setLonAndnLat(nmeaGPGGA GPGGA);    //设置经纬度
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MAP_H
