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
  Loader(Motors* Loader_Motors);
  Loader(Sensors* IR_LoadSensor, Motors* Loader_Motors);
  ~Loader();


  void runLoader();
  void runLoader(double setSpeed);

};

class Storage
{
private:
  Motors* Storage_Motors;

public:
  Storage(Motors* Storage_Motors);
  ~Storage();

  void runStorage();
  void runStorage(double setSpeed);
};






