/**
 * Made for Robotics TeamPi 2021 Build Season
 * Author: Caleb Kyei
 * Date: 10/02/2021 15:30
 * 
 * Remarks: Meant to be used for digital input sensors. eg. IR and ultrasonic sensors
 * 
 **/

#pragma once

#include <frc/DigitalInput.h>


//#include <frc/AnalogInput.h>      //Uncomment if you want to use Analog Trigger or Analog Set Limits


using namespace frc;

class Sensors
{
private:
  DigitalInput *sensor;


public:
  Sensors(int channel);
  ~Sensors();

  bool readSensor();

};
