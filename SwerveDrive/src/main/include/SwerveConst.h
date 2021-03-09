/** Made for Robotics TeamPi 2021 Build Season
  * Author: Martijn van de Sande
  * Year: 2021
  * Date: 06-03-2021 // created
  * 
  * Remarks: File with all the const for the swerve drive.
**/

#pragma once

// Declare PID values
const float kP_Drive = 0.5;
const float kI_Drive = 0;
const float kD_Drive = 0.1;

const float kP_Turning = 0.5;
const float kI_Turning = 0;
const float kD_Turning = 0.1;

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
const float Turning_ratio = 0.047619047619047619;
const float Drive_ratio = 0.040178571428;
const float Wheel_radius = 0.0508; // meter

// Max speed
const float MaxSpeed = 1;
const float MaxRad = 1;

// Math
const float pi = 2 * acos(0.0);

