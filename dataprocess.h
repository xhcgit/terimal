#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include "config.h"
#include "mytool.h"

#include <QObject>
#include <QSemaphore>
#include <QThread>

class DataProcess : public QThread
{
    Q_OBJECT

public:
    DataProcess(){}

    ~DataProcess(){}

    void run();
    char readOneByte();
    void updateHead(char ch);
    bool isRawDataHead();
    void initHead();

    QByteArray header;
    QByteArray nmeaEnd;

    bool isBdNmeaHead();
    bool isGpsNmeaHead();
signals:
    void revAPacketRawData(QByteArray ba, bool success);
    void revAPacketGpsNmeaData(QByteArray ba, bool success);
    void revAPacketBdNmeaData(QByteArray ba, bool success);
};

#endif // DATAPROCESS_H
