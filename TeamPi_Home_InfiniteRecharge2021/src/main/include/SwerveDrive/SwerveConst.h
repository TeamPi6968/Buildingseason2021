/** Made for Robotics TeamPi 2021 Build Season
  * Author: Martijn van de Sande
  * Year: 2021
  * Date: 06-03-2021 // created
  * 
  * Remarks: File with all the const for the swerve drive.
**/

#pragma once

// Declare PID values
const double kP_Drive = 4;
const double kI_Drive = 0;
const double kD_Drive = 0.1;

const double kP_Turning = 4;
const double kI_Turning = 0.0015;
// test
// const double kP_Turning = 6;
// const double kI_Turning = 0.01;
const double kD_Turning = 0.1;

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
// const double Drive_ratio = 0.040178571428;
const double Drive_ratio = 0.0915032679738562;
const double Wheel_radius = 0.0516; // meter

// Max speed
const double MaxSpeed = 3;
const double MaxRad = 3;

// Math
const double pi = 2 * acos(0.0);

