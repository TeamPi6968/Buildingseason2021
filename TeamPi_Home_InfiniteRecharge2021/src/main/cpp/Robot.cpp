// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"


void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {



}

void Robot::TeleopInit() {
  
  frc::DoubleSolenoid anotherDoubleSolenoid{0, 1, 2};
  
  anotherDoubleSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
  
  Swerve.SetAllPID();
  Swerve.ZeroDrivetrain();
}

void Robot::TeleopPeriodic() {
  Swerve.Drive(-m_stick.GetX(), -m_stick.GetY(), m_stick.GetRawAxis(4));
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
