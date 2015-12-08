#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include "config.h"
#include <QObject>
#include <QSemaphore>

class SharedData
{
public:
    SharedData();
    ~SharedData();

    //声明为static，等价于全局变量
    static char bufferRawData [SERIAL_BUFFER_SIZE];
    static QSemaphore freeRawData;
    static QSemaphore usedRawData;
};



#endif // SHAREDDATA_H

