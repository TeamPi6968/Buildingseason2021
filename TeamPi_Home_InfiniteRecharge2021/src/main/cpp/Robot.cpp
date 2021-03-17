// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"





void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {
  // while (frc::Joystick::GetTopPressed == true)
  // {



  // }
}

void Robot::TeleopInit() {
  Swerve.SetAllPID();
  Swerve.ZeroDrivetrain();
}

void Robot::TeleopPeriodic() {
  Swerve.Drive(m_stick.GetX(), m_stick.GetY(), m_stick.GetRawAxis(4));
  
  ModIntake.IntakeSolonoids(m_stick.GetRawButtonPressed(6)); //6 = right top trigger
  //  ModTurret.LoaderStoreLoad(m_stick.GetRawButtonPressed(5));
  ModTurret.Shoot(m_stick.GetRawButton(2),m_stick.GetRawButton(4));
  ModTurret.refillTurret(IRSensor.Get(),m_stick.GetRawButton(4));
  ModTurret.test(m_stick.GetRawButton(3));
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
