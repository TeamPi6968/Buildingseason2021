// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include "Intake_System.h"


class Robot : public frc::TimedRobot {
 private:
  frc::Timer* time;
  double lastTime;
  double intakeDelay = 3;
  Intake_System* intake;


  //Motors
  //Storage
  Motors* StorageMotor1 = new Motors(Motors::motorCtrlTypes::SPARKMAX, StoragecanID1,brushed,accelerate,inverted,noEncoder,noPID);

  //Loader
  Motors* LoaderMotor1 = new Motors(Motors::motorCtrlTypes::SPARKMAX, LoadercanID1,brushed,accelerate,inverted,noEncoder,noPID);


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
