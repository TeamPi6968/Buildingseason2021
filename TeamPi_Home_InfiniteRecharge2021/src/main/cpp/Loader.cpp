#include "Loader.h"

#include <iostream>

using namespace std;

Loader::Loader()
{
  /*Loader::Loader(Sensors* IR_LoadSensor, Motors* Loader_Motors){
  this->IR_LoadSensor = IR_LoadSensor;
  this->Loader_Motors = Loader_Motors;

*/
  shootingMotorMaster->SetInverted(TalonFXInvertType::Clockwise);
  shootingMotorSlave->SetInverted(TalonFXInvertType::CounterClockwise);
  loaderTimer = new Timer();
  loaderTimer->Reset();
  shotingTimer = new Timer();
  shotingTimer->Reset();
  testTimer = new Timer();
  testTimer->Reset();
}

//Loader::~Loader(){}
/*
bool Loader::isCellDetected(){
  return this->IR_LoadSensor->readSensor();
}

void Loader::runLoader(){
  if(isCellDetected()){
    Loader_Motors->GetSparkMax()->Set(LoaderMotorSpeed);
  }
  else{
    Loader_Motors->GetSparkMax()->StopMotor();
  }
}

void Loader::runLoader(double setSpeed){
  Loader_Motors->GetSparkMax()->Set(setSpeed);
}
*/

/*
*/
void Loader::LoaderStoreLoad(bool buttonPressed)
{
  if (buttonPressed)
  {
    if (StatusLoader == 0)
    {
      //change status to go out
      StatusLoader = 1;
      //spin spark motorscontrollers for Loader and storage
      SparkMaxStorage.Set(StorageMotorSpeed);
      SparkMaxLoader.Set(LoaderMotorSpeed);
      cout << "Spinnn!!!" << endl;
    }

    else if (StatusLoader == 1)
    {
      //change status to go in
      StatusLoader = 0;
      //stop motor
      SparkMaxStorage.Set(0);
      SparkMaxLoader.Set(0);
      cout << "Spin stopppp" << endl;
    }
  }
}
/*
// function will shoot a ball when a ball is present at the ir and command is given.
void Loader::Shoot(int ShootButPressed, bool IRSensor) // change SIMir when for 'IRsensor' when code works.
{

  if (ShootButPressed && AmountCellsInStorage > 0)
  {
    shotingStatus = 1;
    cout << "shotingstatus = 1" << endl;
    //shotingTimer->Reset();
  }

  if (shotingStatus == 1 && IRSensor)
  {
    //spin motors for couple of seconds, after seconds 'StatusRefill = 1'
    shotingTimer->Start(); //starts timer for duration
    cout << " shoting" << endl;
    // spin motor falcon shoting motor ID:

    // spin loaderMotor spark max ID: 18
    SparkMaxLoader.Set(LoaderMotorSpeed);
    //change status for refill loader
    StatusRefill = 0; //change status, so storage wont refill
    // if (true)
    if (shotingTimer->HasPeriodPassed(ShotingDuration)) // after shoting duration
    {
      // stop motor falcon CAN ID:
      cout << " shoting stopped" << endl;
      SparkMaxLoader.Set(0); //stops motor
      shotingStatus == 0;    //change shoting status
      shotingTimer->Reset(); //resets timer
      StatusRefill = 1;      //refill is possible
    }
  }
}
*/

void Loader::Shoot(int ShootButPressed, bool IRSensor)
{
  lastIrStatus = currentIrStatus;
  currentIrStatus = IRSensor;
  if (lastIrStatus == 1 && currentIrStatus == 0)
  {
    AmountCellsInStorage--;
   
    if (AmountCellsInStorage <= 0)
    {
      AmountCellsInStorage = 0;
      shotingStatus = 0;
    }
     cout << "amount cells is " << AmountCellsInStorage << endl;
  }

  if (ShootButPressed && AmountCellsInStorage > 0 && IRSensor)
  {
    shotingStatus = 1;
    cout << "shotingstatus = 1" << endl;
    //shotingTimer->Reset();

    if (shotingStatus == 1)
    {
      shotingTimer->Start();
      if (!(shotingTimer->HasPeriodPassed(ShotingDuration)))
      {
        cout << " shoting" << endl;
        // spin motor falcon shoting motor ID:

        shootingMotorMaster->Set(turretShotingSpeed);
        shootingMotorSlave->Set(turretShotingSpeed);

        // SparkMaxStorage.Set(StorageMotorSpeed);

        // spin loaderMotor spark max ID: 18
        SparkMaxLoader.Set(LoaderMotorSpeed);
        //change status for refill loader
        //cout << shotingTimer->Get();
        StatusRefill = 0;
      }
      // stop motor falcon CAN ID:
      shootingMotorMaster->Set(0);
      shootingMotorSlave->Set(0);
      cout << " shoting stopped" << endl;
      //cout << shotingTimer->Get();

      SparkMaxLoader.Set(0); //stops motor
      shotingStatus == 0;    //change shoting status
      shotingTimer->Stop();
      shotingTimer->Reset(); //resets timer
      StatusRefill = 1;      //refill is possible

      SparkMaxStorage.Set(0); // stops motor
    }
  }
}
/*
// function will spin storage motor when there are cells in the storage and no cell is above the IR sensor. i
// it will stop when a cell is above IR sensor.
void Loader::refillTurret(int IRSensor)
{
  int IRstatus;
  int IRstatusNew;
  if (IRSensor)
  {
    IRstatus = 0;
  }
  else
  {
    IRstatus = 1;
  }

  if (IRstatus == 1 and IRstatus != IRstatusNew)
  {
    AmountCellsInStorage = AmountCellsInStorage--; // subtracs value of amount
    IRstatusNew = IRstatus;
  }

  if (IRstatus == 1)
  {
    cout << "ir sensor changed status" << endl;
    IRstatusNew = IRstatus;
  }
  if (AmountCellsInStorage > 0 && !IRSensor)
  {
    //spin storageMotor ID: 19;
    SparkMaxStorage.Set(StorageMotorSpeed);

    cout << "refill storage" << endl;
    // cout << "amount cells is "<< AmountCellsInStorage << endl;
  }
  else
  {
    SparkMaxStorage.Set(0);
  }
}
*/

void Loader::refillTurret(int IRsensor)
{

  if (IRsensor && AmountCellsInStorage > 0)
  {
    //spin storageMotor ID: 19;
    SparkMaxStorage.Set(StorageMotorSpeed);

    // cout << "refill storage" << endl;
    // cout << "amount cells is "<< AmountCellsInStorage << endl;
  }
  else
  {
    // cout << "refill stoped" << endl;
    SparkMaxStorage.Set(0);
  }

  if (AmountCellsInStorage > 0)
  {
    shotingStatus == 1;
    // cout << "more than 0" << endl;
  }
}

// just a function to test things.
void Loader::test(bool sensor)
{
}

// fucntion to simulate values for testing.
void Loader::simulating(bool button1, bool button2, bool button3)
{
  if (button1)
  {
    if (simStatusCase1 == 1)
    {
      AmountCellsInStorage++;
      simStatusCase1 = 0;
      cout << " cells is " << AmountCellsInStorage << endl;
    }
    else if (simStatusCase1 == 0)
    {
      //AmountCellsInStorage = 0;
      simStatusCase1 = 1;
      cout << " cells is 0" << endl;
    }
  }

  if (button2)
  {
    if (simStatusCase2 == 1)
    {
      SimulatingIRSensor = 1;
      simStatusCase2 = 0;
      cout << "IR sensor is true" << endl;
      cout << SimulatingIRSensor << endl;
    }
    else if (simStatusCase2 == 0)
    {
      SimulatingIRSensor = 0;
      simStatusCase2 = 1;
      cout << "IR sensor is false" << endl;
      cout << SimulatingIRSensor << endl;
    }
  }

  if (button3)
  {
    if (simStatusCase3 == 1)
    {
      StatusRefill = 1;
      simStatusCase3 = 0;
      cout << "refill is 1" << endl;
      cout << SimulatingIRSensor << endl;
    }
    else if (simStatusCase3 == 0)
    {
      StatusRefill = 0;
      simStatusCase3 = 1;
      cout << "refill is 0" << endl;
      cout << SimulatingIRSensor << endl;
    }
  }

  /*
 if (button3)
  {
    
  }
 else
 {
   
 }
 */
}

/*
void Loader::visualisation()
{
  NetworkTableEntry myBoolean = Shuffleboard.getTab("Example Tab")
                                    .getLayout("List", "Example List")
                                    .add("My Boolean", false)
                                    .withWidget("Toggle Button")
                                    .getEntry();
}
*/