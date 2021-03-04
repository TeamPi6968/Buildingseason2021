// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <ctre/Phoenix.h>


void Robot::RobotInit() {
 this->Swerve = new RTPI_Swerve();

Swerve->SetCoefEncoderUnits(0,turningEncoderCoef);
Swerve->SetCoefEncoderUnits(1,drivingEncoderCoef);
Swerve->SetRotatePIDValues(1.0,0.0,0.0,0.0,0.5);
//Zero the position of all Rotating Motors
swerve->InitializeEncoders(0);
//Zero the position of all Driving Motors
Swerve->InitializeEncoders(1);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {

}
void Robot::AutonomousPeriodic() {




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
