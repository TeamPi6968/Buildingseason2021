// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <ctre/Phoenix.h>


void Robot::RobotInit() {

}
void Robot::RobotPeriodic() {

}

void Robot::AutonomousInit() {
  this->Swerve = new RTPI_Swerve(DriveCoeficient,RotationCoeficient);
  this->Swerve->SetRotatePIDValues(SwervekP,SwervekI,SwervekD);
  drivePath = DrivePath::first;
  
}
void Robot::AutonomousPeriodic() {
  switch (drivePath)
  {
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
