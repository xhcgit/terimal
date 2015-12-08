/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "mdichild.h"
#include "frmConsole.h"
#include "mytool.h"
#include "config.h"
#include "dataprocess.h"
#include "SharedData.h"
#include "NmeaParser.h"
#include "Configuration.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QException>
#include <QSemaphore>
#include <QThread>


//! [0]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//! [0]
    ui->setupUi(this);

    //添加主窗口mdi区域
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    createDockWindows();
    //添加binary console窗口，暂时添加到此，后面需要在界面上根据用户自己需要进行打开
    initConsoleWindows();

    //新建初始化串口
    serial = new QSerialPort(this);

    //新建串口设置对话框
    settings = new SettingsDialog;

    //卫星信息保存
    satellites = new satMessage();


    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    initActionsConnections();

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

    connect(configView, SIGNAL(sendCmdViaCom(QByteArray)),
            this, SLOT(writeData(QByteArray)));


    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));   //串口有数据，马上触发读取


    //分离、校验线程
    DataProcess *processRawData = new DataProcess;  //初始化消费者线程
    NmeaParser *n = new NmeaParser;
    connect(processRawData, SIGNAL(revAPacketGpsNmeaData(QByteArray, bool)),    //收到GPS的Nmea语句后解析，保存数据库，图形显示
            n, SLOT(parserNmeaSentence(QByteArray)));

    connect(processRawData, SIGNAL(revAPacketBdNmeaData(QByteArray, bool)),    //收到BD的Nmea语句后解析，保存数据库，图形显示
            n, SLOT(parserNmeaSentence(QByteArray)));

//    connect(processRawData, SIGNAL(revAPacketRawData(QByteArray,bool)),    //收到BinaryData语句后按照协议类型分类显示保存程序
//            this, SLOT(pickAndPrintRawData(QByteArray, bool)));

    connect(processRawData, SIGNAL(revAPacketRawData(QByteArray,bool)),    //收到BinaryData语句后的显示到文本框中，以binary保存到txt中
            binaryConsole, SLOT(appendAndSaveAsHex(QByteArray,bool)));


    connect(processRawData, SIGNAL(revAPacketGpsNmeaData(QByteArray, bool)),    //收到GPS的Nmea语句后，显示到文本框中，保存到txt文件中
            textConsole, SLOT(appendAndSaveAsString(QByteArray, bool)));

    connect(processRawData, SIGNAL(revAPacketBdNmeaData(QByteArray, bool)),    //收到BD的Nmea语句后，显示到文本框中，保存到txt文件中
            textConsole, SLOT(appendAndSaveAsString(QByteArray, bool)));



    connect(n, SIGNAL(sendGGA(nmeaGPGGA)),
            mapView, SLOT(setLonAndnLat(nmeaGPGGA)));

    connect(n, SIGNAL(sendGPVTG(nmeaGPVTG)),
            rateView, SLOT(setRate(nmeaGPVTG)));

    connect(n, SIGNAL(sendGPRMC(nmeaGPRMC)),
            utctimeView, SLOT(setDataValue(nmeaGPRMC)));

    connect(n, SIGNAL(sendGPGSVAndGPGSA(nmeaGPGSA, QVector<nmeaGPGSV>)),    //对GPGSV和GPGSA提取卫星信息
            satellites, SLOT(setGpsSatMessage(nmeaGPGSA, QVector<nmeaGPGSV>)));

    connect(n, SIGNAL(sendBDGSVAndBDGSA(nmeaGPGSA, QVector<nmeaGPGSV>)),    //对BDGSV和BDGSA提取卫星信息
            satellites, SLOT(setBdSatMessage(nmeaGPGSA, QVector<nmeaGPGSV>)));

    //接收信息用于GPS卫星位置的显示
    connect(satellites, SIGNAL(sendGpsSatMessage(QVector<int>, QVector<int>,QVector<int>, QVector<int>, QVector<bool>)),
            positionView, SLOT(recGpsSatMessage(QVector<int>, QVector<int>, QVector<int>, QVector<int>, QVector<bool>)));

    //接收信息用于BD卫星位置的显示
    connect(satellites, SIGNAL(sendBdSatMessage(QVector<int>, QVector<int>,QVector<int>, QVector<int>, QVector<bool>)),
            positionView, SLOT(recBdSatMessage(QVector<int>, QVector<int>, QVector<int>, QVector<int>, QVector<bool>)));

    //接收信息用于GPS卫星信息的显示
    connect(satellites, SIGNAL(sendGpsSatMessage(QVector<int>, QVector<int>,QVector<int>, QVector<int>, QVector<bool>)),
            satDataView, SLOT(recGpsSatMessage(QVector<int>, QVector<int>, QVector<int>, QVector<int>, QVector<bool>)));
    //接收信息用于BD卫星信息的显示
    connect(satellites, SIGNAL(sendBdSatMessage(QVector<int>, QVector<int>,QVector<int>, QVector<int>, QVector<bool>)),
            satDataView, SLOT(recBdSatMessage(QVector<int>, QVector<int>, QVector<int>, QVector<int>, QVector<bool>)));

    //接收信息用于卫星信息的显示
    connect(n, SIGNAL(sendAllGSA(nmeaGPGSA,nmeaGPGSA)), satDataView, SLOT(recGSA(nmeaGPGSA,nmeaGPGSA)));

    connect(n, SIGNAL(sendGGA(nmeaGPGGA)),satDataView, SLOT(recGga(nmeaGPGGA)));

    //接收信息用于显示卫星信噪比
    connect(satellites, SIGNAL(sendGpsSatMessage(QVector<int>, QVector<int>,QVector<int>, QVector<int>, QVector<bool>)),
            levelView, SLOT(recGpsSatMessage(QVector<int>, QVector<int>, QVector<int>, QVector<int>, QVector<bool>)));

    connect(satellites, SIGNAL(sendBdSatMessage(QVector<int>, QVector<int>,QVector<int>, QVector<int>, QVector<bool>)),
            levelView, SLOT(recBdSatMessage(QVector<int>, QVector<int>, QVector<int>, QVector<int>, QVector<bool>)));


    dockBinary->show();
    dockText->show();
    processRawData->start();    //启动线程
}

/**
 * @brief MainWindow::~MainWindow 析构函数
 */
MainWindow::~MainWindow()
{
    delete settings;
    delete ui;

//    delete serial;
//    delete configView;
//    delete mapView;
//    delete rateView;
//    delete utctimeView;
//    delete satellites;
//    delete positionView;
//    delete satDataView;
//    delete levelView;
//    delete dockLevel;
//    delete dockData;
//    delete dockPosition;
//    delete dockMap;
//    delete dockRate;
//    delete dockTime;
//    delete dockText;
//    delete dockBinary;
//    delete dockConfig;
}

/**
 * @brief MainWindow::openSerialPort 打开串口
 */
void MainWindow::openSerialPort()
{
    if(serial->isOpen())
    {
        return;
    }
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}

/**
 * @brief MainWindow::closeSerialPort 关闭串口
 */
void MainWindow::closeSerialPort()
{
    if(!serial->isOpen())
    {
        return;
    }
    serial->close();
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}

/**
 * @brief MainWindow::about 关于对话框
 */
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

/**
 * @brief MainWindow::writeData 数据发送
 * @param data 待发送数据
 */
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

/**
 * @brief MainWindow::readData 串口读
 */
void MainWindow::readData()
{
    QByteArray data = serial->readAll();    //读取所有数据
    //填充rawdata线程
    qDebug()<<data;
    static int indexRawData = 0;
    for(int i =0; i<data.length(); i++)
    {
        SharedData::freeRawData.acquire();
        SharedData::bufferRawData[indexRawData%SERIAL_BUFFER_SIZE] = data.at(i);
        indexRawData++;
        SharedData::usedRawData.release();
    }

//    QByteArray data = serial->readAll();    //读取串口所有数据

//    //获取当前时间作为文件名
//    static QDateTime now=QDateTime::currentDateTime();
//    static QString name=now.toString("yyyyMMddHHmmss");
//    //拼接文件全路径，存放在log目录中
//    static QString fileName ="binary-data-" + name + ".txt";

//    //数据以rawdata格式保存
//    QFile file(fileName);
//    file.open(QFile::Append | QIODevice::Text);
//    QDataStream out(&file);
//    out.writeRawData(data.data(), data.length());
//    file.close();

//    //数据转换为string，显示在界面中
//    QString str = MyTool::ByteArrayToHexStr(data);    //16进制byte数组转16进制string数组
//    binaryConsole->append(str); //显示到binary console窗口中
}

/**
 * @brief MainWindow::handleError 错误处理
 * @param error 串口错误
 */
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::pickAndPrintRawData(QByteArray ba, bool success)
{
    char messageBigClassId = ba.at(2);
    char messageSmallClassId = ba.at(3);
    if(messageBigClassId == 0x02)
    {
        if(messageSmallClassId == 0x40)
        {
            _40Console->appendAndSaveAsHex(ba, success);
        }else if(messageSmallClassId == 0x41)

        {
            _41Console->appendAndSaveAsHex(ba, success);
        }else if(messageSmallClassId == 0x42)
        {
            _42Console->appendAndSaveAsHex(ba, success);
        }
    }else if(messageBigClassId == 0x03)
    {
        debugConsole->appendAndSaveAsHex(ba, success);

    }else
    {
        binaryConsole->appendAndSaveAsString(ba, success);
    }
}


/**
 * @brief MainWindow::initActionsConnections 初始化信号连接
 */
void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createDockWindows()
{
    dockLevel = new QDockWidget(tr("Level"), this);
    //卫星信噪比窗口
    levelView = new level(dockLevel);
    dockLevel->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockLevel->setWidget(levelView);
    addDockWidget(Qt::TopDockWidgetArea, dockLevel);
    dockLevel->hide();

    dockData = new QDockWidget(tr("Data"), this);
    //卫星信息
    satDataView = new satelliteData(dockData);
    dockData->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockData->setWidget(satDataView);
    addDockWidget(Qt::TopDockWidgetArea, dockData);
    dockData->hide();

    dockPosition = new QDockWidget(tr("Positon"), this);
    //卫星位置地图
    positionView = new position(dockPosition);
    dockPosition->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockPosition->setWidget(positionView);
    addDockWidget(Qt::TopDockWidgetArea, dockPosition);
    dockPosition->hide();

    dockMap = new QDockWidget(tr("Map"), this);
    //新建地图窗口
    mapView = new map(dockMap);
    dockMap->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockMap->setWidget(mapView);
    addDockWidget(Qt::TopDockWidgetArea, dockMap);
    dockMap->hide();

    dockRate = new QDockWidget(tr("Rate"), this);
    //新建速度窗口
    rateView = new rate(dockRate);
    dockRate->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockRate->setWidget(rateView);
    addDockWidget(Qt::TopDockWidgetArea, dockRate);
    dockRate->hide();

    dockTime = new QDockWidget(tr("Rate"), this);
    //新建时间窗口
    utctimeView = new utcTime(dockTime);
    dockTime->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockTime->setWidget(utctimeView);
    addDockWidget(Qt::TopDockWidgetArea, dockTime);
    dockTime->hide();

    dockConfig = new QDockWidget(tr("Config"), this);
    //新建设置窗口
    configView = new Configuration(dockConfig);
    dockConfig->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockConfig->setWidget(configView);
    addDockWidget(Qt::RightDockWidgetArea, dockConfig);
    dockConfig->hide();
}

/**
 * @brief MainWindow::addBinaryConsole 添加console mdi窗口
 */
void MainWindow::initConsoleWindows()
{
    dockBinary = new QDockWidget(tr("Binary"), this);
    binaryConsole = new FrmConsole(dockBinary);
    dockBinary->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockBinary->setWidget(binaryConsole);
    addDockWidget(Qt::BottomDockWidgetArea, dockBinary);
    dockBinary->hide();

    dockText = new QDockWidget(tr("NMEA"), this);
    textConsole = new FrmConsole(dockText);
    dockText->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockText->setWidget(textConsole);
    addDockWidget(Qt::BottomDockWidgetArea, dockText);
    dockText->hide();

//    _40Console = new FrmConsole;
//    _40Console->setEnabled(true);
//    _40Console->setWindowTitle("40");
//    mdiArea->addSubWindow(_40Console);

//    _41Console = new FrmConsole;
//    _41Console->setEnabled(true);
//    _41Console->setWindowTitle("41");
//    mdiArea->addSubWindow(_41Console);

//    _42Console = new FrmConsole;
//    _42Console->setEnabled(true);
//    _42Console->setWindowTitle("42");
//    mdiArea->addSubWindow(_42Console);

//    debugConsole = new FrmConsole;
//    debugConsole->setEnabled(true);
//    debugConsole->setWindowTitle("Debug");
//    mdiArea->addSubWindow(debugConsole);
}

void MainWindow::on_actionConfiguration_View_triggered()
{
    if(dockConfig->isHidden())
        dockConfig->show();
    else
        dockConfig->hide();

}

void MainWindow::on_actionMap_triggered()
{
    mapView->setAutoFillBackground(true);    //将主窗口背景涂黑
    QPalette palette;
    palette.setBrush(QPalette::Background,Qt::black);
    mapView->setPalette(palette);

    if(dockMap->isHidden())
        dockMap->show();
    else
        dockMap->hide();
}

void MainWindow::on_actionRate_triggered()
{
    if(dockRate->isHidden())
        dockRate->show();
    else
        dockRate->hide();
}

void MainWindow::on_actionTime_triggered()
{
    if(dockTime->isHidden())
        dockTime->show();
    else
        dockTime->hide();
}

void MainWindow::on_actionSatPosion_triggered()
{
    if(dockPosition->isHidden())
        dockPosition->show();
    else
        dockPosition->hide();
}

void MainWindow::on_actionSatData_triggered()
{
    if(dockData->isHidden())
        dockData->show();
    else
        dockData->hide();
}

void MainWindow::on_actionSatLevel_triggered()
{
    if(dockLevel->isHidden())
        dockLevel->show();
    else
        dockLevel->hide();
}

void MainWindow::on_actionBinaryConsole_triggered()
{
    if(dockBinary->isHidden())
        dockBinary->show();
    else
        dockBinary->hide();
}

void MainWindow::on_actionTextConsole_triggered()
{
    if(dockText->isHidden())
        dockText->show();
    else
        dockText->hide();
}

void MainWindow::on_actionBrowse_triggered()
{
    QString path = QDir::currentPath();   //获取程序当前目录
    path.replace("/","\\"); //将地址中的"/"替换为"\"，因为在Windows下使用的是"\"。
    QProcess::startDetached("explorer "+path);  //打开上面获取的目录
}
