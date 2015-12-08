greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET = terminal
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    mdichild.cpp \
    FrmConsole.cpp \
    dataprocess.cpp \
    SharedData.cpp \
    Nmea.cpp \
    NmeaParser.cpp \
    Configuration.cpp \
    map.cpp \
    rate.cpp \
    utctime.cpp \
    satmessage.cpp \
    position.cpp \
    satellitedata.cpp \
    Level.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    mdichild.h \
    mytool.h \
    config.h \
    FrmConsole.h \
    dataprocess.h \
    SharedData.h \
    Nmea.h \
    NmeaParser.h \
    Configuration.h \
    map.h \
    rate.h \
    utctime.h \
    satmessage.h \
    position.h \
    satellitedata.h \
    Level.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    FrmConsole.ui \
    Configuration.ui \
    map.ui \
    rate.ui \
    utctime.ui \
    position.ui \
    satellitedata.ui \
    Level.ui

RESOURCES += \
    terminal.qrc

DISTFILES +=


