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
  // test for autonomous driving.
  Swerve.SetDesiredPositionRobot(0,0);
}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() {
  Swerve.Drive(m_stick.GetX(), -m_stick.GetY(), m_stick.GetRawAxis(4));


  //milans functions
  ModIntake.IntakeSolonoids(m_stick.GetRawButtonPressed(ButtonRB),ModTurret.AmountCellsInStorage); //6 = right top trigger
  //ModTurret.LoaderStoreLoad(m_stick.GetRawButtonPressed(ButtonLB));
  ModTurret.Shoot(m_stick.GetRawButtonPressed(ButtonB),ModTurret.SimulatingIRSensor);
  ModTurret.refillTurret(ModTurret.SimulatingIRSensor);
    
  
  //ModTurret.test(m_stick.GetRawButton(ButtonX));
  ModTurret.simulating(m_stick.GetRawButtonPressed(ButtonX),m_stick.GetRawButtonPressed(ButtonY),m_stick.GetRawButtonPressed(ButtonA));
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
