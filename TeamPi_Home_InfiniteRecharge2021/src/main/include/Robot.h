// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/Joystick.h>

#include "Motors.h"
#include "Loader.h"
#include "Sensors.h"
#include <frc/Timer.h>
#include <frc/Joystick.h>
#include <frc/DoubleSolenoid.h>
#include "Drivetrain.h"
#include "Intake.h"
#include <frc/DigitalInput.h>


class Robot : public frc::TimedRobot {
 private:
  Drivetrain Swerve;
  frc::Joystick m_stick{0};
  Intake ModIntake;
  Loader ModTurret;
  Loader test;
  DigitalInput IRSensor {2};// pin 2 for IR sensor





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
