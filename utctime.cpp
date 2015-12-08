#include "utctime.h"
#include "ui_utctime.h"

utcTime::utcTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::utcTime)
{
    ui->setupUi(this);
    second = 0;
    minute = 0;
    hour = 0;
}

utcTime::~utcTime()
{
    delete ui;
}

void utcTime::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(),Qt::black);    //将窗口背景涂黑

    painter.setRenderHint(QPainter::Antialiasing, true);

    if(width()<height())
        standLen = width();
    else
        standLen = height();

    drawTimeDial(&painter);    //绘制时间表盘

    drawSecPointer(&painter);
    drawminPointer(&painter);
    drawhourPointer(&painter);

}


/**
 * @brief utcTime::drawRateDial    绘制时间表盘
 * @param painter L为窗口长宽中较小的值
 * @param NULL
 */
void utcTime::drawTimeDial(QPainter* painter)
{
    QPen pen;
    int i;
    pen.setWidth(3);
    pen.setColor(Qt::white);
    painter->setPen(pen);

    painter->translate(width()/2, height()/2);    //设置偏移位置为窗口中心

    for(i = 0; i < 4; i++)    //画4条刻度线，表示(0,3,6,9)小时
    {
        painter->drawLine(0, (6.5/20) * standLen, 0, (9.0/20) * standLen);
        painter->rotate(+90.0);    //每条长刻度线偏移角度为90度
    }

    pen.setWidth(2);
    painter->setPen(pen);

    for(i = 0; i < 12; i++)    //画12条刻度线，代表12小时，与上述线有重合
    {
        painter->drawLine(0, (6.5/20) * standLen, 0, (8.5/20) * standLen);
        painter->rotate(+30.0);
    }

    pen.setWidth(1);
    painter->setPen(pen);

    for(i = 0; i < 60; i++)    //画60条刻度线，代表60分钟，与上述线有重合
    {
        painter->drawLine(0, (6.5/20) * standLen, 0, (7.5/20) * standLen);
        painter->rotate(+6.0);
    }

    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));    //画中间的圆点
    painter->drawEllipse(QPoint(0, 0), (0.5/20)*standLen, (0.5/20)*standLen);

    painter->translate(-(width()/2), -(height()/2));    //恢复偏移位置
    pen.setWidth(1);    //恢复画笔宽度
    painter->setPen(pen);
}

/**
 * @brief utcTime::drawSecPointer 绘制秒针
 * @param painter
 */
void utcTime::drawSecPointer(QPainter* painter)
{
    QPen pen;
    int angel;
    angel = second * 6 + 180;    //一秒钟为6度

    pen.setWidth(1);
    pen.setColor(Qt::white);
    painter->setPen(pen);

    painter->translate(width()/2, height()/2);    //定位到窗口中心
    painter->rotate(angel);
    painter->drawLine(0, -(2.5/20)*standLen, 0, (6.0/20.0)*standLen);

    painter->rotate(-angel);    //恢复偏移量和偏移角度
    painter->translate(-width()/2, -height()/2);
}

/**
 * @brief utcTime::drawminPointer 绘制分针
 * @param painter
 */
void utcTime::drawminPointer(QPainter* painter)
{
    QPen pen;
    int angel;
    angel = minute * 6 + 180;    //一分钟为6度

    pen.setWidth(5);
    pen.setColor(Qt::white);
    painter->setPen(pen);

    painter->translate(width()/2, height()/2);    //定位到窗口中心
    painter->rotate(angel);
    painter->drawLine(0, -(2.0/20)*standLen, 0, (5.5/20.0)*standLen);

    painter->rotate(-angel);    //恢复偏移量和偏移角度
    painter->translate(-width()/2, -height()/2);
}

/**
 * @brief utcTime::drawhourPointer 绘制时针
 * @param painter
 */
void utcTime::drawhourPointer(QPainter* painter)
{
    QPen pen;
    int angel;
    angel = (hour%12) * 30 + 180;    //一小时为30度

    pen.setWidth(5);
    pen.setColor(Qt::white);
    painter->setPen(pen);

    painter->translate(width()/2, height()/2);    //定位到窗口中心
    painter->rotate(angel);
    painter->drawLine(0, -(1.5/20)*standLen, 0, (4.5/20.0)*standLen);

    painter->rotate(-angel);    //恢复偏移量和偏移角度
    painter->translate(-width()/2, -height()/2);
}

/**
 * @brief utcTime::setDataValue 设置时间和日期，接口函数
 *
 * @param GPRMC
 */
void utcTime::setDataValue(nmeaGPRMC GPRMC)
{
    bool ok;
    QString utc = GPRMC.utc;
    QString year;
    QString month;
    QString day;
    QString week;
    QString strHour = utc.mid(0, 2);
    QString strMin = utc.mid(2, 2);
    QString strSec = utc.mid(4, 2);

    setHour(strHour.toInt(&ok));    //根据NMEA格式的UTC时间提取出时分秒
    setMinute(strMin.toInt(&ok));    //格式为hhmmss.ss
    setSecond(strSec.toInt(&ok));

    year = QString::number(GPRMC.utc_date.year());
    month = QString::number(GPRMC.utc_date.month());
    day = QString::number(GPRMC.utc_date.day());
    ui->labelTime->setText(strHour+':'+strMin+':'+strSec);
    switch (GPRMC.utc_date.dayOfWeek())
    {
    case 1:
        week = "Monday";
        break;
    case 2:
        week = "Tuesday";
        break;
    case 3:
        week = "Wednesday";
        break;
    case 4:
        week = "Thursday";
        break;
    case 5:
        week = "Friday";
        break;
    case 6:
        week = "Saturday";
        break;
    case 7:
        week = "Sunday";
        break;
    default:
        break;
    }
    ui->labelWeek->setText(week);
    ui->labelData->setText(month + '/' + day + '/' + year);
    utcTime::update();
}

void utcTime::setSecond(int secondValue)
{
    second = secondValue;
}

void utcTime::setMinute(int minuteValue)
{
    minute = minuteValue;
}

void utcTime::setHour(int hourValue)
{
    hour = hourValue;
}

int utcTime::getSecond()
{
    return second;
}

int utcTime::getMinute()
{
    return minute;
}

int utcTime::getHour()
{
    return hour;
}
