QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    airport.cpp \
    airportdialog.cpp \
    airportnamedialog.cpp \
    airportproxymodel.cpp \
    airportstrategy.cpp \
    airporttablemodel.cpp \
    airportwindow.cpp \
    caretaker.cpp \
    connection.cpp \
    database.cpp \
    flight.cpp \
    flightdialog.cpp \
    flightproxymodel.cpp \
    flightstrategy.cpp \
    flighttablemodel.cpp \
    flightwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    memento.cpp \
    nominationdialog.cpp \
    numcertificatedialog.cpp \
    numflightdialog.cpp \
    numpassportdialog.cpp \
    numticketdialog.cpp \
    passenger.cpp \
    passengerdialog.cpp \
    passengerproxymodel.cpp \
    passengerstrategy.cpp \
    passengertablemodel.cpp \
    passengerwindow.cpp \
    purpose.cpp \
    purposedialog.cpp \
    purposeproxymodel.cpp \
    purposestrategy.cpp \
    purposetablemodel.cpp \
    purposewindow.cpp \
    staff.cpp \
    staffdialog.cpp \
    staffproxymodel.cpp \
    staffstrategy.cpp \
    stafftablemodel.cpp \
    staffwindow.cpp \
    strategycreator.cpp \
    ticket.cpp \
    ticketdialog.cpp \
    ticketproxymodel.cpp \
    ticketstrategy.cpp \
    tickettablemodel.cpp \
    ticketwindow.cpp \
    timecontroller.cpp

HEADERS += \
    airport.h \
    airportdialog.h \
    airportnamedialog.h \
    airportproxymodel.h \
    airportstrategy.h \
    airporttablemodel.h \
    airportwindow.h \
    caretaker.h \
    connection.h \
    creator.h \
    database.h \
    datastrategy.h \
    flight.h \
    flightdialog.h \
    flightproxymodel.h \
    flightstrategy.h \
    flighttablemodel.h \
    flightwindow.h \
    mainwindow.h \
    memento.h \
    nominationdialog.h \
    numcertificatedialog.h \
    numflightdialog.h \
    numpassportdialog.h \
    numticketdialog.h \
    passenger.h \
    passengerdialog.h \
    passengerproxymodel.h \
    passengerstrategy.h \
    passengertablemodel.h \
    passengerwindow.h \
    purpose.h \
    purposedialog.h \
    purposeproxymodel.h \
    purposestrategy.h \
    purposetablemodel.h \
    purposewindow.h \
    staff.h \
    staffdialog.h \
    staffproxymodel.h \
    staffstrategy.h \
    stafftablemodel.h \
    staffwindow.h \
    storage.h \
    strategycreator.h \
    ticket.h \
    ticketdialog.h \
    ticketproxymodel.h \
    ticketstrategy.h \
    tickettablemodel.h \
    ticketwindow.h \
    timecontroller.h

FORMS += \
    airportdialog.ui \
    airportnamedialog.ui \
    airportwindow.ui \
    flightdialog.ui \
    flightwindow.ui \
    mainwindow.ui \
    nominationdialog.ui \
    numcertificatedialog.ui \
    numflightdialog.ui \
    numpassportdialog.ui \
    numticketdialog.ui \
    passengerdialog.ui \
    passengerwindow.ui \
    purposedialog.ui \
    purposewindow.ui \
    staffdialog.ui \
    staffwindow.ui \
    ticketdialog.ui \
    ticketwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
