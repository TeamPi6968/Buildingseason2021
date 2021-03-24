/** Made for Robotics TeamPi 2021 Build Season
  * Author: Martijn van de Sande
  * Year: 2021
  * Date: 06-03-2021 // created
  *
  * Remarks: Configre the motors of the modules and set its desired state.
**/

#include "SwerveDrive/SwerveModule.h"

SwerveModule::SwerveModule(int DriveMotorID, int TurningMotorID)
                            : DriveMotor(DriveMotorID), TurningMotor(TurningMotorID){

    // init the encoders of the motors.
    DriveMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, TimeOut);
    TurningMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, TimeOut);

    // set the desired coef to the motor.
    DriveMotor.ConfigSelectedFeedbackCoefficient(DriveCoef, 0, TimeOut);
    TurningMotor.ConfigSelectedFeedbackCoefficient(TurnCoef, 0, TimeOut);
}

void SwerveModule::SetPID(){
    // set PID values for the drive motor.
    DriveMotor.Config_kP(0, kP_Drive, TimeOut);
    DriveMotor.Config_kI(0, kI_Drive, TimeOut);
    DriveMotor.Config_kD(0, kD_Drive, TimeOut);

    // set PID values for the turning motor.
    TurningMotor.Config_kP(0, kP_Turning, TimeOut);
    TurningMotor.Config_kI(0, kI_Turning, TimeOut);
    TurningMotor.Config_kD(0, kD_Turning, TimeOut);
}

void SwerveModule::SetPID(double kp,double ki,double kd){
    // set PID values for the drive motor.
    DriveMotor.Config_kP(0, kP_Drive, TimeOut);
    DriveMotor.Config_kI(0, kI_Drive, TimeOut);
    DriveMotor.Config_kD(0, kD_Drive, TimeOut);

    // set PID values for the turning motor.
    TurningMotor.Config_kP(0, kP_Turning, TimeOut);
    TurningMotor.Config_kI(0, kI_Turning, TimeOut);
    TurningMotor.Config_kD(0, kD_Turning, TimeOut);
}

// zero the encoders of the swerve module.
void SwerveModule::SwerveZero(){
    TurningMotor.SetSelectedSensorPosition(0, 0, TimeOut);
}

// set the motor back to its zero pos.
void SwerveModule::SwerveHome(){
    TurningMotor.Set(ControlMode::Position, 0);
}

// set the desired state of the motor, speed/ pos.
void SwerveModule::SetDesiredState(double SpeedMod, double DirectionMod){
    TurningMotor.Set(ControlMode::Position, 1 * DirectionMod);
    DriveMotor.Set(ControlMode::Velocity, 1 * SpeedMod);
}

// Set the module to a determent position on the field 
void SwerveModule::SetDesiredPosition(double Distance, double Angle){
    TurningMotor.Set(ControlMode::Position, Angle);
    DriveMotor.Set(ControlMode::Position, Distance);
}
