// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include "RTPI_Swerve.h"
#include "RobotConstants.h"
#include <frc/Timer.h>
#include "Intake_System.h"
#include <ctre/Phoenix.h>
#include "Turret.h"


class Robot : public frc::TimedRobot {
  private:
  RTPI_Swerve * Swerve;
  frc::Timer* time;
  double lastTime;
  double intakeDelay = 3;
  Intake_System* intake;

  enum DrivePath
  {
    first = 0,
    second = 1,
    third = 2,
    done = 3
  } drivePath;

  //Motors
  //Storage
  Motors* StorageMotor1;
  //Loader
  Motors* LoaderMotor1;

  //Turret
  Turret * turret;


 public:
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
