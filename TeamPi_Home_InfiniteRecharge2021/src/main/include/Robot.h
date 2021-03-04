// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include "Motors.h"
#include "Loader.h"
#include "Sensors.h"
#include "RTPI_Swerve.h"
#include "RobotConstants.h"


class Robot : public frc::TimedRobot {
  private:
  RTPI_Swerve * Swerve;

  enum DrivePath
  {
    first = 0,
    second = 1,
    third = 2,
    done = 3
  } drivePath;


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
