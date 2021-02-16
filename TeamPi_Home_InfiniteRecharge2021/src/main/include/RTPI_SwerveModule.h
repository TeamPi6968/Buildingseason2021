/**
 * Made for Robotics TeamPi 2021 Build Season
 * Author: 
 * Date: 
 * 
 * Remarks: 
 * 
 **/
#pragma once


#include "Motors.h" 

class RTPI_SwerveModule
{
private:
Motors* speedMotor;
Motors* turnMotor;



    /* data */
public:
void setAngle();
void bestAngle();
void setSpeed();

    RTPI_SwerveModule(Motors * speedMotor, Motors* turnMotor);
    ~RTPI_SwerveModule();
};


