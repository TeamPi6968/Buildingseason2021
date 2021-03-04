/**
 * Made for Robotics TeamPi 2021 Build Season
 * Date: 10/02/2021
 * 
 * Remarks: This file contains the values of all constants and defines
 *
 * 
 **/ 

#pragma once

//Testing
const double firstStep = 120.0;
const double turn90 = 90;

//Swerve Drive
//motor CAN ID's
#define PIDslot 0
#define SwervekP 0.5
#define SwervekI 0.0
#define SwervekD 0.1

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

//Motors
#define brushed true
#define brushless false
#define inverted true
#define nInverted false
#define hasEncoder true
#define noEncoder false
#define hasPID true
#define noPID false

#define accelerate 1

//Loader Specifications
//Loader Motors
//Brushed
const double LoaderMotorSpeed = 0.4;
const int LoadercanID1 = 1;
const int LoadercanID2 = 2;

//Loader Sensors

// Encoder and Gear Coeficients

// 360/43000 360/ steps in one swerve module turn 
const double RotationCoeficient = 0.00837209302; //0.047619047619047619

const double DriveCoeficient = 31.9024; //0.040178571428; // to be determined 31.9024cm is 1 rotation


//--------- Turret System
    // Motor ID's 
    const int shoot_master_CAN = 0;
    const int shoot_slave_CAN = 1;
    const int rotate_motor_CAN = 2;
    const int angle_motor_CAN = 3;

    // Roborio ID's
    const int switch_rotation_port_1 = 0;
    const int switch_rotation_port_2 = 1;
    const int switch_angle_port = 2;

    // var
    const int homing_speed = 0.2;
    const double turretSpeed = 0.5;

//Storage Motors
//Brushed
const double StorageMotorSpeed = 0.4;
const int StoragecanID1 = 1;
const int StoragecanID2 = 2;



//Intake Motors
//Brushed
//reed switches

//Turret motors
//Brushless
