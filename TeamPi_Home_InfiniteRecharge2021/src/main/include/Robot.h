// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>

//#include <frc/DigitalInput.h>
#include "Outtake.h"
#include "Intake_Storage_Loader/Loader.h"
#include "SwerveDrive/Drivetrain.h"
#include "Intake_Storage_Loader/Intake.h"

<<<<<<< Updated upstream
#include "SwerveDrive/DrivePattern.h"
#include "Intake_Storage_Loader/C04_PI_Pixy.h"
=======
<<<<<<< HEAD
#include <Pixy2/Pixy2CCC.h>
//#include <PixyProgram.h>
=======
#include "SwerveDrive/DrivePattern.h"
#include "Intake_Storage_Loader/C04_PI_Pixy.h"
>>>>>>> c6ef59513552808defe2e4b7afec50742d444691
>>>>>>> Stashed changes



class Robot : public frc::TimedRobot {
 private:
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
=======
>>>>>>> Stashed changes
//  Pixy2Program* ball_detect;

//  Get_Pixy2 *pixy;

<<<<<<< Updated upstream
=======
>>>>>>> c6ef59513552808defe2e4b7afec50742d444691
>>>>>>> Stashed changes
  Drivetrain Swerve;
  frc::Joystick m_stick{0};
  frc::Joystick m_stickTurret{1};
  Intake ModIntake;
  Loader ModTurret;
  Outtake Turret;
  Loader test;
  

int ButtonA = 1;
int ButtonB = 2;
int ButtonX = 3;
int ButtonY = 4;
int ButtonLB = 5;
int ButtonRB = 6;
int ButtonBACK = 7;
int ButtonSTART = 8;
int L3 = 9;
int R3 = 10;


 public:
 DigitalInput IRSensor {2};// pin 2 for IR sensor

  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;


};
