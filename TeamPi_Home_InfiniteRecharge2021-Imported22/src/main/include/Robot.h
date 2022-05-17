// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
//#include <frc/DigitalInput.h>
#include "Outtake.h"
#include "Intake_Storage_Loader/Loader.h"
#include "Intake_Storage_Loader/Intake.h"
#include "SwerveDrive/DrivePattern.h"
#include "SwerveDrive/Drivetrain.h"



//#include <Pixy2/Pixy2CCC.h>
//#include <Pixy2/Pixy2Program.h>
// #include <Pixy2/Pixy2CCC.h>
//#include <PixyProgram.h>

// #include "Intake_Storage_Loader/C04_PI_Pixy.h"


class Robot : public frc::TimedRobot {
 private:
//  Pixy2Program ball_detect;
//  Pixy2Program* ball_detect;
//  Get_Pixy2 *pixy;

  Drivetrain Swerve;
  frc::Joystick m_stick{0};
  frc::Joystick m_stickTurret{1};
  Intake ModIntake;
  Loader ModTurret;
  Outtake Turret;
  // Loader test;
  // int bigState;
  // int shootState;
  // int driveToLoad;
  // int driveToShoot;

  int iterateStates;

  enum bigStates
  {
    shoot = 0,
    driveToLoad =1,
    load = 2,
    driveToShoot = 3,
    endChallenge = -1
  };

  enum shootState
  {
    slvl_0 = 0,
    slvl_1 = 1,
    slvl_2 = 2,
    slvl_3 = 3
  };

  enum goToLoad
  {
    dlvl_0 = 0,
    dlvl_1 = 1,
    dlvl_2 = 2,
    dlvl_3 = 3
  };

  enum goToShoot
  {
    dslvl_0 = 0,
    dslvl_1 = 1,
    dslvl_2 = 2,
    dslvl_3 = 3
  };

  bigStates bigState;
  goToLoad D2L;
  goToShoot D2S; 
  shootState shootState;

void init_States(){
  bigState = shoot;
  D2S = dslvl_0;
  D2L = dlvl_0;
  shootState = slvl_0;
  iterateStates = 0;
}

//Moves to the next level state for all cases.
void nextState(){
  switch (iterateStates)
  {
  default:
    iterateStates = 0;
  case 0:
    D2S = dslvl_0;
    D2L = dlvl_0;
    shootState = slvl_0;
    iterateStates++;
    break;
  case 1:
    D2S = dslvl_1;
    D2L = dlvl_1;
    shootState = slvl_1;
    iterateStates++;
    break;  
  case 2:
    D2S = dslvl_2;
    D2L = dlvl_2;
    shootState = slvl_2;
    iterateStates++;
    break;
  case 3:
    D2S = dslvl_3;
    D2L = dlvl_3;
    shootState = slvl_3;
    iterateStates++;
    break;
  }
}

void startIACstateFlow(){
    switch (bigState)
  {
  case shoot:
    switch (shootState) // Write nextState which should be a corressponding driveToLoad(DL) state
    {
    case slvl_0:
      
      break;
    case slvl_1:
      
      break;
    case slvl_2:
      
      break;
    case slvl_3:
      
      break;
    default:
      break;
    }
    bigState = driveToLoad;
    break;
  case driveToLoad:
    switch (D2L)
    {
    case dlvl_0:
      
      break;
    case dlvl_1:
      
      break;
    case dlvl_2:
      
      break;
    case dlvl_3:
      
      break;
    default:
      break;
    }
    bigState = load;
    break;
  case load:  //Tell what driveToShoot level should be next

    nextState();
    bigState = driveToShoot;
    break;
  case driveToShoot:
    switch (D2S)
    {
    case dslvl_0:
      
      break;
    case dslvl_1:
      
      break;
    case dslvl_2:
      
      break;
    case dslvl_3:
      
      break;
    default:
      break;
    }
    bigState = shoot;
    break;
  default:
    break;
  }

}

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
