

#include "Intake_Storage_Loader/C04_PI_Pixy.h"

Get_Pixy2::Get_Pixy2(frc::I2C::Port port, int address)
{
  i2cBus = new ArduinoI2C(port, address);
}


uint8_t * Get_Pixy2::GetBlocks(){
  //x value and surface
  static uint8_t check[2];
  i2cBus->read(check,2);
  return check;

}

