
#pragma once

#include <iostream>
#include "ArduinoI2C.h"
#include <vector>


#define PIXY_HEIGHT 51
#define PIXY_WIDTH 78


class Get_Pixy2{

    private:

    ArduinoI2C *i2cBus;

    public:
    //This needs the port and address and creates a connection with the arduino
    //returns nothing
    Get_Pixy2(frc::I2C::Port port, int address);
   
    uint8_t * GetBlocks();

};
