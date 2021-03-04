/**
 * Made for Robotics TeamPi 2021 Build Season
 * Date: 10/02/2021
 * 
 * Remarks: This file contains the values of all constants and defines
 *
 * 
 **/ 

#pragma once

//motor CAN ID's

const int LFMotor = 1;
const int RFMotor = 2;
const int LBMotor = 3;
const int RBMotor = 4;

const int LFMotorDrive = 5;
const int RFMotorDrive = 6;
const int LBMotorDrive = 7;
const int RBMotorDrive = 8;

//Loader Specifications
const double LoaderMotorSpeed = 0.5;

//Loader Motors

//Loader Sensors

// Encoder and Gear Coeficients

// 360/43000 360/ steps in one swerve module turn 
const double RotationCoeficient = 0.00837209302;

const double DriveCoeficient = 1 ;// to be determined