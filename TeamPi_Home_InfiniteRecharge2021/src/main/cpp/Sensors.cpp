#include "Sensors.h"

/**
 * 
 * @param channel This is the DIO channel used on the Roborio 
 * 
 **/ 
Sensors::Sensors(int channel){
  this->sensor = new DigitalInput(channel);
}

Sensors::~Sensors(){
  
}

//Returns true or false depending on the digital sensor value
bool Sensors::readSensor(){
  return this->sensor->Get();
}



