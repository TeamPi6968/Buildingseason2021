#include "Motors.h"


//Use this to initialise only talonfx based motors
Motors::Motors(motorCtrlTypes selectType, int canID){

  if(selectType == TALONFX){
    talonFX = new WPI_TalonFX(canID);
  }
}

/** Use this to initialise only SparkMax based motors
 * @param acceleration Time in seconds to move from 0 to full throtte
 * @param isInverted Set the direction of motor... false is reverse, true is normal forward
 * @param encoder Set to true if you want to use Spark encoders
 * @param PIDcontroller Set to true if you want to use Spark PIDControl
**/
Motors::Motors(motorCtrlTypes selectType, int canID, bool isBrushless, double acceleration, bool isInverted, bool encoder, bool pidController){

  if (selectType == SPARKMAX){
    Motors::RTPI_SparkMax(isBrushless,canID,acceleration,isInverted,encoder,pidController);
  }
}

Motors::~Motors()
{
}

//TalonFX related Methods
WPI_TalonFX* Motors::GetTalonFX(){
  return this->talonFX;
}


//Below is the SparkMax initialisation and setup 
void Motors::RTPI_SparkMax(bool isBrushless, int canID, double acceleration, bool isInverted, bool encoder, bool pidController) {
  if(isBrushless) {
    this->rtpiSparkMax = new CANSparkMax(canID, CANSparkMax::MotorType::kBrushless);
  }
  else {
    this->rtpiSparkMax = new CANSparkMax(canID, CANSparkMax::MotorType::kBrushed);
  }
  rtpiSparkMax->RestoreFactoryDefaults();
  rtpiSparkMax->SetOpenLoopRampRate(acceleration);
  rtpiSparkMax->SetInverted(isInverted);

  if(encoder) {
    rtpiSparkMaxEncoder = new CANEncoder(rtpiSparkMax->GetEncoder());
  }
  if(pidController) {
    rtpiSparkMaxPIDController = new CANPIDController(rtpiSparkMax->GetPIDController());
  }
}

//returns the SparkMax object of selected motor(s)
CANSparkMax *Motors::GetSparkMax() {
  return this->rtpiSparkMax;
}

//returns the SparkMaxEncoder object of selected motor(s)
CANEncoder *Motors::GetSparkMaxEncoder() {
  return this->rtpiSparkMaxEncoder;
}

//returns the SparkMax PIDcontroller object of selected motor(s)
CANPIDController *Motors::GetSparkMaxPIDController() {
  return this->rtpiSparkMaxPIDController;
}

//Set PID values if PID controller is enabled
void Motors::SetPIDValues(double kP, double kI, double kD, double kMinOutput, double kMaxOutput) {
  this->rtpiSparkMaxPIDController->SetP(kP);
  this->rtpiSparkMaxPIDController->SetI(kI);
  this->rtpiSparkMaxPIDController->SetD(kD);
  this->rtpiSparkMaxPIDController->SetOutputRange(kMinOutput, kMaxOutput);
}