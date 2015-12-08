#include "map.h"
#include "ui_map.h"
#include <QPainter>
#include <QPicture>

map::map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::map)
{
    ui->setupUi(this);
    ui->labelLatitudeValue->setText("NULL");
    ui->labelLongitudeValue->setText("NULL");
}

map::~map()
{
    delete ui;
}

void map::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(ui->widget->x(),ui->widget->y(),ui->widget->width(),ui->widget->height(),QPixmap(":/images/map.png"));
    QPen pen;
    pen.setWidth(2);    //设置画笔宽度为2
    painter.setPen(pen);

    traslate(getLongitude(), getFlagLongitude(), getLatitude(), getFlagLatitude());
}

void map::drawPointAndRound(int x, int y, int width = 5)    //绘制一个半径为5的圆，圆心处画一个点
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoint(x, y);
    painter.drawEllipse(QPoint(x, y), width, width);

}

void map::traslate(double Longitude, char flagLongitude, double Latitude, char flagLatitude)    //Longitude , Latitude 为输入的经纬度
{                                                                                               //flagLongitude是东西经标志位，flagLatitude是南北纬标志位
    if(((flagLongitude == 'W')||(flagLongitude == 'E'))&&((flagLatitude == 'N')||(flagLatitude == 'S')))    //当经纬度数据到来时才进行转换
    {
        int H = ui->widget->width();
        int Y = ui->widget->height();
        ui->labelLatitudeValue->setText(QString::number(Latitude) + flagLatitude);
        ui->labelLongitudeValue->setText(QString::number(Longitude) + flagLongitude);
        if (flagLongitude == 'E')
            Longitude = 180 + Longitude;
        else if (flagLongitude == 'W')
            Longitude =  180 - Longitude;
        if (flagLatitude == 'N')
            Latitude = 90 - Latitude;
        else if (flagLatitude == 'S')
            Latitude = 90 + Latitude;

        Longitude = (Longitude * H) / 360;
        Latitude = (Latitude * Y) / 180 ;
        drawPointAndRound(Longitude , Latitude);
    }
}

void map::setLonAndnLat(nmeaGPGGA GPGGA)    //与主窗口的接口
{
    setLongitude(GPGGA.lon);
    setLatitude(GPGGA.lat);
    setFlagLongitude(GPGGA.ew);
    setFlagLatitude(GPGGA.ns);
    map::update();
}

void map::setLongitude(double Lon)
{
    Longitude = Lon;
}

void map::setLatitude(double Lat)
{
    Latitude = Lat;
}

void map::setFlagLongitude(char flagLon)
{
    flagLongitude = flagLon;
}

void map::setFlagLatitude(char flagLat)
{
    flagLatitude = flagLat;
}

double map::getLongitude()    //获取经度
{
    return Longitude;
}

double map::getLatitude()    //获取纬度
{
    return Latitude;
}
char map::getFlagLongitude()    //获取经度标志
{
    return flagLongitude;
}

char map::getFlagLatitude()    //获取纬度标志
{
    return flagLatitude;
}
