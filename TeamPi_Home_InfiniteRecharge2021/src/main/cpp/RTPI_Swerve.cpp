#include "RTPI_Swerve.h"

RTPI_Swerve::RTPI_Swerve(double driveCoeff, double rotateCoeff){
    LFRotate = new WPI_TalonFX(LFMotor);
    RFRotate = new WPI_TalonFX(RFMotor);
    LBRotate = new WPI_TalonFX(LBMotor);
    RBRotate = new WPI_TalonFX(RBMotor);
    
    LFDrive = new WPI_TalonFX(LFMotorDrive);
    RFDrive = new WPI_TalonFX(RFMotorDrive);
    LBDrive = new WPI_TalonFX(LBMotorDrive);
    RBDrive = new WPI_TalonFX(RBMotorDrive);

    for (int i = 0; i < 4; i++)
    {
        this->RotateMotors[i]->ConfigSelectedFeedbackCoefficient(rotateCoeff,0,50);
        this->DriveMotors[i]->ConfigSelectedFeedbackCoefficient(driveCoeff,0,50);
    }

    for (int i = 0; i < 4; i++)
    {
        this->RotateMotors[i]->SetSelectedSensorPosition(0,0,50);
        this->DriveMotors[i]->SetSelectedSensorPosition(0,0,50);
    }
    
}

void RTPI_Swerve::SetRotatePIDValues(double kP, double kI, double kD) {
  for(int i = 0; i < 4; i++){
    this->RotateMotors[i]->Config_kP(0,kP,50);
    this->RotateMotors[i]->Config_kI(0,kI,50);
    this->RotateMotors[i]->Config_kD(0,kD,50);
  }
}

void RTPI_Swerve::SetAllDirection(double degrees){
    double pos = degrees;          
    for(int i = 0; i< 4; i++){
        this->RotateMotors[i]->Set(ControlMode::Position,pos);
    }
}

void RTPI_Swerve::SetAllDriveSpeed(double speed){
    for(int i = 0; i< 4; i++){
        this->DriveMotors[i]->Set(ControlMode::Velocity,speed);
    }
}

void RTPI_Swerve::SetAllDriveDistance(double distance){
    double pos = distance/this->DriveGearRatio;
    for(int i = 0; i < 4; i++){
        this->DriveMotors[i]->Set(ControlMode::Position,pos);
    }
}