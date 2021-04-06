// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {


}
void Robot::AutonomousPeriodic() {
<<<<<<< HEAD
=======
  DP.Bounce();
<<<<<<< Updated upstream
=======
>>>>>>> c6ef59513552808defe2e4b7afec50742d444691
>>>>>>> Stashed changes

}

void Robot::TeleopInit() {
<<<<<<< Updated upstream
//  pixy = new Get_Pixy2(frc::I2C::kOnboard, 8);
=======
<<<<<<< HEAD
  // frc::DoubleSolenoid anotherDoubleSolenoid{0, 1, 2};

  // anotherDoubleSolenoid.Set(frc::DoubleSolenoid::Value::kForward);

=======
//  pixy = new Get_Pixy2(frc::I2C::kOnboard, 8);
>>>>>>> c6ef59513552808defe2e4b7afec50742d444691
>>>>>>> Stashed changes
  Swerve.SetAllPID();
  Swerve.ZeroDrivetrain();
}

<<<<<<< HEAD

void Robot::TeleopPeriodic() {
  Turret.Calibration(m_stickTurret.GetRawButtonPressed(ButtonSTART));
  if (Turret.Calibrated)
  {
    Turret.Home(m_stickTurret.GetRawButton(L3), m_stickTurret.GetRawButton(R3));
    Turret.Move(m_stickTurret.GetX(), m_stickTurret.GetRawAxis(5));

//   //   ModTurret.Shoot(m_stickTurret.GetRawButtonPressed(ButtonB),IRSensor.Get());
//   //   ModTurret.simulating(m_stickTurret.GetRawButtonPressed(ButtonX),m_stickTurret.GetRawButtonPressed(ButtonY),m_stickTurret.GetRawButtonPressed(ButtonA));
    
//     // Swerve.Drive(m_stick.GetX(), -m_stick.GetY(), m_stick.GetRawAxis(4));

//     // ModIntake.IntakeSolonoids(m_stick.GetRawButtonPressed(ButtonRB),ModTurret.AmountCellsInStorage); //6 = right top trigger
//     // ModTurret.LoaderStoreLoad(m_stick.GetRawButtonPressed(ButtonLB));
//     // ModTurret.refillTurret(ModTurret.SimulatingIRSensor);

//     // ModTurret.test(m_stick.GetRawButton(ButtonX));
  }
}
=======
void Robot::TeleopPeriodic() {
  Swerve.Drive(m_stick.GetX(), -m_stick.GetY(), m_stick.GetRawAxis(4));

//  cout<<"Pixy Value: "<< pixy->GetBlocks();


  //milans functions
  ModIntake.IntakeSolonoids(m_stick.GetRawButtonPressed(ButtonRB),ModTurret.AmountCellsInStorage); //6 = right top trigger
  
  ModTurret.Shoot(m_stick.GetRawButtonPressed(ButtonB),IRSensor.Get());

  //ModTurret.test(m_stick.GetRawButton(ButtonX));
  ModTurret.simulating(m_stick.GetRawButtonPressed(ButtonX),m_stick.GetRawButtonPressed(ButtonY),m_stick.GetRawButtonPressed(ButtonA));
  }

<<<<<<< Updated upstream
=======
>>>>>>> c6ef59513552808defe2e4b7afec50742d444691
>>>>>>> Stashed changes

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

<<<<<<< Updated upstream
=======
<<<<<<< HEAD
void Robot::TestInit() {}
void Robot::TestPeriodic() {}
=======
>>>>>>> Stashed changes
void Robot::TestInit() {
  DP.ClearFile();
}
void Robot::TestPeriodic() {
  DP.RecBounce();
}
>>>>>>> c6ef59513552808defe2e4b7afec50742d444691


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
