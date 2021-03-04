#include "RTPI_Swerve.h"

RTPI_Swerve::RTPI_Swerve(){
    LFRotate = new WPI_TalonFX(LFMotor);
    RFRotate = new WPI_TalonFX(RFMotor);
    LBRotate = new WPI_TalonFX(LBMotor);
    RBRotate = new WPI_TalonFX(RBMotor);
    
    LFDrive = new WPI_TalonFX(LFMotorDrive);
    RFDrive = new WPI_TalonFX(RFMotorDrive);
    LBDrive = new WPI_TalonFX(LBMotorDrive);
    RBDrive = new WPI_TalonFX(RBMotorDrive);

}

void RTPI_Swerve::SetRotatePIDValues(double kP, double kI, double kD, double kMinOutput, double kMaxOutput) {
  for(int i; i<5; i++){
    this->RotateMotors[i]->SetP(kP);
    this->RotateMotors[i]->SetI(kI);
    this->RotateMotors[i]->SetD(kD);
    this->RotateMotors[i]->SetOutputRange(kMinOutput, kMaxOutput);
  }
}

void RTPI_Swerve::SetAllDirection(double degrees){
    double pos = degrees/this->RotateGearRatio; //set gear ratio here
    for(int i; i<5; i++){
        this->RotateMotors[i]->Set(ControlMode::Position,pos);
    }
}

void RTPI_Swerve::SetAllDriveSpeed(double speed){
    for(int i; i<5; i++){
        this->DriveMotors[i]->Set(ControlMode::Velocity,speed);
    }
}

void RTPI_Swerve::SetAllDriveDistance(double distance){
    double pos = degrees/this->DriveGearRatio;
    for(int i; i<5; i++){
        this->DriveMotors[i]->Set(ControlMode::Position,pos);
    }
}