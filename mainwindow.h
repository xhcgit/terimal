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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QDockWidget>
#include <QFile>
#include <QMainWindow>
#include <QMdiArea>

#include <QtSerialPort/QSerialPort>
#include "Configuration.h"
#include "frmConsole.h"
#include "mdichild.h"
#include "mytool.h"
#include "map.h"
#include "rate.h"
#include "utctime.h"
#include "satmessage.h"
#include "position.h"
#include "satellitedata.h"
#include "Level.h"
QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readANmeaSentence(QByteArray data, int begin);
    void newFile();
    MdiChild *createMdiChild();


private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void pickAndPrintRawData(QByteArray ba, bool success);

    void on_actionConfiguration_View_triggered();

    void on_actionMap_triggered();

    void on_actionRate_triggered();

    void on_actionTime_triggered();

    void on_actionSatPosion_triggered();

    void on_actionSatData_triggered();

    void on_actionSatLevel_triggered();


    void on_actionBinaryConsole_triggered();

    void on_actionTextConsole_triggered();

    void on_actionBrowse_triggered();

private:
    Ui::MainWindow *ui;
    SettingsDialog *settings;
    QSerialPort *serial;
    Configuration *configView;
    QFile file;
    map *mapView;
    rate *rateView;
    utcTime *utctimeView;
    satMessage *satellites;
    position *positionView;    //卫星位置地图
    satelliteData *satDataView;    //卫星信息
    level *levelView;

    QDockWidget *dockLevel;
    QDockWidget *dockData;
    QDockWidget *dockPosition;
    QDockWidget *dockMap;
    QDockWidget *dockRate;
    QDockWidget *dockTime;
    QDockWidget *dockText;
    QDockWidget *dockBinary;
    QDockWidget *dockConfig;


    QMdiArea *mdiArea;
    FrmConsole *binaryConsole;
    FrmConsole *textConsole;
    FrmConsole *debugConsole;
    FrmConsole *_40Console;
    FrmConsole *_41Console;
    FrmConsole *_42Console;

    void initConsoleWindows();
    void initActionsConnections();
    void processRawData(QByteArray ba);
    void processNmeaData(QByteArray ba);
    void createDockWindows();
};

#endif // MAINWINDOW_H
