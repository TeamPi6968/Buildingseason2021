// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "SwerveModule.h"
#include <ctre/Phoenix.h>
#include <frc/geometry/Rotation2d.h>
#include <wpi/math>
#include "tuple"

SwerveModule::SwerveModule(const int driveMotorChannel,
                           const int turningMotorChannel)
    : m_driveMotor(driveMotorChannel), m_turningMotor(turningMotorChannel),
      m_driveEncoder(driveMotorChannel), m_turningEncoder(turningMotorChannel){
  // Set the distance per pulse for the drive encoder. We can simply use the
  // distance traveled for one rotation of the wheel divided by the encoder
  // resolution.
  m_driveEncoder.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
  m_turningEncoder.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
  // .ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 1);
  // m_driveMotor.GetSelectedSensorPosition();

  // m_driveMotor.GetIntegratedSensorAbsolutePosition();
  //  m_driveMotor.SetDistancePerPulse(2 * wpi::math::pi * kWheelRadius /
  //                                    kEncoderResolution);

  // Set the distance (in this case, angle) per pulse for the turning encoder.
  // This is the the angle through an entire rotation (2 * wpi::math::pi)
  // divided by the encoder resolution.
  // auto m_turningEncoder = m_turningMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
  // m_turningEncoder.SetDistancePerPulse(2 * wpi::math::pi / kEncoderResolution);

  // Limit the PID Controller's input range between -pi and pi and set the input
  // to be continuous.
  m_turningPIDController.EnableContinuousInput(-units::radian_t(wpi::math::pi),
                                               units::radian_t(wpi::math::pi));
}
/*units::meters_per_second_t*/
frc::SwerveModuleState SwerveModule::GetState() {
    // auto arr = GetStateInput();
    // double DriveEncoder = arr[0];
    // double RotateEncoder = arr [1];
  return {units::meters_per_second_t{m_driveEncoder.GetSelectedSensorVelocity()},
          frc::Rotation2d(units::radian_t( m_turningEncoder.GetSelectedSensorPosition()))};
}

// auto SwerveModule::GetStateInput(){
//     double DriveEncoder = m_driveEncoder.GetSelectedSensorVelocity();
//     double RotateEncoder = m_turningEncoder.GetSelectedSensorPosition();
//     double encoderVal[] = {DriveEncoder, RotateEncoder};
//     return encoderVal;
// }

void SwerveModule::SetDesiredState(frc::SwerveModuleState& referenceState) {
  // Optimize the reference state to avoid spinning further than 90 degrees
  const auto state = frc::SwerveModuleState::Optimize(
      referenceState, units::radian_t(m_turningEncoder.GetSelectedSensorPosition()));

  // Calculate the drive output from the drive PID controller.
  const auto driveOutput = m_drivePIDController.Calculate(
      m_driveEncoder.GetSelectedSensorVelocity(), state.speed.to<double>());

  const auto driveFeedforward = m_driveFeedforward.Calculate(state.speed);

  // Calculate the turning motor output from the turning PID controller.
  const auto turnOutput = m_turningPIDController.Calculate(
      units::radian_t(m_turningEncoder.GetSelectedSensorPosition()), state.angle.Radians());

  const auto turnFeedforward = m_turnFeedforward.Calculate(
      m_turningPIDController.GetSetpoint().velocity);

  // Set the motor outputs.
  m_driveMotor.SetVoltage(units::volt_t{driveOutput} + driveFeedforward);
  m_turningMotor.SetVoltage(units::volt_t{turnOutput} + turnFeedforward);
}
