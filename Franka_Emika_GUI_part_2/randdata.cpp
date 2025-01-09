#include "randdata.h"
#include <QDebug>
#include "calib.h"


RandData::RandData(int num, bool grid, QObject *parent)
    :QThread(parent),
    num(num), // num specifies the number of randomized current values
    grid(grid){  // specifies if data collection should be in grid pts or randomized

}

void RandData::RandData::run()
{
    std::cout<<"Initializing the randomized data collection! "<<std::endl;

    int counter = 0;

    while(counter < num){

        emit setCurrent(); // set random current to the coil table
        std::cout<<"setting randomized current value: "<<counter<<" of "<<num<<std::endl;
        //QThread::sleep(1);
        emit OrientAdj();    //adjusts Franka's orientation

        QThread::msleep(5000);

            if(grid == false){
                int counter2 = 0;

                while(counter2 < 5){
                    emit move();
                    //moving the robot to the new location = 2sec
                    //pause to collect data for 2sec
                    QThread::msleep(4000);
                    counter2++;
                }

            }
            else {

                // spcify the sparcity (spacial interval) of the data points
                std::array<double,4> x = {0.160,0.160};
                std::array<double,4> y = {0.160,0.160};
                double z = 0.04;

                // specifying the number of layers for the 3D sweep
                int x_layer = 3;
                int y_layer = 3;
                int z_layer = 7;

                abs_EE_loc = {0.160, 0.160, 0.1404};

                emit sendArray(abs_EE_loc);

                QThread::sleep(4);

                int x_dir = 1;
                int y_dir = 1;

                for(int i = 0; i < z_layer; i++){
                    y_dir *=-1; // change direction every turn

                    for (int j = 0; j < y_layer; j++){

                        x_dir *= -1;
                        for(int k = 1; k< x_layer; k++){

                            abs_EE_loc[0] += x_dir* x[k-1];
                            abs_EE_loc[1] += 0;
                            abs_EE_loc[2] += 0;

                            // move to the designated point

                            emit sendArray(abs_EE_loc);

                            //pause to collect data for 2sec
                            QThread::sleep(4);

                            }

                        if (j == y_layer-1) break;

                        abs_EE_loc[0] += 0;
                        abs_EE_loc[1] += y_dir*y[j];
                        abs_EE_loc[2] += 0;


                        emit sendArray(abs_EE_loc);

                        QThread::sleep(4);

                    }




                    if (i == z_layer -1) break;

                    abs_EE_loc[0] += 0;
                    abs_EE_loc[1] += 0;
                    abs_EE_loc[2] += z;

                    emit sendArray(abs_EE_loc);
                    emit OrientAdj();

                    QThread::sleep(8);


                    }
        }

            counter++; //update the the counter

            std::cout<<"Randomized data collection finished. Click stop \"recording button\" to save the file."<<std::endl;

    }

    emit setZeroCurrent(); // sert zero current



}
