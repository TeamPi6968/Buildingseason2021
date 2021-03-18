#include "Loader.h"
#include <frc/GenericHID.h>
#include <iostream> 

using namespace std;
/*
Loader::Loader(Sensors* IR_LoadSensor, Motors* Loader_Motors){
  this->IR_LoadSensor = IR_LoadSensor;
  this->Loader_Motors = Loader_Motors;
}

Loader::~Loader(){

}

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
void Loader::LoaderStoreLoad (bool buttonPressed){
  if (buttonPressed){
        if  (StatusLoader == 0) {
        //change status to go out
        StatusLoader = 1;
        //spin spark motorscontrollers for Loader and storage 
         SparkMaxStorage.Set(StorageMotorSpeed);    
        SparkMaxLoader.Set(LoaderMotorSpeed);
        cout<< "Spinnn!!!" << endl; 
        }


    else if (StatusLoader == 1){
        //change status to go in
        StatusLoader = 0;
        //stop motor
        SparkMaxStorage.Set(0);    
        SparkMaxLoader.Set(0);
        cout<< "Spin stopppp" << endl;
        }
    }
}


// function will shoot a ball when a ball is present at the ir and command is given.
void Loader::Shoot (int ShootButPressed, bool SimIR)
{
  if (ShootButPressed && !SimIR)
  {
      //spin motors for couple of seconds, after seconds 'StatusRefill = 1'
    // spin motor falcon shoting motor ID: 

    // spin loaderMotor spark max ID: 18
    SparkMaxLoader.Set(LoaderMotorSpeed);
    //change status for refill loader
     StatusRefill = 0;
     cout << "refill = 0" << endl;
      }
  else
  {
    // stop motor falcon CAN ID: 

    // stop loaderMotor
    SparkMaxLoader.Set(0);
    //chagne status for refill loader
    StatusRefill = 1;
    cout << "refill = 1" << endl;
    }
}

// function will spin storage motor when there are cells in the storage and no cell is above the IR sensor. i
// it will stop when a cell is above IR sensor.
void Loader::refillTurret(int IRSensor, bool SimIR)
{
  if (AmountCellsInStorage>0 && !SimIR && StatusRefill == 1)
  {
      //spin storageMotor ID: 19;
      SparkMaxStorage.Set(StorageMotorSpeed);
      if (!IRSensor == 0) {
        // AmountCellsInStorage = AmountCellsInStorage--;
      } 
      
      cout << "refill storage" << endl;
      // cout << "amount cells is "<< AmountCellsInStorage << endl;
    }
    else
    {
      SparkMaxStorage.Set(0);
    }
    
}



void Loader::test (bool sensor)
{
  if (sensor)
  {
    AmountCellsInStorage = 3;
    cout << "cell amount is 3" << endl;
  }
  else
  {
    AmountCellsInStorage = 0;
  }
  
}




