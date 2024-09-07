/*
  _____  _ _ _             __  __ _                          _           _   _            _           _     
 |  __ \(_) | |           |  \/  (_)                        | |         | | (_)          | |         | |    
 | |  | |_| | | ___ _ __  | \  / |_  ___ _ __ ___  _ __ ___ | |__   ___ | |_ _  ___ ___  | |     __ _| |__  
 | |  | | | | |/ _ \ '__| | |\/| | |/ __| '__/ _ \| '__/ _ \| '_ \ / _ \| __| |/ __/ __| | |    / _` | '_ \ 
 | |__| | | | |  __/ |    | |  | | | (__| | | (_) | | | (_) | |_) | (_) | |_| | (__\__ \ | |___| (_| | |_) |
 |_____/|_|_|_|\___|_|    |_|  |_|_|\___|_|  \___/|_|  \___/|_.__/ \___/ \__|_|\___|___/ |______\__,_|_.__/ 

-> Filename: SensorDetector.ino
-> Project: Electromagnetic Navigation System Calibration
-> Author: Ardavan Alaei Fard
-> Description: Arduino script for detecting the magnetometers on multiplexers, attached to the Arduino
-> Starting Date: Jul 5, 2023
*/

#include <Wire.h>                           // Include Wire library for I2C communication
#include <SparkFun_I2C_Mux_Arduino_Library.h> // Include SparkFun I2C Mux library
#include <MLX90393.h>                        // Include MLX90393 magnetometer library

QWIICMUX myMux[2];                   // Create two QWIICMUX objects for the two multiplexers
int muxAddress[2] = { 0X70, 0X71 };  // Define the I2C addresses of the multiplexers
int sensorAddress = 0X0C;            // Define the I2C address of the magnetometers
MLX90393 mlx[2][8];                  // Create a 2D array for the magnetometers connected to each multiplexer port
MLX90393::txyz data;  // Create a structure, called data, of four floats (t, x, y, and z) to store magnetometer data

void setup() {
  Serial.begin(57600);  // Initialize serial communication at 57600 baud rate

  Wire.begin();  // Initialize I2C communication

  // Check if both multiplexers are attached
  if (myMux[0].begin(muxAddress[0]) == false || myMux[1].begin(muxAddress[1]) == false) {
    Serial.println("Muxes not detected. Freezing...");
    // If either mux is not detected, enter an infinite loop
    while (myMux[0].begin(muxAddress[0]) == false || myMux[1].begin(muxAddress[1]) == false)
      ;
  }

  // Initialize all ports and magnetometers
  for (int mux = 0; mux < 2; mux++) { // Loop through both multiplexers
    for (int port = 0; port < 8; port++) { // Loop through all 8 ports of each multiplexer
      myMux[mux].enablePort(port);   // Enable the current port
      myMux[mux].setPort(port);      // Set the current port

      Wire.beginTransmission(sensorAddress);
      byte error = Wire.endTransmission();

      if (error == 0) { // If a sensor is detected at the current port
        byte sensorStatus = mlx[mux][port].begin(0, 0); // Initialize the sensor
        // Configure the sensor settings
        mlx[mux][port].setOverSampling(0);
        mlx[mux][port].setDigitalFiltering(0);
        mlx[mux][port].setGainSel(3);
        mlx[mux][port].setResolution(3, 3, 3);
      }
      myMux[mux].disablePort(port);  // Disable the current port
    }
  }
  
  delay(10000);  // Wait for 10 seconds before starting the loop
}

void loop() {
  delay(200); // Wait for 200 milliseconds between each loop iteration

  for (int number = 0; number < 2; number++) { // Loop through both multiplexers
    Wire.beginTransmission(muxAddress[number]);
    byte error = Wire.endTransmission();

    // Check if the mux is attached
    if (error == 0) {
      for (int sensor = 0; sensor < 8; sensor++) { // Loop through all 8 ports of each multiplexer
        myMux[number].enablePort(sensor);  // Enable the current port
        myMux[number].setPort(sensor);     // Set the mux port to check

        Wire.beginTransmission(sensorAddress);
        byte error = Wire.endTransmission();

        // Print the address if a device (a magnetometer in this case) other than the other mux is detected
        if (error == 0) {
          mlx[number][sensor].readData(data); // Read data from the magnetometer
          // Print the x, y, and z values of the magnetometer data
          Serial.print(data.x);
          Serial.print(",");
          Serial.print(data.y);
          Serial.print(",");
          Serial.print(data.z);
          if (sensor == 7 && number == 1)
            Serial.println(); // Print a newline if it's the last sensor of the last mux
          else
            Serial.print(","); // Print a comma to separate values
        } else {
          Serial.print("0,0,0"); // If no sensor is detected, print 0,0,0
          if (sensor == 7 && number == 1)
            Serial.println(); // Print a newline if it's the last sensor of the last mux
          else
            Serial.print(","); // Print a comma to separate values
        }

        myMux[number].disablePort(sensor);  // Disable the current port
      }
    }
  }
}

