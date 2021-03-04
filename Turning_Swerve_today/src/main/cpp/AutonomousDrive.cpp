#include "AutonomousDrive.h"

void AutonomousDrive::MotorVelocity(int VelocityDrive)
{
           this->Motor[i]->Set(ControlMode::Velocity,VelocityDrive);
}

 void AutonomousDrive::AngleRotating (int AngleWheel)
 {
    Angle1->Set(ControlMode::Position, AngleWheel);
  Angle2->Set(ControlMode::Position, AngleWheel);
  Angle3->Set(ControlMode::Position, AngleWheel);
  Angle4->Set(ControlMode::Position, AngleWheel);
  
  }
 
 void AutonomousDrive::DistanceDriveMotor (int MotorRev)
 {for (int i=0, i<4, i++)
    this->Motor[i]->Set(ControlMode::Position,MotorRev);
 }



// Function for 
 void AutonomousDrive (int DisToDrive, int AngleWheel, int VelocityDrive, int DirToDrive) 
{

  int MotorRev = DisToDrive/(diameterWheel*10*3.14159265359*RatMotToWheel);//in cm
/* need to check at which value wheel made 1 rev. 

*/
if (DirToDrive ==1) // 1=forwards drive, 0= backwards drive
{
  VelocityDrive=VelocityDrive*-1;
  }
  else
  {
    VelocityDrive=VelocityDrive; 
  }
  
//angle the modules in deg.

// angle of the rotating motor
for(int i=1; i<5; i++){
        this->Angle[i]->Set(ControlMode::Position,AngleWheel);
}

// velocity of the motor
for(int i=1; i<5; i++){
        this->Motor[i]->Set(ControlMode::Position,VelocityDrive);
}

//drive distance in cm
for(int i=1; i<5; i++){
        this->Motor[i]->Set(ControlMode::Position,MotorRev);
}



}