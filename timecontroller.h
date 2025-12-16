#ifndef TIMECONTROLLER_H
#define TIMECONTROLLER_H

#include <QObject>
#include <QTimer>

class TimeController : public QObject
{
    Q_OBJECT
private:
    QTimer* timer;
public:
    explicit TimeController(QObject *parent = nullptr);
    void Timer();
signals:
    void NotifyFlight();
};

#endif // TIMECONTROLLER_H
