#include "delay.h"

#include <QDebug>
#include "calib.h"




Delay::Delay(QObject *parent)
    :QThread(parent) {}
//QMutex *mutex = new QMutex(); // Correct alignment
//QMutexLocker locker(mutex);

void Delay::Delay::run()
{
    std::cout<<"Waiting 10sec for coil temperatures to stablize! "<<std::endl;

    QThread::sleep(10);



    // spcify the sparcity (spacial interval) of the data points
    std::array<double,4> x = {0.160,0.160};
    std::array<double,4> y = {0.160,0.160};
    double z = 0.04;

    // specifying the number of layers for the 3D sweep
    int x_layer = 3;
    int y_layer = 3;
    int z_layer = 7;

    abs_EE_loc = {0.160, 0.160, 0.1404};


        //record_status->updateStatus(1);
        // emit writerecord_status(1);


        QThread::sleep(2);

        //record_status->updateStatus(0);
        // emit writerecord_status(0);




        //double duration = 2;// in seconds



        int x_dir = 1;
        int y_dir = 1;

        for(int i = 0; i < z_layer; i++){
            y_dir *=-1; // change direction every turn

            for (int j = 0; j < y_layer; j++){

                x_dir *= -1;
                for(int k = 1; k< x_layer; k++){

//                    relative_robotpos[0] = x_dir* x[k-1];
//                    relative_robotpos[1] = 0;
//                    relative_robotpos[2] = 0;


                    abs_EE_loc[0] += x_dir* x[k-1];
                    abs_EE_loc[1] += 0;
                    abs_EE_loc[2] += 0;
                    // move to the designated point


                    //FrankaCalibration_moves(relative_robotpos, duration);
                    //emit sendArray(relative_robotpos);
                    emit sendArray(abs_EE_loc);


                    //record_status->updateStatus(1);
                    //emit writerecord_status(1);

                    //pause to collect data for 2sec
                    QThread::sleep(4);

                    //record_status->updateStatus(0);
                    //emit writerecord_status(0);


                    }



                if (j == y_layer-1) break;

//                relative_robotpos[0] = 0;
//                relative_robotpos[1] = y_dir*y[j];
//                relative_robotpos[2] = 0;


                abs_EE_loc[0] += 0;
                abs_EE_loc[1] += y_dir*y[j];
                abs_EE_loc[2] += 0;



                //FrankaCalibration_moves(relative_robotpos, duration);
                //emit sendArray(relative_robotpos);
                emit sendArray(abs_EE_loc);

                //record_status->updateStatus(1);
                //emit writerecord_status(1);


                QThread::sleep(4);

                //record_status->updateStatus(0);
                //emit writerecord_status(0);


            }
            if (i == z_layer -1) break;

//            relative_robotpos[0] = 0;
//            relative_robotpos[1] = 0;
//            relative_robotpos[2] = z;

            abs_EE_loc[0] += 0;
            abs_EE_loc[1] += 0;
            abs_EE_loc[2] += z;


            //FrankaCalibration_moves(relative_robotpos, duration);
            //emit sendArray(relative_robotpos);
            emit sendArray(abs_EE_loc);
            //record_status->updateStatus(1);
            // emit writerecord_status(1);


            QThread::sleep(4);

            //record_status->updateStatus(0);
            //emit writerecord_status(0);


        }



    std::cout<<"3D sweep finished. Click stop \"recording button\" to save the file."<<std::endl;



}

//void Delay::FrankaCalibration_moves(double relative_robotpos[3], double& duration)
//{
//    std::cout<< "command relative position in robot frame is: "<<relative_robotpos[0]<<", "<<relative_robotpos[1]<<", "<<relative_robotpos[2]<<std::endl;

//    //move robot in relative position
//    franka::Robot robot(fci_ip);
//try{
//        setDefaultBehavior(robot);
//        // Set additional parameters always before the control loop, NEVER in the control loop!

//        std::array<double, 16> initial_pose;



//        //std::array<double, 16> track_pose;

//        double time = 0;

//        /// ----------------robot control loop---------------------------------
// //        robot.control([=, &time](const franka::RobotState& robot_state,
// //                                 franka::Duration period) -> franka::CartesianVelocities
//                robot.control([&time, &initial_pose, relative_robotpos, &duration]( const franka::RobotState& robot_state,
//                                                     franka::Duration period) -> franka::CartesianPose
//        {
//          if(time == 0.0){initial_pose = robot_state.O_T_EE_c;} // _c
// //          std::copy(robot_state.O_T_EE.begin(), robot_state.O_T_EE.end(), robot_pose.data());
//          //robot_pose = robot_state.O_T_EE;
//          time += period.toSec();

//          // ************ Cycloidal *************

//          std::array<double,16> new_pose = initial_pose;
//          double interpVal = time/duration;
//          new_pose[12] += (relative_robotpos[0]/(M_PI))*(M_PI*interpVal-0.5*std::sin(2*M_PI*interpVal));
//          new_pose[13] += (relative_robotpos[1]/(M_PI))*(M_PI*interpVal-0.5*std::sin(2*M_PI*interpVal));
//          new_pose[14] += (relative_robotpos[2]/(M_PI))*(M_PI*interpVal-0.5*std::sin(2*M_PI*interpVal));
//          if(time>= duration){

//              return franka::MotionFinished(new_pose);}
//          return new_pose;


//          // **************



//         });



//    }catch (const franka::Exception& e) {
//    std::cout << e.what() << std::endl;
//    std::cout << "Running error recovery..." << std::endl;
//    robot.automaticErrorRecovery();
//    }


//}






