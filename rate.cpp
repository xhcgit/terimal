#include "rate.h"
#include "ui_rate.h"

rate::rate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rate)
{
    ui->setupUi(this);
}

rate::~rate()
{
    delete ui;
}

void rate::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    double rateKm;
    double rateM;
    painter.fillRect(0, 0, width(), height(),Qt::black);
    int L;
    if(width()<height())
        L = width();
    else
        L = height();
    drawRateDial(&painter, L);
    drawRatePointer(&painter, L, getRate());

    rateKm = nowRate;
    rateM = rateKm/3.6;    //km/h转为m/s需要除以3.6
    ui->label->setText(QString::number(rateM).mid(0, 4) + "m/s = " + QString::number(rateKm).mid(0, 5) + "km/h");
}

/**
 * @brief rate::drawRateDial    绘制速度表盘
 * @param painter L为窗口长宽中较小的值
 * @param NULL
 */
void rate::drawRateDial(QPainter* painter, int L)
{
    QPen pen;
    int i;
    pen.setWidth(2);
    pen.setColor(Qt::white);
    painter->setPen(pen);

    painter->translate(width()/2, height()/2);    //设置偏移位置为窗口中心
    painter->rotate(+30.0);    //设置偏移角度为30度(0刻度线位置)
    painter->drawLine(0, 0.208*L, 0, 0.208*L+0.125*L);    //表盘上长的刻度线


    for(i = 0; i < 5; i++)    //再画5条长刻度线
    {
        painter->rotate(+60.0);    //每条长刻度线偏移角度为60度
        painter->drawLine(0,0.208*L,0,0.208*L+0.125*L);
    }

    for(i = 0;i<5;i++)    //恢复偏移角度
        painter->rotate(-60);

    pen.setWidth(1);
    painter->setPen(pen);

    painter->drawLine(0, 0.208*L, 0 , 0.208*L+0.067*L);    //表盘上短的刻度线
    for(i = 0; i < 25; i++)    //再画25条短刻度线
    {
        painter->rotate(+12);
        painter->drawLine(0, 0.208*L, 0 , 0.208*L+0.067*L);
    }

    for(i = 0; i < 25; i++)
        painter->rotate(-12);

    pen.setWidth(0.04*L);    //绘制表盘中心的圆
    painter->setPen(pen);
    painter->drawEllipse(QPoint(0,0), 0.06*L, 0.06*L);

    painter->rotate(-30);    //恢复偏移角度
    //绘制表盘刻度
    painter->drawText(-0.2*L, 0.35*L, "0");
    painter->drawText(-0.4*L, 0, "50");
    painter->drawText(-0.2*L, -0.35*L, "100");
    painter->drawText(0.2*L, -0.35*L, "150");
    painter->drawText(0.4*L, 0, "200");
    painter->drawText(0.2*L, 0.35*L, "250");


    painter->translate(-(width()/2), -(height()/2));    //恢复偏移位置

    pen.setWidth(1);    //恢复画笔宽度
    painter->setPen(pen);

}

void rate::drawRatePointer(QPainter* painter, int L, double rate)    //绘制表盘指针
{
    QPen pen;
    double angel;
    angel = (rate/250)*300;
    pen.setWidth(4);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->translate(width()/2, height()/2);    //定位到窗口中心
    painter->rotate(30+angel);    //将指针定位至0刻度线处

    painter->drawLine(0, 0, 0, 0.3*L);
}

void rate::setRate(nmeaGPVTG GPVTG)
{
    nowRate = GPVTG.spk;
    rate::update();
}

double rate::getRate()
{
    return nowRate;
}

