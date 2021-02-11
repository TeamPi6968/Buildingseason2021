#pragma once

#include "Motors.h"
#include "Sensors.h"
#include "RobotConstants.h"

class Loader
{
private:
  Sensors* IR_LoadSensor;
  Motors* Loader_Motors;
  
  bool isCellDetected();

public:
  Loader(Sensors* IR_LoadSensor, Motors* Loader_Motors);
  ~Loader();


  void runLoadMotor();
  void runLoadMotor(double setSpeed);


};



