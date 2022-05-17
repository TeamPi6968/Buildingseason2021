/** Made for Robotics TeamPi 2021 Build Season
  * Author: Marius Drop
  * Year: 2021
  * Date: 22-03-2021 // created
  * 
  * Edit: 23-03-2021 // added variables for homing functionality
**/

#pragma once

#include <frc/DigitalInput.h>
#include <rev/CANSparkMax.h>
#include <frc/smartdashboard/SmartDashboard.h> 

using namespace frc;
using namespace rev;

class Outtake
{
private:
// Motor IDs
static const int SparkMaxAngleID = 15;
static const int SparkMaxRotationID = 16;

// Create motor variable
CANSparkMax SparkMaxAngleMotor{SparkMaxAngleID, CANSparkMax::MotorType::kBrushless};
CANSparkMax SparkMaxRotationMotor{SparkMaxRotationID, CANSparkMax::MotorType::kBrushless};

// Encoders
SparkMaxRelativeEncoder *SparkMaxAngleEncoder = new SparkMaxRelativeEncoder(SparkMaxAngleMotor.GetEncoder());
SparkMaxRelativeEncoder *SparkMaxRotationEncoder = new SparkMaxRelativeEncoder(SparkMaxRotationMotor.GetEncoder());

// limit switches
DigitalInput angleLimit{3};
DigitalInput rotationLimit{0};

// Motor speeds
double angleSpeed = 0.08;
double rotationSpeed = 0.1;  

// Angle position
int minAngleEncoder = -45;
int maxAngleEncoder = -3;

double angleHomePosition = -15.5;
double angleHomePositionMax = angleHomePosition + 0.3;
double angleHomePositionMin = angleHomePosition - 0.3;

// Rotation position
int minRotationEncoder = -40;
int maxRotationEncoder = -2;

double rotationHomePosition = -14.5;
double rotationHomePositionMax = rotationHomePosition + 0.3;
double rotationHomePositionMin = rotationHomePosition - 0.3;

public:
// Calibration
bool Calibrated = false;
bool startButtonPressed = false;
bool rotationCalibrated = false;
bool rotationLimitPressed = false;
bool angleCalibrated = false;
bool angleLimitPressed = false;

// Homing
bool rotationHomed = false;
bool angleHomed = false;

// General functions
void Move(double xValue, double yValue);
void Home(bool L3Pressed, bool R3Pressed);
void Calibration(bool startButtonPressed);
void Reset(bool buttonPressed);

// Functions for rotation
void SetRotation(double xValue);
void rotationHome(bool L3Pressed);
void RotationCalibration();
void displayRotationEncoder();
void testRotationLimit();

// Functions for angle change
void SetAngle(double yValue);
void angleHome(bool R3Pressed);
void AngleCalibration();
void displayAngleEncoder();
void testAngleLimit();
};