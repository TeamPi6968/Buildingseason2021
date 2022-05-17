#pragma once
#include <frc/Compressor.h>
#include <frc/DoubleSolenoid.h>
#include <frc/GenericHID.h>
#include "rev/CANSparkMax.h"
#include <frc/Joystick.h>
#include "Intake_Storage_Loader/C04_PI_Pixy.h"
#include <frc/smartdashboard/SmartDashboard.h> 

class Intake {
private:
//variables
bool StatusIntake = 0;
bool thing = 0;
double IntakeMotorSpeed = 0.6;

//setup compressor
frc::Compressor Comp{0,frc::PneumaticsModuleType::CTREPCM};
bool pressureSwitch = Comp.GetPressureSwitchValue();
bool enabled = Comp.Enabled();

//setup doublesolonoids
frc::DoubleSolenoid SolonoidLeft {0,frc::PneumaticsModuleType::CTREPCM,0,1};

//setup motors of intake
static const int SparkMaxIntakeID = 17;

//Pixy 2 Values


rev::CANSparkMax SparkMaxIntake{SparkMaxIntakeID, rev::CANSparkMax::MotorType::kBrushed};

public:

void IntakeMotor();
void IntakeSolonoids (bool buttonPressed, int cellAmount);
void IntakeMotors (bool buttonPressed, int cellAmount);
};
// DoubleSolenoid;
// double current = c.GetCompressorCurrent()