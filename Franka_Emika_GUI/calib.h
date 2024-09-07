#ifndef CALIB_H
#define CALIB_H
#include "mainwindow.h" // Include MainWindow header to access it
#include <QMainWindow> // Include QMainWindow if needed
#include "delay.h"

#include <QWidget>
#include <Eigen/Dense>

namespace Ui {
class Calib;
}

class MainWindow;

class Calib : public QWidget
{
    Q_OBJECT

public:
    explicit Calib(MainWindow *parent = nullptr);
    ~Calib();
    int running = 0;
    int durationMs = 2000; //duration in milli-seconds

private slots:

//    void on_move_clicked();
    void updateStatus(int running);

    void on_pushButton_record_clicked();

    void on_pushButton_stop_record_clicked();

    void on_pushButton_pauseRecording_clicked();

    void on_pushButton_setReference_clicked();


    void on_pushbutton_move_clicked();

    void on_pushButton_start_3D_sweep_clicked();

    void start_sweep();

//    void checkVariable();


    void on_pushButton_init_pos_clicked();

    void on_pushButton_GausstoOrigin_clicked();


private:
    Ui::Calib *ui;
    MainWindow *mainWindow;
//    Delay *sweep;
//    QTimer timer;

};

#endif // CALIB_H
