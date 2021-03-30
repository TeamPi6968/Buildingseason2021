/** Made for Robotics TeamPi 2021 Build Season
  * Author: Martijn van de Sande
  * Year: 2021
  * Date: 06-03-2021 // created
  * 
  * Remarks: Hearder file for SwerveDrive to configre the motors of the modules and set its desired state.
**/

#pragma once

#include <ctre/phoenix.h>
#include "SwerveConst.h"
#include "math.h"
#include <iostream>

using namespace std;

class SwerveModule{
 public:
    // init all the swerve motors of the modules
    SwerveModule(int DriveMotorID, int TurningMotorID);
    void SetPID();
    void SetPID(double kp,double ki,double kd);
    // Zero the wheel position of the swerve.
    void SwerveZero();
    // Set the swerve wheel direction back to 0.
    void SwerveHome();
    // Set swerve to desired pos/ speed.
    void SetDesiredState(double speed, double Direction);
    // Set the module to a determent position on the field 
    void SetDesiredPosition(double Distance, double Angle);

    double GetModulePosition();

    double GetModulePositionDrive();
    double GetModulePositionAngle();



   //function for hard coded autonomous part to drive.
   // void AutonomousDrive (int DistanceToDrive, int AngleOfWheels)

 private:
    WPI_TalonFX DriveMotor;
    WPI_TalonFX TurningMotor; 

    // coef for the motors
    double DriveCoef = Drive_ratio* 360 * Wheel_radius / EncoderResolution;
    double TurnCoef = Turning_ratio* 360 / EncoderResolution;
    
};