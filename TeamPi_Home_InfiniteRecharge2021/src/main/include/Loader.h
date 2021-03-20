#pragma once

#include "Motors.h"
#include "Sensors.h"
#include "RobotConstants.h"

#include <ctre/phoenix.h>
#include <frc/Timer.h>
#include <frc/GenericHID.h>
//#include <frc/Shuffleboard.h>

class Loader
{
private:
  Sensors* IR_LoadSensor;
  Motors* Loader_Motors;
  
  bool isCellDetected();



WPI_TalonFX* shootingMotorMaster = new WPI_TalonFX{9};
WPI_TalonFX* shootingMotorSlave = new WPI_TalonFX{10};



Timer* loaderTimer; //timer for delay for refilling the turret.
Timer* shotingTimer;// timer for amount of seconds that the shoting motors spin.
Timer* testTimer;

//variable for statuses
bool StatusLoader = 0; // status for loading, for controlling it with controller
bool StatusRefill = 1; // status for refilling loader, able to refill loader with a cell. ready = 1, wait = 0.

float StorageDelayTimer = 1; // amount of seconds for the delay
float ShotingDuration = 2;
bool shotingStatus = 0; // status of shooting
int simStatusCase1 = 0;
int simStatusCase2 = 0;
int simStatusCase3 = 0;
int lastIrStatus = 0;
  int currentIrStatus = 0;

//ID of motors
static const int SparkMaxStorageID = 18;
static const int SparkMaxLoaderID = 19;

// speeds of motors
float StorageMotorSpeed = -0.3;
float LoaderMotorSpeed = -0.7;
float turretMotorSpeed = 0.7;
float turretShotingSpeed = 1;

// create motor variable
rev::CANSparkMax SparkMaxStorage{SparkMaxStorageID, rev::CANSparkMax::MotorType::kBrushed}; // storage motor
rev::CANSparkMax SparkMaxLoader{SparkMaxLoaderID, rev::CANSparkMax::MotorType::kBrushed}; //loader motor

  

public:
  //Loader(Sensors* IR_LoadSensor, Motors* Loader_Motors);
  Loader();
  // ~Loader();

  bool loaderTest;
  // void runLoader();
  // void runLoader(double setSpeed);

//variables

int AmountCellsInStorage = 0;// amount cells in storage
bool SimulatingIRSensor = 0;
void LoaderStoreLoad (bool buttonPressed);
void Shoot (int ShootButPressed, bool SimIR);
void refillTurret(int IRSensor);
void test (bool sensor);

// testing functions
void simulating(bool button1, bool button2, bool button3);
void visualisation();
};



