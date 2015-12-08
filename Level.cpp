#include "Level.h"
#include "ui_Level.h"

level::level(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::level)
{
    ui->setupUi(this);\
    maxDb = 50;
    initWidgetEvent();
    initLabel();

}

level::~level()
{
    delete ui;
}

void level::initWidgetEvent()
{
    ui->widget_1->installEventFilter(this);
    ui->widget_2->installEventFilter(this);
    ui->widget_3->installEventFilter(this);
    ui->widget_4->installEventFilter(this);
    ui->widget_5->installEventFilter(this);
    ui->widget_6->installEventFilter(this);
    ui->widget_7->installEventFilter(this);
    ui->widget_8->installEventFilter(this);
    ui->widget_9->installEventFilter(this);
    ui->widget_10->installEventFilter(this);
    ui->widget_11->installEventFilter(this);
    ui->widget_12->installEventFilter(this);
    ui->widget_13->installEventFilter(this);
    ui->widget_14->installEventFilter(this);
    ui->widget_15->installEventFilter(this);
    ui->widget_16->installEventFilter(this);
    ui->widget_17->installEventFilter(this);
    ui->widget_18->installEventFilter(this);
    ui->widget_19->installEventFilter(this);
    ui->widget_20->installEventFilter(this);
    ui->widget_21->installEventFilter(this);
    ui->widget_22->installEventFilter(this);
    ui->widget_23->installEventFilter(this);
    ui->widget_24->installEventFilter(this);
    ui->widget_25->installEventFilter(this);
    ui->widget_26->installEventFilter(this);
    ui->widget_27->installEventFilter(this);
    ui->widget_28->installEventFilter(this);
    ui->widget_29->installEventFilter(this);
    ui->widget_30->installEventFilter(this);
    ui->widget_31->installEventFilter(this);
    ui->widget_32->installEventFilter(this);
    ui->widgetUpCoor->installEventFilter(this);
    ui->widgetDownCoor->installEventFilter(this);
}

void level::paintEvent(QPaintEvent *event)
{

}

bool level::eventFilter(QObject *watched, QEvent *e)
{
    if (watched == ui->widget_1)
    {
        if (e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_1, 1);
            return true;
        }
    }
    else if(watched == ui->widget_2)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_2, 2);
            return true;
        }
    }
    else if(watched == ui->widget_3)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_3, 3);
            return true;
        }
    }
    else if(watched == ui->widget_4)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_4, 4);
            return true;
        }
    }
    else if(watched == ui->widget_5)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_5, 5);
            return true;
        }
    }
    else if(watched == ui->widget_6)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_6, 6);
            return true;
        }
    }
    else if(watched == ui->widget_7)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_7, 7);
            return true;
        }
    }
    else if(watched == ui->widget_8)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_8, 8);
            return true;
        }
    }
    else if(watched == ui->widget_9)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_9, 9);
            return true;
        }
    }
    else if(watched == ui->widget_10)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_10, 10);
            return true;
        }
    }
    else if(watched == ui->widget_11)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_11, 11);
            return true;
        }
    }
    else if(watched == ui->widget_12)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_12, 12);
            return true;
        }
    }
    else if(watched == ui->widget_13)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_13, 13);
            return true;
        }
    }
    else if(watched == ui->widget_14)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_14, 14);
            return true;
        }
    }
    else if(watched == ui->widget_15)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_15, 15);
            return true;
        }
    }
    else if(watched == ui->widget_16)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_16, 16);
            return true;
        }
    }
    else if(watched == ui->widget_17)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_17, 17);
            return true;
        }
    }
    else if(watched == ui->widget_18)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_18, 18);
            return true;
        }
    }
    else if(watched == ui->widget_19)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_19, 19);
            return true;
        }
    }
    else if(watched == ui->widget_20)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_20, 20);
            return true;
        }
    }
    else if(watched == ui->widget_21)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_21, 21);
            return true;
        }
    }
    else if(watched == ui->widget_22)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_22, 22);
            return true;
        }
    }
    else if(watched == ui->widget_23)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_23, 23);
            return true;
        }
    }
    else if(watched == ui->widget_24)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_24, 24);
            return true;
        }
    }
    else if(watched == ui->widget_25)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_25, 25);
            return true;
        }
    }
    else if(watched == ui->widget_26)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_26, 26);
            return true;
        }
    }
    else if(watched == ui->widget_27)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_27, 27);
            return true;
        }
    }
    else if(watched == ui->widget_28)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_28, 28);
            return true;
        }
    }
    else if(watched == ui->widget_29)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_29, 29);
            return true;
        }
    }
    else if(watched == ui->widget_30)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_30, 30);
            return true;
        }
    }
    else if(watched == ui->widget_31)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_31, 31);
            return true;
        }
    }
    else if(watched == ui->widget_32)
    {
        if(e->type() == QEvent::Paint)
        {
            paintOnWidget(ui->widget_32, 32);
            return true;
        }
    }
    else if(watched == ui->widgetUpCoor)
    {
        if(e->type() == QEvent::Paint)
        {
            paintCoordinate(ui->widgetUpCoor);
            return true;
        }
    }
    else if(watched == ui->widgetDownCoor)
    {
        if(e->type() == QEvent::Paint)
        {
            paintCoordinate(ui->widgetDownCoor);
            return true;
        }
    }
    return QWidget::eventFilter(watched, e);
}

/**
 * @brief level::paintOnWidget  画表格
 * @param w
 */
void level::paintOnWidget(QWidget *w, int labelIndex)
{
    QPainter painter(w);
    QPen pen;
    QColor color;
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawRect(0,0,w->width(),w->height());

    //画虚线，间隔为10
    int num = (maxDb/10) + 1 ;
    painter.setPen(QPen(Qt::white, 1, Qt::DashLine));    //设置画笔风格
    int space = w->height()/num;    //设置每条线的间隔
    int i ;
    int h = w->height();
    for(i = 1; i < num; i++)
    {
        h -= space;
        painter.drawLine(0, h, w->width(), h);
    }

    //画柱子
    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));     //设置画笔
    if(labelIndex >= 1 && labelIndex <= 16)    //判断上半部和下半部
    {
        int snr;    //信噪比
        double len;    //柱子长度
        if(labelIndex <= gpsMessage.snr.size())    //避免越界
        {
            if(gpsMessage.locateFlag.at(labelIndex - 1) == true)    //由于labelIndex从1开始，所以需要减1
            {
                color = Qt::green;
            }
            else if((gpsMessage.locateFlag.at(labelIndex - 1) == false) && (gpsMessage.snr.at(labelIndex - 1) != 0))
            {
                color = Qt::blue;
            }
            snr = gpsMessage.snr.at(labelIndex -1);
            painter.setBrush(QBrush(color, Qt::SolidPattern));
            len = (snr/10.0) * space;
            painter.drawRect(0, w->height()-len, w->width(), len);

            if(snr != 0)
            {
                painter.setPen(QPen(Qt::black, 2));
                painter.drawText((w->width())/2, w->height(), QString::number(snr));
            }
        }
    }

    else if(labelIndex >= 17 && labelIndex <= 32)    //判断上半部和下半部
    {
        int snr;    //信噪比
        double len;    //柱子长度
        labelIndex -= 16;    //由于属于下半部，需要减去16
        if(labelIndex <= bdMessage.snr.size())    //避免越界
        {
            if(bdMessage.locateFlag.at(labelIndex - 1) == true)    //由于labelIndex从1开始，所以需要减1
            {
                color = Qt::green;
            }
            else if((bdMessage.locateFlag.at(labelIndex - 1) == false) && (bdMessage.snr.at(labelIndex - 1) != 0))
            {
                color = Qt::blue;
            }
            snr = bdMessage.snr.at(labelIndex -1);
            painter.setBrush(QBrush(color, Qt::SolidPattern));
            len = (snr/10.0) * space;
            painter.drawRect(0, w->height()-len, w->width(), len);

            if(snr != 0)
            {
                painter.setPen(QPen(Qt::black, 2));
                painter.drawText((w->width())/2, w->height(), QString::number(snr));
            }
        }
    }
}

/**
 * @brief level::paintCoordinate  画右边坐标
 * @param w
 */
void level::paintCoordinate(QWidget *w)
{
    int min = 0;
    int num = (maxDb/10) + 1;
    int space = w->height()/num;
    int i;
    int h = w->height();
    QPainter painter(w);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);
    for(i = 0; i < num; i++)
    {
        painter.drawText(0, h, QString::number(min) );
        h -= space;
        min += 10;
    }
}

void level::initLabel()
{
    labelAll.append(ui->label_1);
    labelAll.append(ui->label_2);
    labelAll.append(ui->label_3);
    labelAll.append(ui->label_4);
    labelAll.append(ui->label_5);
    labelAll.append(ui->label_6);
    labelAll.append(ui->label_7);
    labelAll.append(ui->label_8);
    labelAll.append(ui->label_9);
    labelAll.append(ui->label_10);
    labelAll.append(ui->label_11);
    labelAll.append(ui->label_12);
    labelAll.append(ui->label_13);
    labelAll.append(ui->label_14);
    labelAll.append(ui->label_15);
    labelAll.append(ui->label_16);
    labelAll.append(ui->label_17);
    labelAll.append(ui->label_18);
    labelAll.append(ui->label_19);
    labelAll.append(ui->label_20);
    labelAll.append(ui->label_21);
    labelAll.append(ui->label_22);
    labelAll.append(ui->label_23);
    labelAll.append(ui->label_24);
    labelAll.append(ui->label_25);
    labelAll.append(ui->label_26);
    labelAll.append(ui->label_27);
    labelAll.append(ui->label_28);
    labelAll.append(ui->label_29);
    labelAll.append(ui->label_30);
    labelAll.append(ui->label_31);
    labelAll.append(ui->label_32);
}

void level::recGpsSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate)
{
    int i;
    gpsMessage.type = GPS;
    gpsMessage.satelliteNum = satNum;
    gpsMessage.elevation = ele;
    gpsMessage.azimuth = azi;
    gpsMessage.snr = sig;
    gpsMessage.locateFlag = locate;
    //提取最大信噪比
    for(i = 0; i < gpsMessage.snr.size(); i++)
    {
        if(gpsMessage.snr.at(i) > maxDb)
            maxDb = gpsMessage.snr.at(i);
    }
    setLabelName(gpsMessage.type, gpsMessage.satelliteNum);
    update();
}

void level::recBdSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate)
{
    int i;
    bdMessage.type = BD;
    bdMessage.satelliteNum = satNum;
    bdMessage.elevation = ele;
    bdMessage.azimuth = azi;
    bdMessage.snr = sig;
    bdMessage.locateFlag = locate;
    //提取最大信噪比
    for(i = 0; i < gpsMessage.snr.size(); i++)
    {
        if(gpsMessage.snr.at(i) > maxDb)
            maxDb = gpsMessage.snr.at(i);
    }
    setLabelName(bdMessage.type, bdMessage.satelliteNum);
    update();
}

void level::setLabelName(const GPSWorkMode& type, const QVector<int>& satNum)
{
    if(type == GPS)
    {
        for(int i = 0; i < satNum.size(); i++ )
        {
            labelAll.at(i)->setText('G' + QString::number(satNum.at(i)));
        }
    }
    else if (type == BD)
    {
        for(int i = 0; i < satNum.size(); i++ )
        {
            labelAll.at(i + 16)->setText('B' + QString::number(satNum.at(i)));
        }
    }
}

