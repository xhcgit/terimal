#include "position.h"
#include "ui_position.h"
#include <QtMath>
position::position(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::position)
{
    ui->setupUi(this);

}

position::~position()
{
    delete ui;
}


void position::drawDial(QPainter *painter)    //绘制表盘
{
    QPen pen;
    pen.setColor(Qt::white);
    painter->setPen(pen);

    painter->translate(width()/2, height()/2);    //设置偏移位置为窗口中心


    painter->drawEllipse(QPoint(0, 0), (6.3/28.0)*standLen, (6.3/28.0)*standLen);

    painter->drawEllipse(QPoint(0, 0), (6.3/14.0)*standLen, (6.3/14.0)*standLen);

    //painter->setFont(5);
    painter->drawText(0, (-6.5/14.0)*standLen, "N");
    painter->drawText(0, (6.7/14.0)*standLen, "S");
    painter->drawText((-6.7/14.0)*standLen, 0, "W");
    painter->drawText((6.5/14.0)*standLen, 0, "E");

    painter->translate(-width()/2, -height()/2);     //恢复偏移
}

void position::drawsatellites(QPainter *painter, int satelliteNum, double elevation, double azimuth, QColor color, GPSWorkMode type)    //绘制卫星
{
    double l;
    double x;    //偏移坐标(x,y)
    double y;
    QPen pen;
    QPixmap pix;
    QString satName;

    if(type == GPS)
    {
        if(satelliteNum == 193)
            satName = 'Q' + QString::number(satelliteNum);
        else
            satName = 'G' + QString::number(satelliteNum);
    }
    else if(type == BD)
    {
        satName = 'B' + QString::number(satelliteNum);
    }

    painter->translate(width()/2, height()/2);

    l = (6.3/14.0) * standLen * qCos((elevation/180.0)*M_PI);
    if(l != 0)
    {
        x = l * qSin((azimuth/180.0)*M_PI);
        y = -l * qCos((azimuth/180.0)*M_PI);
        painter->translate(x, y);
    }
    else
    {
        painter->translate(0, (6.3/14.0) * standLen);
        painter->rotate(azimuth);
    }


    if(type == GPS)
    {
        if(satelliteNum == 193)
            pix.load(":/images/Japan.jpg");
        else
            pix.load(":/images/USA.png");
    }
    else if(type == BD)
        pix.load(":/images/China.png");

    pen.setWidth(2);
    painter->setBrush(QBrush(color, Qt::SolidPattern));
    pen.setColor(color);

    painter->setPen(pen);

//    if(standLen < 300)
//        standLen = 300;

    painter->drawPixmap((-0.35/20.0)*standLen, (-0.75/20.0)*standLen, (0.7/20.0)*standLen,(0.4/20.0)*standLen, pix);
    painter->drawEllipse(QPoint(0, 0), (1.1/40.0)*standLen, (0.7/40.0)*standLen);
    painter->drawLine((-0.75/20.0)*standLen, 0, (0.75/20)*standLen, 0);
    painter->drawLine((-0.75/20.0)*standLen, (-0.4/20.0)*standLen,  (-0.75/20.0)*standLen, (0.4/20.0)*standLen);
    painter->drawLine((0.75/20.0)*standLen, (-0.4/20.0)*standLen,  (0.75/20.0)*standLen, (0.4/20.0)*standLen);

    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->drawText((-0.2/20.0)*standLen,0,satName);

    //恢复偏移
    if(l != 0)
    {
        painter->translate(-x, -y);
    }
    else
    {
        painter->translate(0, -(6.3/14.0) * standLen);
        painter->rotate(-azimuth);
    }
    painter->translate(-width()/2, -height()/2);
}


void position::paintEvent(QPaintEvent *event)
{
    int i ;
    QPainter *painter = new QPainter(this);
    painter->fillRect(0, 0, width(), height(),Qt::black);    //将窗口背景涂黑

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(width()<height())
        standLen = width();
    else
        standLen = height();

    drawDial(painter);    //绘制时间表盘
    for(i = 0; i < gpsMessage.satelliteNum.size(); i++ )
    {
        QColor color;
        if(gpsMessage.locateFlag.at(i) == true)
            color = Qt::green;
        else if((gpsMessage.locateFlag.at(i) == false)&&(gpsMessage.snr.at(i) != 0))
            color = Qt::blue;
        else
            color = Qt::red;
        drawsatellites(painter,
                       gpsMessage.satelliteNum.at(i),
                       gpsMessage.elevation.at(i),
                       gpsMessage.azimuth.at(i),
                       color,
                       gpsMessage.type);
    }

    for(i = 0; i < bdMessage.satelliteNum.size(); i++ )
    {
        QColor color;
        if(bdMessage.locateFlag.at(i) == true)
            color = Qt::green;
        else if((bdMessage.locateFlag.at(i) == false)&&(bdMessage.snr.at(i) != 0))
            color = Qt::blue;
        else
            color = Qt::red;
        drawsatellites(painter,
                       bdMessage.satelliteNum.at(i),
                       bdMessage.elevation.at(i),
                       bdMessage.azimuth.at(i),
                       color,
                       bdMessage.type);
    }
    delete painter;
    painter = NULL;
}

void position::recGpsSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate)
{
    gpsMessage.type = GPS;
    gpsMessage.satelliteNum = satNum;
    gpsMessage.elevation = ele;
    gpsMessage.azimuth = azi;
    gpsMessage.snr = sig;
    gpsMessage.locateFlag = locate;
    update();
}

void position::recBdSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate)
{
    bdMessage.type = BD;
    bdMessage.satelliteNum = satNum;
    bdMessage.elevation = ele;
    bdMessage.azimuth = azi;
    bdMessage.snr = sig;
    bdMessage.locateFlag = locate;
    update();
}



