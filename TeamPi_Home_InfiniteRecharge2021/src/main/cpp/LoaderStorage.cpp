#include "LoaderStorage.h"

Loader::Loader(Motors*Loader_Motors){
  this->Loader_Motors = Loader_Motors;
  this->IR_LoadSensor = NULL;
}

Loader::Loader(Sensors* IR_LoadSensor, Motors* Loader_Motors){
  this->IR_LoadSensor = IR_LoadSensor;
  this->Loader_Motors = Loader_Motors;
}

Loader::~Loader(){

}

bool Loader::isCellDetected(){
  return this->IR_LoadSensor->readSensor();
}

//Run automatically depending on IR sensor value at defaul set speed
void Loader::runLoader(){
  if(this->IR_LoadSensor != NULL){  
    if(isCellDetected()){
      Loader_Motors->GetSparkMax()->Set(LoaderMotorSpeed);
    }
    else{
      Loader_Motors->GetSparkMax()->StopMotor();
    }
  }
  else
  {
    Loader_Motors->GetSparkMax()->Set(LoaderMotorSpeed);
  }
  
}

void Loader::runLoader(double setSpeed){
  Loader_Motors->GetSparkMax()->Set(setSpeed);
}

//------------------------------------ Storage class

Storage::Storage(Motors* Storage_Motors)
{
  this->Storage_Motors = Storage_Motors;
}

Storage::~Storage()
{
}


//Run at default set Speed
void Storage::runStorage(){
  this->Storage_Motors->GetSparkMax()->Set(StorageMotorSpeed);
}

void Storage::runStorage(double setSpeed){
  this->Storage_Motors->GetSparkMax()->Set(setSpeed);
}




