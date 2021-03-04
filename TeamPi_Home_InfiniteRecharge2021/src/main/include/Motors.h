/**
 * Made for Robotics TeamPi 2021 Build Season
 * Author: Caleb Kyei
 * Date: 10/02/2021 14:00
 * 
 * Remarks: Can be resused for newer motor controllers by simply
 *          overloading the constructor to accommodate initialisation
 *          process and adding functions in between
 * 
 **/


#pragma once


#include <rev/CANSparkMax.h>
#include <ctre/phoenix.h>

using namespace rev;  //To avoid writing rev everytime I call something from the rev libraries

class Motors
{
private:

  //General fields
  int canID;


  //SparkMax Fields
  CANSparkMax *rtpiSparkMax;
  CANEncoder *rtpiSparkMaxEncoder;
  CANPIDController *rtpiSparkMaxPIDController;
  void RTPI_SparkMax(bool isBrushless, int canID, double acceleration, bool isInverted, bool encoder, bool pidController);


  //TalonFX Fields
  WPI_TalonFX* talonFX;



public:

  //Select the motor controller type... 
  enum motorCtrlTypes{
    SPARKMAX,
    TALONFX
  };

  Motors(motorCtrlTypes selectType, int canID);
  Motors(motorCtrlTypes selectType, int canID, bool isBrushless, double acceleration, bool isInverted, bool encoder, bool pidController);
  ~Motors();
  

  //SparkMax Methods
  CANSparkMax *GetSparkMax();
  CANEncoder *GetSparkMaxEncoder();
  CANPIDController *GetSparkMaxPIDController();
  void SetPIDValues(double kP, double kI, double kD, double kMinOutput, double kMaxOutput);

  //TalonFX Methods
  WPI_TalonFX *GetTalonFX();

};
