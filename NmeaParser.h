#ifndef NMEAPARSER_H
#define NMEAPARSER_H

#include "Nmea.h"
#include <QObject>
#include <QThread>
#include <QVector>

class NmeaParser : public QThread
{
    Q_OBJECT

public:
    NmeaParser()
    {
        GpgsvBegin = 1;
        BdgsvBegin = 1;
    }
    ~NmeaParser(){}

    void run();


    static QList<nmeaGPGGA> gGAList;
    static QList<nmeaGPGLL> gLLList;
    static QList<nmeaGPGSA> gSAList;
    static QList<nmeaGPGSV> gSVList;
    static QList<nmeaGPRMC> rMCList;
    static QList<nmeaGPVTG> vTGList;
    static QList<nmeaGPZDA> zDAList;
    static QList<nmeaGPTXT> tXTList;

    GPSWorkMode getWorkMode(QString str);
    NmeaScentenceType getNmeaScentenceType(QString str);

    void updateDataBase();
    void updateDataBase(nmeaGPGGA nmeaGpgga);
    void updateDataBase(nmeaGPGLL nmeaGpgll);
    void updateDataBase(nmeaGPGSA nmeaGpgsa);
    void updateDataBase(nmeaGPGSV nmeaGpgsv);
    void updateDataBase(nmeaGPRMC nmeaGprmc);
    void updateDataBase(nmeaGPVTG nmeaGpvtg);
    void updateDataBase(nmeaGPZDA nmeaGpzda);
    void updateDataBase(nmeaGPTXT nmeaGptxt);
signals:
    void sendGGA(nmeaGPGGA GPGGA);
    void sendGPVTG(nmeaGPVTG GPVTG);
    void sendGPRMC(nmeaGPRMC GPRMC);
    void sendGPGSVAndGPGSA(nmeaGPGSA GPGSA, QVector<nmeaGPGSV> GPGSV);
    void sendBDGSVAndBDGSA(nmeaGPGSA BDGSA, QVector<nmeaGPGSV> BDGSV);
    void sendAllGSA(nmeaGPGSA GPGSA, nmeaGPGSA BDGSA);


private slots:
    bool parserNmeaSentence(QByteArray ba);
private:
    void mergeGsv(QVector<nmeaGPGSV> &GSV);
    QVector<nmeaGPGSV> GPGSV;
    QVector<nmeaGPGSV> BDGSV;\
    nmeaGPGSA GPGSA;
    nmeaGPGSA BDGSA;
    int flagReadyGpgsa;
    int flagReadyBdgsa;
    int GpgsvBegin;
    int BdgsvBegin;
};

#endif // NMEAPARSER_H
