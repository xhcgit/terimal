#include "NmeaParser.h"
#include "Nmea.h"
#include "config.h"

#include <QException>
#include <QRegExp>




void NmeaParser::run()
{

}

GPSWorkMode NmeaParser::getWorkMode(QString nmeaScentence)
{
    GPSWorkMode mode;
    if(nmeaScentence.startsWith("$GP"))
    {
        mode = GPS;
    }else if(nmeaScentence.startsWith("$BD"))
    {
        mode = BD;
    }else if(nmeaScentence.startsWith("$GN"))
    {
        mode = GPSBD;
    }else
    {
        mode = UnCertain;
    }
    return mode;
}

/**
 * @brief NmeaParser::getNmeaScentenceType 获取nmea语句类型
 * @param nmeaScentence nmea语句
 * @return nmea语句类型
 */
NmeaScentenceType NmeaParser::getNmeaScentenceType(QString nmeaScentence)
{
    NmeaScentenceType type;

    if(nmeaScentence.indexOf("GGA") == 3)
    {
        type = NMEA0183GGA;         
    }
    else if(nmeaScentence.indexOf("GLL") == 3)
    {
        type = NMEA0183GLL;                
    }
    else if(nmeaScentence.indexOf("GSA") == 3)
    {
        type = NMEA0183GSA;                
    }
    else if(nmeaScentence.indexOf("GSV") == 3)
    {
        type = NMEA0183GSV;                
    }
    else if(nmeaScentence.indexOf("RMC") == 3)
    {
        type = NMEA0183RMC;                
    }
    else if(nmeaScentence.indexOf("VTG") == 3)
    {
        type = NMEA0183VTG;                
    }
    else if(nmeaScentence.indexOf("ZDA") == 3)
    {
        type = NMEA0183ZDA;                
    }
    else if(nmeaScentence.indexOf("TXT") == 3)
    {
        type = NMEA0183TXT;                
    }
    else
    {
        type = NMEA0183PMTK;
    }

    return type;
}
bool NmeaParser::parserNmeaSentence(QByteArray ba)
{
    QString nmeaScentence =  QString(ba);

    GPSWorkMode gpsWorkMode = getWorkMode(nmeaScentence);    //判断工作模式

    NmeaScentenceType nmeaScentenceType = getNmeaScentenceType(nmeaScentence);    //判断NMEA语句类型

    switch(nmeaScentenceType)
    {
    case NMEA0183GGA :
    {
        nmeaGPGGA nmeaGGA;
        nmeaGGA.gpsWorkMode = gpsWorkMode;
        Nmea::nmeaParseGpgga(&nmeaScentence, &nmeaGGA);
        emit sendGGA(nmeaGGA);
        //updateDataBase(nmeaGGA);
        break;
    }
    case NMEA0183GLL:
    {
        nmeaGPGLL nmeaGLL;
        nmeaGLL.gpsWorkMode = gpsWorkMode;
        Nmea::nmeaParseGpgll(&nmeaScentence, &nmeaGLL);
        //updateDataBase(nmeaGLL);
        break;
    }
    case NMEA0183GSA:
    {
        nmeaGPGSA nmeaGSA;
        nmeaGSA.gpsWorkMode = gpsWorkMode;
        Nmea::nmeaParseGpgsa(&nmeaScentence, &nmeaGSA);
        if(gpsWorkMode == GPS)
        {
            GPGSA = nmeaGSA;
            flagReadyGpgsa = 1;    //表示GSA信息已准备好
        }
        else if(gpsWorkMode == BD)
        {
            BDGSA = nmeaGSA;
            flagReadyBdgsa = 1;    //表示GSA信息已准备好
        }
        if((flagReadyGpgsa == 1)&&(flagReadyBdgsa == 1))
            emit sendAllGSA(GPGSA, BDGSA);
        //updateDataBase(nmeaGSA);
        break;
    }
    case NMEA0183GSV :
    {
        nmeaGPGSV nmeaGSV;
        nmeaGSV.gpsWorkMode = gpsWorkMode;

        if((Nmea::nmeaParseGpgsv(&nmeaScentence, &nmeaGSV)) == 1)
        {
            if(nmeaGSV.gpsWorkMode == GPS)
            {
                GPGSV.push_back(nmeaGSV);
                mergeGsv(GPGSV);
            }
            else if(nmeaGSV.gpsWorkMode == BD)
            {
                BDGSV.push_back(nmeaGSV);
                mergeGsv(BDGSV);
            }
        }

        //updateDataBase(nmeaGSV);
        break;
    }
    case NMEA0183RMC :
    {
        nmeaGPRMC nmeaRMC;
        nmeaRMC.gpsWorkMode = gpsWorkMode;
        Nmea::nmeaParseGprmc(&nmeaScentence, &nmeaRMC);
        //TODO 方法不严谨，有待改正
        if(nmeaRMC.utc_date.year() < 2000)    //卫星日期会被判定成19XX年，所以加1000年。
            nmeaRMC.utc_date = nmeaRMC.utc_date.addYears(100);
        emit sendGPRMC(nmeaRMC);
        //updateDataBase(nmeaRMC);
        break;
        }
    case NMEA0183VTG :
    {
        nmeaGPVTG nmeaVTG;
        nmeaVTG.gpsWorkMode = gpsWorkMode;
        Nmea::nmeaParseGpvtg(&nmeaScentence, &nmeaVTG);
        emit sendGPVTG(nmeaVTG);
        //updateDataBase(nmeaVTG);
        break;
    }
    case NMEA0183ZDA :
    {
        nmeaGPZDA nmeaZDA;
        nmeaZDA.gpsWorkMode = gpsWorkMode;
        Nmea::nmeaParseGpzda(&nmeaScentence, &nmeaZDA);
        //updateDataBase(nmeaZDA);
        break;
    }
    case NMEA0183TXT :
    {
        nmeaGPTXT nmeaTXT;
        nmeaTXT.gpsWorkMode = gpsWorkMode;
        Nmea::nmeaParseGptxt(&nmeaScentence, &nmeaTXT);
        //updateDataBase(nmeaTXT);
        break;
    }
    default:
        break;
    }

}

//合并GSV语句
void NmeaParser::mergeGsv(QVector<nmeaGPGSV>& GSV)
{
    //首先判断GSV语句类型是GPS还是BD
    if(GSV.at(0).gpsWorkMode == GPS)
    {
        if(GSV.front().pack_index != 1)    //如果第一个不是1号GSV则删去
        {
            GSV.pop_front();
        }
        else if((GSV.size() == GSV.front().pack_count) && (flagReadyGpgsa == 1))
        {
            emit sendGPGSVAndGPGSA(GPGSA, GSV);
            flagReadyGpgsa = 0;
            GSV.clear();
        }
    }
    else if(GSV.at(0).gpsWorkMode == BD)
    {
        if(GSV.front().pack_index != 1)    //如果第一个不是1号GSV则删去
        {
            GSV.pop_front();
        }
        else if((GSV.size() == GSV.front().pack_count) && (flagReadyBdgsa == 1))
        {
            emit sendBDGSVAndBDGSA(BDGSA, GSV);
            flagReadyBdgsa = 0;
            GSV.clear();
        }
    }
}



/*void NmeaParser::updateDataBase(nmeaGPGGA nmeaGpgga)
{
    if(gGAList.size() > NMEA_BUFFER_QUEUE_SIZE)
    {
        gGAList.removeFirst();
    }
    gGAList.append(nmeaGpgga);
}
void NmeaParser::updateDataBase(nmeaGPGLL nmeaGpgll)
{
    if(gLLList.size() > NMEA_BUFFER_QUEUE_SIZE)
    {
        gLLList.removeFirst();
    }
    gLLList.append(nmeaGpgll);
}
void NmeaParser::updateDataBase(nmeaGPGSA nmeaGpgsa)
{
    if(gSAList.size() > NMEA_BUFFER_QUEUE_SIZE)
    {
        gSAList.removeFirst();
    }
    gSAList.append(nmeaGpgsa);
}
void NmeaParser::updateDataBase(nmeaGPGSV nmeaGpgsv)
{
    if(gSVList.size() > NMEA_BUFFER_QUEUE_SIZE)
    {
        gSVList.removeFirst();
    }
    gSVList.append(nmeaGpgsv);
}
void NmeaParser::updateDataBase(nmeaGPRMC nmeaGprmc)
{
    if(rMCList.size() > NMEA_BUFFER_QUEUE_SIZE)
    {
        rMCList.removeFirst();
    }
    rMCList.append(nmeaGprmc);
}
void NmeaParser::updateDataBase(nmeaGPVTG nmeaGpvtg)
{
    if(vTGList.size() > NMEA_BUFFER_QUEUE_SIZE)
    {
        vTGList.removeFirst();
    }
    vTGList.append(nmeaGpvtg);
}
void NmeaParser::updateDataBase(nmeaGPZDA nmeaGpzda)
{
    if(zDAList.size() > NMEA_BUFFER_QUEUE_SIZE)
    {
        zDAList.removeFirst();
    }
    zDAList.append(nmeaGpzda);
}
void NmeaParser::updateDataBase(nmeaGPTXT nmeaGptxt)
{
    if(tXTList.size() > NMEA_BUFFER_QUEUE_SIZE)
    {
        tXTList.removeFirst();
    }
    tXTList.append(nmeaGptxt);
}*/

//static member initialize
/*QList<nmeaGPGGA> NmeaParser::gGAList;
QList<nmeaGPGLL> NmeaParser::gLLList;
QList<nmeaGPGSA> NmeaParser::gSAList;
QList<nmeaGPGSV> NmeaParser::gSVList;
QList<nmeaGPRMC> NmeaParser::rMCList;
QList<nmeaGPVTG> NmeaParser::vTGList;
QList<nmeaGPZDA> NmeaParser::zDAList;
QList<nmeaGPTXT> NmeaParser::tXTList;*/
