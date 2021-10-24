/*
Arduino to RoboRio over I2C

This library handles the communication with an arduino over I2C with the arduino as a slave.

Connect the arduino directly to the roboRio I2C port. The roboRio is 5V tolerant.

Created by Eduard Cazacu on 07 February 2019
Team PI 6968
*/

#pragma once

#include <frc/I2C.h>

class ArduinoI2C
{
  public:
    /*
        Description:    Arduino communication over I2C object
        Input:          Port - the I2C Port
                        Address [uint8_t] - the I2C address of the arduino
        Output:         None;
    */
    ArduinoI2C(frc::I2C::Port port, uint8_t address);

    /*
        Description:    Send data to the arduino
        Input:          pointer to 8 bit data and number of bytes to be sent
        Output:         error?
    */
    bool write(uint8_t *data, int count);

    /*
        Description:    Read data from the arduino
        Input:          pointer to where to store the data and number of bytes to be read
        Output:         error?
    */
    bool read(uint8_t *data, int count);

  private:
    frc::I2C *_i2c;
};
