QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    airport.cpp \
    airportstrategy.cpp \
    airporttablemodel.cpp \
    caretaker.cpp \
    connection.cpp \
    database.cpp \
    flight.cpp \
    flightstrategy.cpp \
    main.cpp \
    mainwindow.cpp \
    memento.cpp \
    passenger.cpp \
    passengerstrategy.cpp \
    purpose.cpp \
    purposestrategy.cpp \
    staff.cpp \
    staffstrategy.cpp \
    strategycreator.cpp \
    ticket.cpp \
    ticketstrategy.cpp

HEADERS += \
    airport.h \
    airportstrategy.h \
    airporttablemodel.h \
    caretaker.h \
    connection.h \
    creator.h \
    database.h \
    datastrategy.h \
    flight.h \
    flightstrategy.h \
    mainwindow.h \
    memento.h \
    passenger.h \
    passengerstrategy.h \
    purpose.h \
    purposestrategy.h \
    staff.h \
    staffstrategy.h \
    storage.h \
    strategycreator.h \
    ticket.h \
    ticketstrategy.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
