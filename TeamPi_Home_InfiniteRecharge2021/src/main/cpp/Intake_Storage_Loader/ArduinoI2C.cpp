#include "Intake_Storage_Loader/ArduinoI2C.h"

/*
        Description:    Arduino communication over I2C object
        Input:          Port - the I2C Port
                        Address [uint8_t] - the I2C address of the arduino
        Output:         None;
*/
ArduinoI2C::ArduinoI2C(frc::I2C::Port port, uint8_t address)
{
    this->_i2c = new frc::I2C(port, address);
}
/*
        Description:    Send data to the arduino
        Input:          pointer to 8 bit data and number of bytes to be sent
        Output:         error?
*/
bool ArduinoI2C::write(uint8_t *data, int count)
{
    uint8_t *received = new uint8_t();
    return _i2c->Transaction(data, count, received, count);
}
/*
        Description:    Read data from the arduino
        Input:          pointer to where to store the data and number of bytes to be read
        Output:         error?
*/
bool ArduinoI2C::read(uint8_t *data, int count)
{
    //send some garbage data to notify the arduino of a request:
    //uint8_t garbage = 0xFF;
    //return _i2c->Transaction(&garbage,1,data,count);
    return _i2c->ReadOnly(count, data);
}