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
  double MathSpeed(double xVal, double yVal);
  // double MathDirection(double xVal, double yVal);
  void MathSwerve(double xValue, double yValue, double rot);
  void AngleCorrection();
  // Drive with the swerve drive, uses the x and y values of the stick.
  void Drive(double xValue, double yValue, double rotation);


 private:
  // create the swervedrive modules.
  SwerveModule module_frontLeft{LFMotorDrive, LFMotor};
  SwerveModule module_frontRight{RFMotorDrive, RFMotor};
  SwerveModule module_backLeft{LBMotorDrive, LBMotor};
  SwerveModule module_backRight{RBMotorDrive, RBMotor};

  // var
  double prevDirection = 0;
  double Speedfl, Speedfr, Speedbl, Speedbr;
  double Directionfl, Directionfr, Directionbl, Directionbr;
  double RotVecInRad = 45 * pi / 180;

  // position of the module x, y
  double PosModuleFL[2] = {-0.340, 0.2735};
  double PosModuleFR[2] = {0.340, 0.2735};
  double PosModuleBL[2] = {-0.340, -0.2735};
  double PosModuleBR[2] = {0.340, -0.2735};

  double DistanceModFL = sqrt(pow(PosModuleFL[0],2)+pow(PosModuleFL[1],2));
  double DistanceModFR = sqrt(pow(PosModuleFR[0],2)+pow(PosModuleFR[1],2));
  double DistanceModBL = sqrt(pow(PosModuleBL[0],2)+pow(PosModuleBL[1],2));
  double DistanceModBR = sqrt(pow(PosModuleBR[0],2)+pow(PosModuleBR[1],2));

  double DistanceMod[4] = {DistanceModFL, DistanceModFR, DistanceModBL, DistanceModBR};

  double PrevDirectionfl = 0;
  double PrevDirectionfr = 0;
  double PrevDirectionbl = 0;
  double PrevDirectionbr = 0;

  double AngleCorrectionFl = 0;
  double AngleCorrectionFr = 0;
  double AngleCorrectionBl = 0;
  double AngleCorrectionBr = 0;
  
  
};