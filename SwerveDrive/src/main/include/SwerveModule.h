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
#include <cmath>
#include <iostream>

using namespace std;

class SwerveModule{
 public:
    // init all the swerve motors of the modules
    SwerveModule(int DriveMotorID, int TurningMotorID);
    void SetPID();
    // Zero the wheel position of the swerve.
    void SwerveZero();
    // Set the swerve wheel direction back to 0.
    void SwerveHome();
    // Set swerve to desired pos/ speed.
    void SetDesiredState(float speed, float Direction);

 private:
    WPI_TalonFX DriveMotor;
    WPI_TalonFX TurningMotor; 

    // coef for the motors
    float DriveCoef = Drive_ratio*2 *pi / EncoderResolution;
    float TurnCoef = Turning_ratio*2 *pi / EncoderResolution;

};