#pragma once

#include <ctre/Phoenix.h>

//class for function to make it easy to drive the Autonav challenge, idea is, copy this function, 
//you only have to change the parameters for forward, distance, angel of swerve modules and so on.

class AutonomousDrive
{
private:
    WPI_TalonFX *Motor1 = new WPI_TalonFX(1);
  WPI_TalonFX *Motor2 = new WPI_TalonFX(3);
  WPI_TalonFX *Motor3 = new WPI_TalonFX(5);
  WPI_TalonFX *Motor4 = new WPI_TalonFX(7);

  WPI_TalonFX *Angle1 = new WPI_TalonFX(2);
  WPI_TalonFX *Angle2 = new WPI_TalonFX(4);
  WPI_TalonFX *Angle3 = new WPI_TalonFX(6);
  WPI_TalonFX *Angle4 = new WPI_TalonFX(8);
  int DirToDrive;
 
  int MotorRev;


// 
public:
    AutonomousDrive(WPI_TalonFX *Angle1, WPI_TalonFX *Angle2, WPI_TalonFX *Angle3,WPI_TalonFX *Angle4 );
    ~AutonomousDrive( );


     void MotorVelocity(int VelocityDrive);
void AngleRotating (int AngleWheel);
void DistanceDriveMotor (int MotorRev);
void AutonomousDrive (int DisToDrive, int AngleWheel, int VelocityDrive, int DirToDrive);
    
  // variables for the function
    int AutonomousDrive.RatMotToWheel = 6380;//ratio of wheel to motor
  int AutonomousDrive.diameterWheel = 101.6; // in mm
};



 
