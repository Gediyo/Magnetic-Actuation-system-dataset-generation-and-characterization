#ifndef RANDDATA_H
#define RANDDATA_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QThread>

#include <QVector>
#include <QMetaType>

class RandData: public QThread
{
    Q_OBJECT
public:
    RandData(int num, bool grid, QObject *parent = nullptr);


public slots:
    //void stagnate();
//    void FrankaCalibration_moves(double relative_robotpos[3], double& duration);


signals:

    //void writerecord_status(int value);
    void move();
    void OrientAdj();
    void setCurrent();
    void setZeroCurrent();
    void sendArray(const QVector<double> &relative_robotpos);



private:
    int num;
    bool grid;
    int duration;
    std::string fci_ip = "192.168.100.10";
    // QMutex mutex;
    // SharedResource *record_status;
    void run() override; // Override the run method to perform thread operations
    QVector<double> abs_EE_loc;


};

#endif // RANDDATA_H
