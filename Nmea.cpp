#include "nmea.h"
#include "mytool.h"
#include <QString>
#include<QDateTime>
#include <QRegExp>
#include <QStringList>


/**
 * @brief Nmea::Nmea构造函数
 *
 * @param parent 父对象
 */
Nmea::Nmea(QObject *parent) : QObject(parent)
{

}

/**
 * @brief Nmea::~Nmea析构函数
 */
Nmea::~Nmea()
{

}

/**
 * @brief Nmea::nmea_parse_GPGGA 解析GPGGA语句
 *
 * @param str 包含GPGGA的字符串
 * @param pack GPGGA语句类型中
 *
 * @return success
 */
int Nmea::nmeaParseGpgga(QString *str, nmeaGPGGA *pack){
     //rx 分隔符正则表达式："，或*"
    QRegExp rx("[,\\*]");

    //brief list 依据nmea格式进行字符串分割
    QStringList list =  str->split(rx) ;
    if(list.length()<15)
    {
        return FAIL;
    }
    bool ok;
    pack->utc = QDateTime::fromString(list[1], "hhmmss.zz");
    pack->lat = MyTool::NmeaLatStringToDouble(list[2]);
    pack->ns = list[3].isEmpty()? '\0' : list[3].at(0).toLatin1();
    pack->lon = MyTool::NmeaLonStringToDouble(list[4]);
    pack->ew = list[5].isEmpty()? '\0' : list[5].at(0).toLatin1();
    pack->sig = list[6].toInt(&ok, 10);
    pack->satinuse = list[7].toInt(&ok, 10);
    pack->HDOP = list[8].toDouble();
    pack->elv = list[9].toDouble();
    pack->elv_units = list[10].isEmpty()? '\0' : list[10].at(0).toLatin1();;
    pack->diff = list[11].toDouble();
    pack->diff_units = list[12].isEmpty()? '\0' : list[12].at(0).toLatin1();;
    pack->dgps_age = list[13].toDouble();
    pack->dgps_sid = list[14].toInt(&ok, 10);

    return SUCCESS;
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param str [description]
 * @param pack [description]
 *
 * @return [description]
 */
int Nmea::nmeaParseGpgsa(QString *str, nmeaGPGSA *pack)
{
    //rx 分隔符正则表达式："，或*"
   QRegExp rx("[,\*]");
   //brief list 依据nmea格式进行字符串分割
   QStringList list =  str->split(rx) ;
   if(list.length()<18)
   {
       return FAIL;
   }
   bool ok;
   pack->fix_mode = list[1].isEmpty()? '\0' : list[1].at(0).toLatin1();
   pack->fix_type = list[2].toInt(&ok, 10);
   for(int i=0;i<12;i++)
       pack->sat_prn[i] = list[i+3].toInt(&ok,10);
   pack->PDOP = list[15].toDouble();
   pack->HDOP = list[16].toDouble();
   pack->VDOP = list[17].toDouble();

   return SUCCESS;
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param str [description]
 * @param pack [description]
 *
 * @return [description]
 */

int Nmea::nmeaParseGpgsv(QString *str, nmeaGPGSV *pack)
{
    QRegExp rx("[,\*]");
    //brief list 依据nmea格式进行字符串分割
    QStringList list =  str->split(rx) ;

    bool ok;
    int count;//本条GSV信息应该输出的卫星信息个数
    int free_sat_count;

    if(list.length()<9)
    {
        return FAIL;
    }
    pack->pack_count = list[1].toInt(&ok,10);    //总的GSV语句电文数
    pack->pack_index = list[2].toInt(&ok,10);    //当前GSV语句号
    pack->sat_count = list[3].toInt(&ok,10);    //可视卫星总数

    int index = 4;//每条GSV信息最多输出4个卫星的信息

    free_sat_count = (pack->sat_count - (pack->pack_index - 1) * 4 );

    if(free_sat_count >= 4)    //如果剩余卫星的数量大于4，则本条GSV信息包含4个卫星信息
        count = 4;
    else
        count = ((pack->sat_count) % 4);    //否则包含剩余卫星信息(1~3个)

    for(int i = 0; i < count; i++)
    {
        pack->sat_data[i].id = list[index].toInt(&ok,10);
        pack->sat_data[i].elv = list[index + 1].toInt(&ok,10);
        pack->sat_data[i].azimuth = list[index + 2].toInt(&ok,10);
        pack->sat_data[i].sig = list[index +3].toInt(&ok,10);
        index += 4;
    }
    return SUCCESS;
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param str [description]
 * @param pack [description]
 *
 * @return [description]
 */
int Nmea::nmeaParseGprmc(QString *str, nmeaGPRMC *pack)
{
    QRegExp rx("[,\*]");

    //brief list 依据nmea格式进行字符串分割
    QStringList list =  str->split(rx) ;
    if(list.length()<13)
    {
        return FAIL;
    }
    pack->utc = list[1];
    pack->status = list[2].isEmpty()? '\0' : list[2].at(0).toLatin1();
    pack->lat = list[3].toDouble();
    pack->ns = list[4].isEmpty()? '\0' : list[4].at(0).toLatin1();
    pack->lon = list[5].toDouble();
    pack->ew = list[6].isEmpty()? '\0' : list[6].at(0).toLatin1();
    pack->speed = list[7].toDouble();
    pack->direction = list[8].toDouble();
    pack->utc_date = QDate::fromString(list[9],"ddMMyy");
    pack->declination = list[10].toDouble();
    pack->declin_ew = list[11].isEmpty()? '\0' : list[11].at(0).toLatin1();
    pack->mode = list[12].isEmpty()? '\0' : list[12].at(0).toLatin1();

    return SUCCESS;
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param str [description]
 * @param pack [description]
 *
 * @return [description]
 */
int Nmea::nmeaParseGpvtg(QString *str, nmeaGPVTG *pack)
{
    QRegExp rx("[,\*]");
    //brief list 依据nmea格式进行字符串分割
    QStringList list =  str->split(rx) ;
    if(list.length()<10)
    {
        return FAIL;
    }
    pack->dir = list[1].toDouble();
    pack->dir_t = list[2].isEmpty()? '\0' : list[2].at(0).toLatin1();
    pack->dec = list[3].toDouble();
    pack->dec_m = list[4].isEmpty()? '\0' : list[4].at(0).toLatin1();
    pack->spn = list[5].toDouble();
    pack->spn_n = list[6].isEmpty()? '\0' : list[6].at(0).toLatin1();
    pack->spk = list[7].toDouble();
    pack->spk_k = list[8].isEmpty()? '\0' : list[8].at(0).toLatin1();
    pack->pos = list[9].isEmpty()? '\0' : list[9].at(0).toLatin1();

    return SUCCESS;
}

int Nmea::nmeaParseGpgll(QString *str, nmeaGPGLL *pack)
{
    QRegExp rx("[,\*]");
    //brief list 依据nmea格式进行字符串分割
    QStringList list =  str->split(rx) ;

    if(list.length()<7)
    {
        return FAIL;
    }

    pack->lat = list[1].toDouble();
    pack->ns = list[2].isEmpty()? '\0' : list[2].at(0).toLatin1();
    pack->lon = list[3].toDouble();
    pack->ew =  list[4].isEmpty()? '\0' : list[4].at(0).toLatin1();;
    pack->utc = QDateTime::fromString(list[5], "hhmmss.zz");
    pack->status = list[6].isEmpty()? '\0' : list[6].at(0).toLatin1();;

    return SUCCESS;
}

int Nmea::nmeaParseGpzda(QString *str, nmeaGPZDA *pack)
{
    QRegExp rx("[,\*]");
    //brief list 依据nmea格式进行字符串分割
    QStringList list =  str->split(rx) ;
    if(list.length()<7)
    {
        return FAIL;
    }
    bool ok;
    pack->time = QDateTime::fromString(list[1], "hhmmss.zz");
    pack->day = QDate::fromString(list[2],"d");
    pack->month = QDate::fromString(list[3],"M");
    pack->year = QDate::fromString(list[4],"yyyy");
    pack->ltzh = list[5].toInt(&ok,10);
    pack->ltzn = list[6].toInt(&ok,10);

    return SUCCESS;
}

int Nmea::nmeaParseGptxt(QString *str, nmeaGPTXT *pack)
{
    return SUCCESS;
}

/**
 * @brief nmea_calc_crc 求取校验和
 *
 * @param buff待校验字符串
 * @param buff_sz字符串长度
 *
 * @return  校验和
 */
int nmea_calc_crc(const char *buff, int buff_sz)
{
    int chsum = 0,
        it;

    for(it = 0; it < buff_sz; ++it)
        chsum ^= (int)buff[it];

    return chsum;
}
