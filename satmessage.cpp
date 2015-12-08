#include "satmessage.h"
satMessage::satMessage()
{

}

satMessage::~satMessage()
{

}

void satMessage::clearBox()
{
    satelliteNum.clear();
    elevation.clear();
    azimuth.clear();
    snr.clear();
    locateFlag.clear();
}

void satMessage::setGpsSatMessage(nmeaGPGSA GPGSA, QVector<nmeaGPGSV> GPGSV)
{
    type = GPGSA.gpsWorkMode;
    QVector<int> locateSat;    //用于保存GSA中的定位卫星号
    int i = 0;
    int j = 0;
    int delete_count = 0;
    for(i = 0; i <  GPGSV.size(); i++)    //循环次数GSV语句数量
    {
        for(j = 0; j < 4; j++)
        {
           satelliteNum.push_back(GPGSV.at(i).sat_data[j].id);
           elevation.push_back(GPGSV.at(i).sat_data[j].elv);
           azimuth.push_back(GPGSV.at(i).sat_data[j].azimuth);
           snr.push_back(GPGSV.at(i).sat_data[j].sig);
        }
    }

    delete_count = (GPGSV.front().pack_count) * 4 - GPGSV.front().sat_count ;
    for(; delete_count > 0; delete_count--)    //删去多余的卫星信息
    {
        satelliteNum.pop_back();
        elevation.pop_back();
        azimuth.pop_back();
        snr.pop_back();
    }

    i = 0;
    while(GPGSA.sat_prn[i] != 0)    //收集用于定位的卫星号
    {
        locateSat.push_back(GPGSA.sat_prn[i]);
        i++;
    }

    for(i = 0; i < satelliteNum.size(); i++)
    {
        for(j = 0; j < locateSat.size(); j++)
        {
            if(satelliteNum.at(i) == locateSat.at(j))
            {
                locateFlag.push_back(true);
                break;
            }
        }
        if(j == locateSat.size())
        {
            locateFlag.push_back(false);
        }
    }

    emit sendGpsSatMessage(satelliteNum, elevation, azimuth, snr, locateFlag);

    clearBox();

}

void satMessage::setBdSatMessage(nmeaGPGSA BDGSA, QVector<nmeaGPGSV> BDGSV)
{
    type = BDGSA.gpsWorkMode;
    QVector<int> locateSat;    //用于保存GSA中的定位卫星号
    int i = 0;
    int j = 0;
    int delete_count = 0;
    for(i = 0; i <  BDGSV.size(); i++)    //循环次数GSV语句数量
    {
        for(j = 0; j < 4; j++)
        {
           satelliteNum.push_back(BDGSV.at(i).sat_data[j].id);
           elevation.push_back(BDGSV.at(i).sat_data[j].elv);
           azimuth.push_back(BDGSV.at(i).sat_data[j].azimuth);
           snr.push_back(BDGSV.at(i).sat_data[j].sig);
        }
    }

    delete_count = (BDGSV.front().pack_count) * 4 - BDGSV.front().sat_count ;
    for(; delete_count > 0; delete_count--)    //删去多余的卫星信息
    {
        satelliteNum.pop_back();
        elevation.pop_back();
        azimuth.pop_back();
        snr.pop_back();
    }

    i = 0;
    while(BDGSA.sat_prn[i] != 0)    //收集用于定位的卫星号
    {
        locateSat.push_back(BDGSA.sat_prn[i]);
        i++;
    }

    for(i = 0; i < satelliteNum.size(); i++)
    {
        for(j = 0; j < locateSat.size(); j++)
        {
            if(satelliteNum.at(i) == locateSat.at(j))
            {
                locateFlag.push_back(true);
                break;
            }
        }
        if(j == locateSat.size())
        {
            locateFlag.push_back(false);
        }
    }

    emit sendBdSatMessage(satelliteNum, elevation, azimuth, snr, locateFlag);

    clearBox();
}

