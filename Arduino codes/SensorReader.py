"""
  _____  _ _ _             __  __ _                          _           _   _            _           _     
 |  __ \(_) | |           |  \/  (_)                        | |         | | (_)          | |         | |    
 | |  | |_| | | ___ _ __  | \  / |_  ___ _ __ ___  _ __ ___ | |__   ___ | |_ _  ___ ___  | |     __ _| |__  
 | |  | | | | |/ _ \ '__| | |\/| | |/ __| '__/ _ \| '__/ _ \| '_ \ / _ \| __| |/ __/ __| | |    / _` | '_ \ 
 | |__| | | | |  __/ |    | |  | | | (__| | | (_) | | | (_) | |_) | (_) | |_| | (__\__ \ | |___| (_| | |_) |
 |_____/|_|_|_|\___|_|    |_|  |_|_|\___|_|  \___/|_|  \___/|_.__/ \___/ \__|_|\___|___/ |______\__,_|_.__/ 

-> Filename: SensorReader.py
-> Project: Electromagnetic Navigation System Calibration
-> Author: Ardavan Alaei Fard
-> Edited by: Gediyon M. Girma (2024-07-18) - added comments and added time & date stamp to the data collection
-> Description: Script for reading the values from the Arduino and save the data
-> Starting Date: Jul 14, 2023
"""

import serial
import numpy as np
import pandas as pd
import datetime


class SensorArray:
    def __init__(self, 
                 # check the comport by going to tools > port in the arduino IDE after pluging the arduino to your computer
                 #  comPort: str = '/dev/ttyACM0',
                 comPort: str = 'COM3', # for windows, 
                 baudRate: int = 57600,
                 timeout: float = 1.0,
                 conversionFactor: float = 1e-3):
        """
        Construct the class
        """
        self.ser = serial.Serial(comPort, baudRate, timeout=timeout)
        self.currentMeasurement = np.empty(shape=(1, 49), dtype=float).reshape((1, 49))
        self.calibrationOffsets = np.zeros(shape=(1, 49), dtype=float).reshape((1, 49))
        self.conversionFactor = conversionFactor
        self.listData = []
        self.csvData = {}
        self.directions = ['X', 'Y', 'Z']

    def measure(self):
        """
        read the data line from Serial
        """
        # Read a line from the serial port and decode it
        sensorValue = self.ser.readline().decode().split(',')   # Make a list from the reading data
        
        now = datetime.datetime.now().isoformat()
        
        # Check if the length of the sensor data is 48 (valid data length)
        if len(sensorValue) == 48:   # Check if the reading is valid
            
            # Remove the last two characters from the last item in the list (likely to remove unwanted characters like newline)
            sensorValue[-1] = sensorValue[-1][:-2]
            
            # Convert all items in the list from strings to floats and store them in currentMeasurement
            
                       
            sensorValue = list(map(float, sensorValue))
            
            # Create a list to store the current measurement
            self.currentMeasurement = [now] + sensorValue
            
                        
            # Check if the first value in the measurement is less than 1000
            # (This could be a sanity check to ensure the values are within expected range)
            
            if self.currentMeasurement[2] < 1000:
                return True
            
        # If the length of sensorValue is not 48 or the first value is not less than 1000, return False
        return False
    
    def calibrate(self, calibrationSize):
        """
        Calibrate the all connected magnetometers
        """
        #  Initialize an empty array to store calibration data
        self.calibrateData = np.empty(shape=(calibrationSize, 48), dtype=float).reshape((calibrationSize, 48))
        
        # Collect data for calibrationSize iterations
        for count in range(calibrationSize):
            # Continuously attempt to read valid sensor data
            while self.measure() == False:
                pass
            
            # Store the valid sensor data in the calibration array
            self.calibrateData[count] = self.currentMeasurement[1:]
        
        # Calculate the mean of the collected calibration data to determine the offsets
        self.calibrationOffsets = np.mean(self.calibrateData, axis=0, dtype=float)   # Get average as the offset

    def dataCollection(self):
        """
        Collect data from reading the Serial
        """
        # Start an infinite loop to collect data continuously
        while(1):
            try:
                start_time = datetime.datetime.now().strftime("%d-%m-%Y_%H-%M-%S")
                
                # Measure the current data
                self.measure()               
                
                # Apply calibration offsets and conversion factor to the current measurement
                self.currentMeasurement[1:] = (self.currentMeasurement[1:] - self.calibrationOffsets) * self.conversionFactor   # Subtract the offset, change to mT
                
                # Append the calibrated and converted data to the listData
                self.listData.append(self.currentMeasurement)
                
                print(self.currentMeasurement)
                
            except:    # The end of data collection process (unplugging the arduino or when serial connection is lost)
                
                # Convert listData to a NumPy array and transpose it, then convert it to a list
                self.listData = np.array(self.listData).T.tolist()
                
                # assignning the first column as timestamp
                self.csvData["TimeStamp"] = self.listData[0]
                
                # Initialize the queryIndex for iterating over listData
                queryIndex = 1   # The list index to query
                
                # Populate the csvData dictionary with the sensor data
                for mux in range(2):
                    for sensor in range(8):
                        for dir in self.directions:
                            
                            # Create a column name for each sensor direction
                            # columnName = f"mux{mux + 1}_sensor{sensor}_{dir} [mT]"
                            columnName = f"sensor_{(mux*8)+(sensor+1)}_{dir} [mT]"
                            
                            # Add the data to the csvData dictionary
                            self.csvData[columnName] = self.listData[queryIndex]
                            
                            queryIndex += 1     # increment the query index
                
                # Create dataframe and save the data into csv file
                dataframe = pd.DataFrame(self.csvData)
                
                # Print the DataFrame for verification
                print(dataframe)
                
                file_name = f"./Data/{start_time}_Mangnetometer_sensor_data.csv"
                
                # Save the DataFrame to a CSV file
                dataframe.to_csv(file_name, index=False)
                
                # Break the loop after saving the data
                break

if __name__ == '__main__':
    """
    Main function
    Key steps for using the code:
    1.  Upload SensorReader.ino to the Arduino, then unplug the Arduino
    2.  Make sure the port you are using the Arduino with matches the one mentioned in line 23.
        If not, change it to the desired one in line 23.
    3.  Plug in back the Arduino
    4.  Run the code in less than 10 seconds after the Arduino is plugged in
    5.  End the data collection only and only by unplugging the Arduino
    """
    sensors = SensorArray()
    print("Starting Calibration ...")
    sensors.calibrate(calibrationSize=20) 
    print("Calibration complete")
    sensors.dataCollection()