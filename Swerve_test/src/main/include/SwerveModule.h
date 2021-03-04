// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Encoder.h>
#include <frc/PWMVictorSPX.h>
#include <ctre/Phoenix.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <units/angular_velocity.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <wpi/math>

class SwerveModule {
 public:
  SwerveModule(int driveMotorChannel, int turningMotorChannel);
  frc::SwerveModuleState GetState() ;
  void SetDesiredState(frc::SwerveModuleState& state);
//   auto SwerveModule::GetStateInput();

 private:
  static constexpr double kWheelRadius = 0.0508;
  static constexpr int kEncoderResolution = 2048;

  static constexpr auto kModuleMaxAngularVelocity =
      wpi::math::pi * 1_rad_per_s;  // radians per second
  static constexpr auto kModuleMaxAngularAcceleration =
      wpi::math::pi * 2_rad_per_s / 1_s;  // radians per second^2


  WPI_TalonFX m_driveMotor;
  WPI_TalonFX m_turningMotor; 

  WPI_TalonFX m_driveEncoder;
  WPI_TalonFX m_turningEncoder; 


//   frc::PWMVictorSPX m_driveMotor;
//   frc::PWMVictorSPX m_turningMotor;

//     WPI_TalonFX 
// m_driveEncoder = m_driveMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
//   frc::Encoder m_turningEncoder{2, 3};

  frc2::PIDController m_drivePIDController{1.0, 0, 0};
  frc::ProfiledPIDController<units::radians> m_turningPIDController{
      1.0,
      0.0,
      0.0,
      {kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}};

  frc::SimpleMotorFeedforward<units::meters> m_driveFeedforward{1_V,
                                                                3_V / 1_mps};
  frc::SimpleMotorFeedforward<units::radians> m_turnFeedforward{
      1_V, 0.5_V / 1_rad_per_s};
};
