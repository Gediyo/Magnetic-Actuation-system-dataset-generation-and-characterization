#include "calib.h"
#include "ui_calib.h"
#include "mainwindow.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

Calib::Calib(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::Calib)
    , mainWindow(parent)

{
    ui->setupUi(this);
//    connect(ui->pushbutton_move, &QPushButton::clicked, this, &Calib::on_pushbutton_move_clicked);
//    connect(ui->pushButton_record, &QPushButton::clicked, this, &Calib::on_pushButton_record_clicked);
//    connect(ui->pushButton_stop_record, &QPushButton::clicked, this, &Calib::on_pushButton_stop_record_clicked);
//    connect(ui->pushButton_setReference, &QPushButton::clicked, this, &Calib::on_pushButton_setReference_clicked);
//    connect(sweep, &Delay::sendArray,mainWindow, &MainWindow::FrankaCalibration_moves);

    // Connect the timer timeout signal to the slot
//    timer.setInterval(1000); // 1000 milliseconds (1 second)
//    connect(&timer, &QTimer::timeout, this, &Calib::checkVariable);


}

Calib::~Calib()
{
    delete ui;
//    sweep->quit();
//    sweep->wait();
//    delete sweep;

}



//MainWindow mw;  // Create an instance of MainWindow

//void Calib::on_move_clicked()
//{
////    double x = ui->x_dir ->text().toDouble()/1000; // convert to m
////    double y = ui->y_dir ->text().toDouble()/1000; // convert to m
////    double z = ui->z_dir ->text().toDouble()/1000; // convert to m


////    double relative_robotpos[3];

////    relative_robotpos[0] = x;
////    relative_robotpos[1] = y;
////    relative_robotpos[2] = z;

////    relative_robotpos[0] = 0;
////    relative_robotpos[1] = 0;
////    relative_robotpos[2] = 0;

//    mainWindow->startThread();



//}



//    double I_command[8] = {0,0,0,0,0,0,0,0}; // coil current values
//    mainWindow->updateCurrents_CalibrationOnly(I_command); // to set coil current vaues

//    parentMainWindow->CloseFiles(); // close the file

void Calib::updateStatus(int running){
    if(running == 4){
        ui->radioButton_record_status->setChecked(1);
        ui->radioButton_record_status->setText("Recording");

    }else if(running == 3){
        ui->radioButton_record_status->setChecked(0);
        ui->radioButton_record_status->setText("Recording Paused");
        ui->pushButton_pauseRecording->setText("Resume Recoding");

    }else{
    ui->radioButton_record_status->setChecked(running);
    ui->radioButton_record_status->setText(running ? "Recording" : "Recording Stopped");
    }
}


void Calib::on_pushButton_record_clicked()
{
    mainWindow->record_status= 1;
    mainWindow->Record_calibdata(); // record calibration data
    running = 1;
    updateStatus(running);
}


void Calib::on_pushButton_stop_record_clicked()
{
    mainWindow->record_status = 0;
    mainWindow->Close_Calib_File(); // close the file
    running = 0;
    updateStatus(running);
}

void Calib::on_pushButton_pauseRecording_clicked()
{

    if(mainWindow->record_status ==  1){
        mainWindow->record_status = 0;
        running = 3;
        updateStatus(running);
        std::cout<<"Recording Paused. "<<std::endl;
    }else if (mainWindow->record_status == 0){
        mainWindow->record_status = 1;
        running = 4;
        updateStatus(running);
        std::cout<<"Recording Resumed. "<<std::endl;
    }

}



void Calib::on_pushButton_setReference_clicked()
{
    franka::Robot robot(mainWindow->fci_ip);
    //read franka robot pose
    franka::RobotState initial_state = robot.readOnce();

    Eigen::Affine3d initial_transform(Eigen::Matrix4d::Map(initial_state.O_T_EE.data())); // transformation matrix


    // get the transformation matrix from the robot base to the end effectot
    Eigen::Affine3d T_EO = initial_transform.inverse();

    // creating a transformation matrix from the robot end effector to to coil table
    // Create an affine transformation (Identity matrix as a base)
    mainWindow->T_TE = Eigen::Affine3d::Identity();

    // Apply some transformations: translation, rotation
    mainWindow->T_TE.translate(Eigen::Vector3d(0.0, 0.0, 106.4e-3));
    mainWindow->T_TE.rotate(Eigen::AngleAxisd(M_PI , Eigen::Vector3d::UnitX()));
    mainWindow->T_TE.rotate(Eigen::AngleAxisd(M_PI/4 , Eigen::Vector3d::UnitZ()));

    // calculate the transformation matrix from the robot base to the coil table orign
    mainWindow->T_TO = mainWindow->T_TE * T_EO;

    std::cout<<"Reference position has been set! "<<std::endl;
    std::cout<<"Transformation matrix from robot frame to coil Table frame, T_TO: \n"<<mainWindow->T_TO.matrix()<<std::endl;


}



void Calib::on_pushbutton_move_clicked()
{
    double x = ui->x_dir ->text().toDouble()/1000; // convert to m
    double y = ui->y_dir ->text().toDouble()/1000; // convert to m
    double z = ui->z_dir ->text().toDouble()/1000; // convert to m

    QVector<double> relative_robotpos = {0.0, 0.0, 0.0};


    relative_robotpos[0] = x;
    relative_robotpos[1] = y;
    relative_robotpos[2] = z;


    mainWindow->Franka_EERel_MovesInTableFrame(relative_robotpos);

}

void Calib::on_pushButton_start_3D_sweep_clicked()
{

    mainWindow->start_calib_sweep();

    //    mainWindow->runnig_temp_timer->start(5000);
    //    timer.start();



}

void Calib::start_sweep(){
    //mainWindow->startThread();

//    std::cout<<"3D sweep started! "<<std::endl;
//    sweep = new Delay();
//    sweep->start();
}

//void Calib::checkVariable() {
//    if (mainWindow->calc_run_temp_avg == 0) {
//        timer.stop();
//        std::cout<<"Coil temperatures have stablized! "<<std::endl;
//        std::cout<<"Starting data collection "<<std::endl;
//        start_sweep();
//    }
//}

void Calib::on_pushButton_init_pos_clicked()
{

    QVector<double> r_T_PT = {0.160, 0.160, 0.1404};

    mainWindow->T_TE = Eigen::Affine3d::Identity();

    // Apply some transformations: translation, rotation
    mainWindow->T_TE.translate(Eigen::Vector3d(0.0, 0.0, 106.4e-3));
    mainWindow->T_TE.rotate(Eigen::AngleAxisd(M_PI , Eigen::Vector3d::UnitX()));
    mainWindow->T_TE.rotate(Eigen::AngleAxisd(M_PI/4 , Eigen::Vector3d::UnitZ()));

    Eigen::Affine3d T_EO = mainWindow->T_TE.inverse() * mainWindow->T_TO;


    Eigen::Matrix3d rotMat(T_EO.inverse().linear()); // rotation matrix in robot frame

    //std::array<double, 3> EulerAngles = mainWindow->RotMat2EulerAngle(rotMat)

    mainWindow->FrankaMovesInTableFrame(r_T_PT);
    mainWindow->FrankaAbsOrientmotion(rotMat);
}

void Calib::on_pushButton_GausstoOrigin_clicked()
{
    QVector<double> r_T_PT = {-0.065875, 0.000, 0.352925};
    mainWindow->T_TE = Eigen::Affine3d::Identity();

    // Apply some transformations: translation, rotation
    mainWindow->T_TE.translate(Eigen::Vector3d(0.0, 0.0, 106.4e-3));
    mainWindow->T_TE.rotate(Eigen::AngleAxisd(M_PI , Eigen::Vector3d::UnitX()));
    mainWindow->T_TE.rotate(Eigen::AngleAxisd(M_PI/4 , Eigen::Vector3d::UnitZ()));


    Eigen::Affine3d T_EO = mainWindow->T_TE.inverse() * mainWindow->T_TO;


    Eigen::Matrix3d rotMat(T_EO.inverse().linear()); // rotation matrix in robot frame

    //std::array<double, 3> EulerAngles = mainWindow->RotMat2EulerAngle(rotMat)

    mainWindow->FrankaMovesInTableFrame(r_T_PT);
    mainWindow->FrankaAbsOrientmotion(rotMat);


}


