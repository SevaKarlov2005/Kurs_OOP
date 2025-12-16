#include "timecontroller.h"
#include <QThread>

TimeController::TimeController(QObject *parent)
    : QObject{parent}
{

}

void TimeController::Timer()
{
    this->timer = new QTimer();
    this->timer->setInterval(60000);

    connect(this->timer, &QTimer::timeout, this, &TimeController::NotifyFlight);

    this->timer->start();

    emit NotifyFlight();
}
