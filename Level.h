#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>
#include "satmessage.h"

namespace Ui {
class level;
}

class level : public QWidget
{
    Q_OBJECT

public:
    explicit level(QWidget *parent = 0);
    ~level();

private:
    Ui::level *ui;
    int maxDb;      //当前收到卫星的最大信噪比
    QVector<QLabel*> labelAll;
    satMessage gpsMessage;
    satMessage bdMessage;
    void drawTable(QPainter* painter, QWidget* widget);
    void initWidgetEvent();

    void setLabelName(const GPSWorkMode &type, const QVector<int> &satNum);
protected:
    void paintEvent(QPaintEvent *event);
    void paintOnWidget(QWidget *w, int labelIndex);
    bool eventFilter(QObject *watched, QEvent *e);
    void paintCoordinate(QWidget *w);
    void initLabel();

public slots:
    void recGpsSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate);
    void recBdSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate);
};

#endif // LEVEL_H
