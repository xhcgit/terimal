#include "satellitedata.h"
#include "ui_satellitedata.h"

satelliteData::satelliteData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::satelliteData)
{
    ui->setupUi(this);
    initLabel();
}

satelliteData::~satelliteData()
{
    delete ui;
}

void satelliteData::initLabel()
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

void satelliteData::recGga(const nmeaGPGGA& GGA)
{
    ui->labelLonValue->setText(QString::number(GGA.lon) + GGA.ew);
    ui->labelLatValue->setText(QString::number(GGA.lat) + GGA.ns);
    ui->labelAltValue->setText(QString::number(GGA.elv) + 'm');
}

void satelliteData::recGSA(const nmeaGPGSA &GPGSA, const nmeaGPGSA &BDGSA)
{
    QString messageFixMode;
    QString messagePDOP;
    QString messageHDOP;
    messageFixMode.append("GPS:");
    switch(GPGSA.fix_type)
    {
    case 1:
        messageFixMode.append("NO");
        break;
    case 2:
        messageFixMode.append("2D");
        break;
    case 3:
        messageFixMode.append("3D");
        break;
    default:
        break;
    }
    messageFixMode.append("    ");
    messageFixMode.append("BD:");
    switch(BDGSA.fix_type)
    {
    case 1:
        messageFixMode.append("NO");
        break;
    case 2:
        messageFixMode.append("2D");
        break;
    case 3:
        messageFixMode.append("3D");
        break;
    default:
        break;
    }
    messagePDOP.append("GPS:" + QString::number(GPGSA.PDOP) + "    " + "BD:" + QString::number(BDGSA.PDOP));
    messageHDOP.append("GPS:" + QString::number(GPGSA.HDOP) + "    " + "BD:" + QString::number(BDGSA.HDOP));
    ui->labelFixModeValue->setText(messageFixMode);
    ui->labelPdopValue->setText(messagePDOP);
    ui->labelHdopValue->setText(messageHDOP);
}

void satelliteData::recGpsSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate)
{
    gpsMessage.type = GPS;
    gpsMessage.satelliteNum = satNum;
    gpsMessage.elevation = ele;
    gpsMessage.azimuth = azi;
    gpsMessage.snr = sig;
    gpsMessage.locateFlag = locate;
    updateLabel();
}

void satelliteData::recBdSatMessage(QVector<int> satNum, QVector<int> ele, QVector<int> azi, QVector<int> sig, QVector<bool> locate)
{
    bdMessage.type = BD;
    bdMessage.satelliteNum = satNum;
    bdMessage.elevation = ele;
    bdMessage.azimuth = azi;
    bdMessage.snr = sig;
    bdMessage.locateFlag = locate;
    updateLabel();
}

void satelliteData::updateLabel()
{
    int i;
    for(i = 0; i< gpsMessage.locateFlag.size(); i++)
    {
        QString message;
        if(gpsMessage.locateFlag.at(i) == true)
            message = "QLabel{background:rgb(0,255,0)}";
        else if((gpsMessage.locateFlag.at(i) == false) && (gpsMessage.snr.at(i) != 0))
            message = "QLabel{background:rgb(0,85,255)}";
        else
            message = "QLabel{background:rgb(170,166,162)}";
        labelAll.at(i)->setStyleSheet(message);
    }

    for(i = 0; i< bdMessage.locateFlag.size(); i++)
    {
        QString message;
        if(bdMessage.locateFlag.at(i) == true)
            message = "QLabel{background:rgb(0,255,0)}";
        else if((bdMessage.locateFlag.at(i) == false) && (bdMessage.snr.at(i) != 0))
            message = "QLabel{background:rgb(0,85,255)}";
        else
            message = "QLabel{background:rgb(170,166,162)}";
        labelAll.at(i+16)->setStyleSheet(message);
    }
}
