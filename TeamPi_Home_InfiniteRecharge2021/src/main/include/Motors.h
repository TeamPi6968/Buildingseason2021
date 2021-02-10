#pragma once


#include <rev/CANSparkMax.h>
#include <ctre/phoenix.h>

using namespace rev;  //To avoid writing rev everytime I call something from the rev libraries

class Motors
{
private:

  enum motorCtrlTypes{
    SPARKMAX,
    TALONFX
  };
  motorCtrlTypes motorCtrlType;

  //General fields
  int canID;


  //SparkMax Fields
  CANSparkMax *rtpiSparkMax;
  CANEncoder *rtpiSparkMaxEncoder;
  CANPIDController *rtpiSparkMaxPIDController;
  void RTPI_SparkMax(bool brushless, int canID, double acceleration, bool inverted, bool encoder, bool pidController);
  

  //TalonFX Fields
  WPI_TalonFX* talonFX;



public:
  Motors(Motors::motorCtrlTypes selectType, int canID);
  Motors(Motors::motorCtrlTypes selectType, int canID, bool brushless, double acceleration, bool inverted, bool encoder, bool pidController);
  ~Motors();
  

  //SparkMax Methods
  CANSparkMax *GetSparkMax();
  CANEncoder *GetSparkMaxEncoder();
  CANPIDController *GetSparkMaxPIDController();
  void SetPIDValues(double kP, double kI, double kD, double kMinOutput, double kMaxOutput);

  //TalonFX Methods
  WPI_TalonFX *GetTalonFX();

};


namespace SparkMax{
  
  
}
