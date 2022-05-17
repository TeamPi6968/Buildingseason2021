// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void Robot::RobotInit() {
  Swerve.SetAllPID();
  Swerve.ZeroDrivetrain();
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {
  // DP.Bounce();
}

void Robot::TeleopInit() {

  Swerve.SetAllPID();
  Swerve.ZeroDrivetrain();

  init_States();

}

// void Robot::TeleopPeriodic() {
//   Swerve.Drive(m_stick.GetX(), -m_stick.GetY(), m_stick.GetRawAxis(4));


//   //milans functions
//   ModIntake.IntakeSolonoids(m_stick.GetRawButtonPressed(ButtonRB),ModTurret.AmountCellsInStorage); //6 = right top trigger
//   ModTurret.Shoot(m_stickTurret.GetRawButtonPressed(ButtonB),IRSensor.Get());

//   //ModTurret.test(m_stick.GetRawButton(ButtonX));
//   ModTurret.simulating(m_stick.GetRawButtonPressed(ButtonX),m_stick.GetRawButtonPressed(ButtonY),m_stickTurret.GetRawButtonPressed(ButtonA));
//   Turret.Move(m_stickTurret.GetX(),m_stickTurret.GetY(), m_stickTurret.GetRawButton(ButtonSTART),m_stickTurret.GetRawButtonPressed(L3),m_stickTurret.GetRawButtonPressed(R3));  
//   Turret.displayAngleEncoder();
//   }

void Robot::TeleopPeriodic() {
  Turret.Calibration(m_stickTurret.GetRawButtonPressed(ButtonSTART));
  if (Turret.Calibrated){
    Turret.Home(m_stickTurret.GetRawButtonPressed(R3),m_stickTurret.GetRawButtonPressed(L3));
    Turret.Move(m_stickTurret.GetX(), m_stickTurret.GetRawAxis(5));
  }
  Swerve.Drive(m_stick.GetX(), -m_stick.GetY(), m_stick.GetRawAxis(4));
  ModIntake.IntakeSolonoids(m_stick.GetRawButtonPressed(ButtonRB),ModTurret.AmountCellsInStorage); //6 = right top trigger
  ModIntake.IntakeMotors(m_stick.GetRawButtonPressed(ButtonLB),ModTurret.AmountCellsInStorage); //6 = left top trigger

  ModTurret.simulating(m_stickTurret.GetRawButtonPressed(ButtonX),m_stickTurret.GetRawButtonPressed(ButtonY),m_stickTurret.GetRawButtonPressed(ButtonA));
  ModTurret.Shoot(m_stickTurret.GetRawButtonPressed(ButtonB),m_stickTurret.GetRawButtonPressed(ButtonY));
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {

}



#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif