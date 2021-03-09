/** Made for Robotics TeamPi 2021 Build Season
  * Author: Martijn van de Sande
  * Year: 2021
  * Date: 06-03-2021 // created
  * 
  * Edit: 07-03-2021 // added some basic math to test driving the swerve bot.
  * 
  * Remarks: header file for Drivetrain to create the modules and functions to drive with the swerve bot.
**/

#pragma once

#include "SwerveModule.h"
#include <ctre/phoenix.h>

class Drivetrain{
 public:
  // Drivetrain();
  void SetAllPID();
  // Zero all the wheel position of the swerve.
  void ZeroDrivetrain();
  // Set all the swerve wheel direction back to 0.
  void DrivetrainHome();
  // some math for the swerve drive.
  // double MathSpeed(double xVal, double yVal);
  // double MathDirection(double xVal, double yVal);
  auto MathSwerve(float xValue, float yValue, float rot);
  // Drive with the swerve drive, uses the x and y values of the stick.
  void Drive(float xValue, float yValue, float rotation);


 private:
  // create the swervedrive modules.
  SwerveModule module_frontLeft{LFMotorDrive, LFMotor};
  SwerveModule module_frontRight{RFMotorDrive, RFMotor};
  SwerveModule module_backLeft{LBMotorDrive, LBMotor};
  SwerveModule module_backRight{RBMotorDrive, RBMotor};

  // var
  float prevDirection = 0;
  float Speedfl, Speedfr, Speedbl, Speedbr;
  float Directionfl, Directionfr, Directionbl, Directionbr;
  float RotVecInRad = 45 * pi / 180;

  // position of the module x, y
  float PosModuleFL[2] = {-340, 273.5};
  float PosModuleFR[2] = {340, 273.5};
  float PosModuleBL[2] = {-340, -273.5};
  float PosModuleBR[2] = {340, -273.5};

  float DistanceModFL = sqrt(pow(PosModuleFL[0],2)+pow(PosModuleFL[1],2));
  float DistanceModFR = sqrt(pow(PosModuleFR[0],2)+pow(PosModuleFR[1],2));
  float DistanceModBL = sqrt(pow(PosModuleBL[0],2)+pow(PosModuleBL[1],2));
  float DistanceModBR = sqrt(pow(PosModuleBR[0],2)+pow(PosModuleBR[1],2));

  float DistanceMod[4] = {DistanceModFL, DistanceModFR, DistanceModBL, DistanceModBR};
  
};