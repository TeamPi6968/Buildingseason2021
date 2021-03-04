// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"


void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  time = new Timer();
  time->Start();
  lastTime = time->Get();
  intake = new Intake_System(LoaderMotor1,StorageMotor1);
}

void Robot::AutonomousPeriodic() {

  if (time->Get() - lastTime < intakeDelay) //Time to keep the motors running
  {
    intake->loader->runLoader();
    intake->storage->runStorage();
  }
  
}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
