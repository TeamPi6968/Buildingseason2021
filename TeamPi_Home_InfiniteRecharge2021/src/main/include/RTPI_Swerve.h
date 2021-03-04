#pragma once

#include <rev/CANSparkMax.h>
#include <ctre/phoenix.h>

using namespace rev;  //To avoid writing rev everytime I call something from the rev libraries

class RTPI_Swerve
{
    private:

        WPI_TalonFX* LFRotate;
        WPI_TalonFX* RFRotate;
        WPI_TalonFX* LBRotate;
        WPI_TalonFX* RBRotate;

        WPI_TalonFX* LFDrive; 
        WPI_TalonFX* RFDrive; 
        WPI_TalonFX* LBDrive; 
        WPI_TalonFX* RBDrive; 

        const int LFMotor = 1;
        const int RFMotor = 3;
        const int LBMotor = 5;
        const int RBMotor = 7;

        const int LFMotorDrive = 2;
        const int RFMotorDrive = 4;
        const int LBMotorDrive = 6;
        const int RBMotorDrive = 8;        

        WPI_TalonFX* RotateMotors[4] = {LFRotate,RFRotate,LBRotate,RBRotate};
        WPI_TalonFX* DriveMotors[4]  = {LFDrive,RFDrive,LBDrive,RBDrive};

        double RotateGearRatio = 1000;
        double DriveGearRatio = 100;
        double degrees =1;

    public:

        RTPI_Swerve(double driveCoeff, double rotateCoeff);
        //to set the PID of the motors
        void SetRotatePIDValues(double kP, double kI, double kD, double kMinOutput, double kMaxOutput);
        //void SetDrivePIDValues(double kP, double kI, double kD, double kMinOutput, double kMaxOutput);
        
        //move all the rotation motors to a specific angle
        void SetAllDirection(double degrees);

        //set all the driving motors to a specific speed
        void SetAllDriveSpeed(double speed);

        //set all the driving motors to a specific distance
        void SetAllDriveDistance(double distance);

};