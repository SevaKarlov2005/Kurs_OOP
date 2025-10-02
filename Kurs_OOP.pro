QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    airport.cpp \
    caretaker.cpp \
    connection.cpp \
    flight.cpp \
    main.cpp \
    mainwindow.cpp \
    memento.cpp \
    passenger.cpp \
    purpose.cpp \
    staff.cpp \
    ticket.cpp

HEADERS += \
    airport.h \
    caretaker.h \
    connection.h \
    datastrategy.h \
    flight.h \
    mainwindow.h \
    memento.h \
    passenger.h \
    purpose.h \
    staff.h \
    storage.h \
    ticket.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
