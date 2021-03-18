/** Made for Robotics TeamPi 2021 Build Season
  * Author: Martijn van de Sande
  * Year: 2021
  * Date: 06-03-2021 // created
  * 
  * Remarks: File with all the const for the swerve drive.
**/

#pragma once

// Declare PID values
const double kP_Drive = 1;
const double kI_Drive = 0;
const double kD_Drive = 0.1;

const double kP_Turning = 1.1;
const double kI_Turning = 0.002;
const double kD_Turning = 0.9;

// Declare Motor ID's
const int LFMotor = 2;
const int RFMotor = 4;
const int LBMotor = 6;
const int RBMotor = 8;

const int LFMotorDrive = 1;
const int RFMotorDrive = 3;
const int LBMotorDrive = 5;
const int RBMotorDrive = 7;

// Declare encoder var
const int EncoderResolution = 2048;
const int TimeOut = 60;

// Declare gear ratio
const double Turning_ratio = 0.047619047619047619;
const double Drive_ratio = 0.040178571428;
const double Wheel_radius = 0.0508; // meter

// Max speed
const double MaxSpeed = 12;
const double MaxRad = 5;

// Math
const double pi = 2 * acos(0.0);

