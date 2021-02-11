#include "Loader.h"

Loader::Loader(Sensors* IR_LoadSensor, Motors* Loader_Motors){
  this->IR_LoadSensor = IR_LoadSensor;
  this->Loader_Motors = Loader_Motors;
}

Loader::~Loader(){

}

bool Loader::isCellDetected(){
  return this->IR_LoadSensor->readSensor();
}

void Loader::runLoadMotor(){
  if(isCellDetected()){
    Loader_Motors->GetSparkMax()->Set(LoaderMotorSpeed);
  }
  else{
    Loader_Motors->GetSparkMax()->StopMotor();
  }
}

void Loader::runLoadMotor(double setSpeed){
  Loader_Motors->GetSparkMax()->Set(setSpeed);
}
