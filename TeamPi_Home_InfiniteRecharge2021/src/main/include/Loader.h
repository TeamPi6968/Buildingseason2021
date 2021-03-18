#pragma once

#include "Motors.h"
#include "Sensors.h"
#include "RobotConstants.h"
#include <frc/DigitalInput.h>

class Loader
{
private:
  // Sensors* IR_LoadSensor;
  // Motors* Loader_Motors;
  
  // bool isCellDetected();


//
// WPI_TalonFX shooting= new WPI_TalonFX{9};
// WPI_TalonFX shootingReverse= new WPI_TalonFX{10};

//variable for statuses
bool StatusLoader = 0; // status for loading, for controlling it with controller
bool StatusRefill = 1; // status for refilling loader, able to refill loader with a cell. ready = 1, wait = 0.
int AmountCellsInStorage = 0;// amount cells in storage


//ID of motors
static const int SparkMaxStorageID = 18;
static const int SparkMaxLoaderID = 19;

// speeds of motors
float StorageMotorSpeed = -0.2;
float LoaderMotorSpeed = -0.6;

// create motor variable
rev::CANSparkMax SparkMaxStorage{SparkMaxStorageID, rev::CANSparkMax::MotorType::kBrushed}; // storage motor
rev::CANSparkMax SparkMaxLoader{SparkMaxLoaderID, rev::CANSparkMax::MotorType::kBrushed}; //loader motor

  

public:
  // Loader(Sensors* IR_LoadSensor, Motors* Loader_Motors);
  // ~Loader();

  bool loaderTest;
  // void runLoader();
  // void runLoader(double setSpeed);

//variables


void LoaderStoreLoad (bool buttonPressed);
void Shoot (int ShootButPressed, bool SimIR);
void refillTurret(int IRSensor, bool SimIr);
void test (bool sensor);
};



