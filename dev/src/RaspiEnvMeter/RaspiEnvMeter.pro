QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    envmeter.cpp \
    model/adevicebase.cpp \
    model/apart.cpp \
    model/cdatetime.cpp \
    model/cdatetimemodel.cpp \
    model/cdht11device.cpp \
    model/cmpl115a1device.cpp \
    model/cpressuremodel.cpp \
    model/craspienvmetermodelbase.cpp \
    model/cgpio.cpp \
    model/ctemperaturemodel.cpp \
    util/util.cpp \
    view/craspienvmetertimeview.cpp \
    view/craspienvmeterview.cpp \
    view/craspienvpressview.cpp \
    view/craspihumidityview.cpp \
    view/craspitemperatureview.cpp

HEADERS += \
    envmeter.h \
    model/adevicebase.h \
    model/apart.h \
    model/cdatetime.h \
    model/cdatetimemodel.h \
    model/cdht11device.h \
    model/cmpl115a1device.h \
    model/cpressuremodel.h \
    model/craspienvmetermodelbase.h \
    model/ctemperaturemodel.h \
    model/gpio_pin_layout.h \
    model/cgpio.h \
    util/util.h \
    view/craspienvmetertimeview.h \
    view/craspienvmeterview.h \
    view/craspienvpressview.h \
    view/craspihumidityview.h \
    view/craspitemperatureview.h

FORMS += \
    envmeter.ui

INCLUDEPATH += \
    ./model \
    ./view \
    ./lib/include

TRANSLATIONS += \
    RaspiEnvMeter_ja_JP.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: linux: {
    target.path = /opt/$${TARGET}/bin
    LIBS += -lpthread \
            -lpigpio
}
else: unix:!android: target.path = /opt/$${TARGET}/bin
