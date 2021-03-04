// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <frc/Joystick.h>


void Robot::RobotInit() {

}
void Robot::RobotPeriodic() {

}

void Robot::AutonomousInit() {
  time = new Timer();
  StorageMotor1 = new Motors(Motors::motorCtrlTypes::SPARKMAX, StoragecanID1,brushed,accelerate,inverted,noEncoder,noPID);
  LoaderMotor1  = new Motors(Motors::motorCtrlTypes::SPARKMAX, LoadercanID1,brushed,accelerate,inverted,noEncoder,noPID);

  turret = new Turret();


  time->Start();
  lastTime = time->Get();
  intake = new Intake_System(LoaderMotor1,StorageMotor1);
  this->Swerve = new RTPI_Swerve(DriveCoeficient,RotationCoeficient);
  this->Swerve->SetRotatePIDValues(SwervekP,SwervekI,SwervekD);
  drivePath = DrivePath::first;
  
}
void Robot::AutonomousPeriodic() {
  switch (drivePath){
  case DrivePath::first:
    this->Swerve->SetAllDriveDistance(firstStep);
    drivePath = DrivePath::second;
    break;
  case DrivePath::second:
    this->Swerve->SetAllDirection(turn90);
    this->Swerve->SetAllDriveDistance(firstStep/2);
    drivePath = DrivePath::third;
    break;
  case DrivePath::third:
      if (time->Get() - lastTime < intakeDelay){ //Time to keep the motors running
      intake->loader->runLoader();
      intake->storage->runStorage();
      }
      
      turret->Shoot(true, turretSpeed);
    drivePath = DrivePath::done;
    break;
  default:
    break;
  }
}



void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {


}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
