#ifndef DELAY_H
#define DELAY_H
#include <QThread>
#include <QObject>
#include <QMutex>
#include <QMutexLocker>
//#include "SharedResource.h"

#include <QVector>
#include <QMetaType>





class Delay : public QThread
{
     Q_OBJECT
public:
    Delay(QObject *parent = nullptr);

public slots:
    //void stagnate();
//    void FrankaCalibration_moves(double relative_robotpos[3], double& duration);


signals:

    //void writerecord_status(int value);
    void sendArray(const QVector<double> &relative_robotpos);



private:

    int duration;
    std::string fci_ip = "192.168.100.10";
    QMutex mutex;
    // SharedResource *record_status;
    void run() override; // Override the run method to perform thread operations
    QVector<double> relative_robotpos = {0.0, 0.0, 0.0};
    QVector<double> abs_EE_loc;






};

#endif // DELAY_H
