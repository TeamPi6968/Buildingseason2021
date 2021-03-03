// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <ctre/Phoenix.h>


/**
 * This sample program shows how to control a motor using a joystick. In the
 * operator control part of the program, the joystick is read and the value is
 * written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as
 * range from -1 to 1 making it easy to work together.
 */
class Robot: public frc::TimedRobot {
 private:


  WPI_TalonFX *Motor1 = new WPI_TalonFX(1);
  WPI_TalonFX *Motor2 = new WPI_TalonFX(3);
  WPI_TalonFX *Motor3 = new WPI_TalonFX(5);
  WPI_TalonFX *Motor4 = new WPI_TalonFX(7);

  WPI_TalonFX *Angle1 = new WPI_TalonFX(2);
  WPI_TalonFX *Angle2 = new WPI_TalonFX(4);
  WPI_TalonFX *Angle3 = new WPI_TalonFX(6);
  WPI_TalonFX *Angle4 = new WPI_TalonFX(8);


 

  double limx = 0.2;
  double limy = 0.2;


 public:
  double x;
  double y;
  double angleCoef = 0.00837209302;
  double motorCoef = 0.00837209302; //TBD
  frc::Joystick m_stick{0};

  

  double Stick_limx(){
    double xvalue;
    if(m_stick.GetX() < -limx){
      xvalue = -limx;
    } 
    else if(m_stick.GetX() > limx){
      xvalue = limx;
    } 
    else {
      xvalue = m_stick.GetX();
    }
    return xvalue;
  }

  double Stick_limy(){
    double yvalue;
    if(m_stick.GetY() < -limy){
      yvalue = -limy;
    } 
    else if(m_stick.GetY()*0.7 > limy){
      yvalue = limy;
    } 
    else {
      yvalue = m_stick.GetY();
    }
    return yvalue;
  }

  void TeleopInit() override {
   Angle1->SetSelectedSensorPosition(0,0,50);
   Angle2->SetSelectedSensorPosition(0,0,50);
   Angle3->SetSelectedSensorPosition(0,0,50);
   Angle4->SetSelectedSensorPosition(0,0,50);

   Angle1->ConfigSelectedFeedbackCoefficient(angleCoef,0,50);
   Angle2->ConfigSelectedFeedbackCoefficient(angleCoef,0,50);
   Angle3->ConfigSelectedFeedbackCoefficient(angleCoef,0,50);
   Angle4->ConfigSelectedFeedbackCoefficient(angleCoef,0,50);






  // Motor1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);
  // Motor2->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 10);

  }

 void TeleopPeriodic() override { 
    Motor1->Set(Stick_limy()); 
    Motor2->Set(-Stick_limy()); 
    Motor3->Set(Stick_limy()); 
    Motor4->Set(-Stick_limy()); 
    //
    // Motor1->Config_kP(0,0.05);
    // Motor1->Config_kI(0,0);
    // Motor1->Config_kD(0,0);
    // Motor1->Set(ControlMode::Position,m_stick.GetX());
   
    Angle1->Config_kP(0,0.5);
    Angle1->Config_kI(0,0);
    Angle1->Config_kD(0,0.1);
    Angle1->Set(ControlMode::Position,m_stick.GetX()*720);

    Angle2->Config_kP(0,0.5);
    Angle2->Config_kI(0,0);
    Angle2->Config_kD(0,0.1);
    Angle2->Set(ControlMode::Position,m_stick.GetX()*720);

    Angle3->Config_kP(0,0.5);
    Angle3->Config_kI(0,0);
    Angle3->Config_kD(0,0.1);
    Angle3->Set(ControlMode::Position,m_stick.GetX()*720);

    Angle4->Config_kP(0,0.5);
    Angle4->Config_kI(0,0);
    Angle4->Config_kD(0,0.1);
    Angle4->Set(ControlMode::Position,m_stick.GetX()*720);
    
  
    // Angle1->Set(Stick_limy());

    
    // Angle2->Set(Stick_limy());
    // Angle3->Set(Stick_limy());
    // Angle4->Set(Stick_limy());

    double pos1 = Angle1->GetSelectedSensorPosition();
    double pos2 = Angle2->GetSelectedSensorPosition();
    // double pos3 = Angle3->GetSelectedSensorPosition();
    // double pos4 = Angle4->GetSelectedSensorPosition();

    std::cout << "ONE "<< pos1 <<" \n"; 
    std::cout << "TWO "<< pos2<<" \n"; 
  //  std::cout << "ONE "<< pos1<<" \n"; 
  //  std::cout << "ONE "<< pos1<<" \n"; 
    // std::cout << pos2;

  }

  void AutonomousInit() override{
    Motor1->SetSelectedSensorPosition(0,0,50);  
    Motor2->SetSelectedSensorPosition(0,0,50);
    Motor3->SetSelectedSensorPosition(0,0,50);
    Motor4->SetSelectedSensorPosition(0,0,50);

    // Motor2->Follow(*Motor1);
    // Motor3->Follow(*Motor1);
    // Motor4->Follow(*Motor1);

    Motor1->ConfigSelectedFeedbackCoefficient(motorCoef,0,50);
    Motor2->ConfigSelectedFeedbackCoefficient(motorCoef,0,50);
    Motor3->ConfigSelectedFeedbackCoefficient(motorCoef,0,50);
    Motor4->ConfigSelectedFeedbackCoefficient(motorCoef,0,50);


    Angle1->SetSelectedSensorPosition(0,0,50);  
    Angle2->SetSelectedSensorPosition(0,0,50);
    Angle3->SetSelectedSensorPosition(0,0,50);
    Angle4->SetSelectedSensorPosition(0,0,50);

    Angle1->ConfigSelectedFeedbackCoefficient(angleCoef,0,50);
    Angle2->ConfigSelectedFeedbackCoefficient(angleCoef,0,50);
    Angle3->ConfigSelectedFeedbackCoefficient(angleCoef,0,50);
    Angle4->ConfigSelectedFeedbackCoefficient(angleCoef,0,50);

  }
  void AutonomousPeriodic() override{


    Motor1->Config_kP(0,0.5);
    Motor1->Config_kI(0,0);
    Motor1->Config_kD(0,0.1);
    Motor1->Set(ControlMode::Position,360); //Must check

    Motor2->Config_kP(0,0.5);
    Motor2->Config_kI(0,0);
    Motor2->Config_kD(0,0.1);
    Motor2->Set(ControlMode::Position,360);

    Motor3->Config_kP(0,0.5);
    Motor3->Config_kI(0,0);
    Motor3->Config_kD(0,0.1);
    Motor3->Set(ControlMode::Position,360);

    Motor4->Config_kP(0,0.5);
    Motor4->Config_kI(0,0);
    Motor4->Config_kD(0,0.1);
    Motor4->Set(ControlMode::Position,360);

    double pos1 = Motor1->GetSelectedSensorPosition();
    double pos2 = Motor2->GetSelectedSensorPosition();
    // double pos3 = Angle3->GetSelectedSensorPosition();
    // double pos4 = Angle4->GetSelectedSensorPosition();

    std::cout << "ONE "<< pos1 <<" \n"; 
    std::cout << "TWO "<< pos2<<" \n"; 
  //  std::cout << "ONE "<< pos1<<" \n"; 
  //  std::cout << "ONE "<< pos1<<" \n"; 
    // std::cout << pos2;

    Angle1->Config_kP(0,0.5);
    Angle1->Config_kI(0,0);
    Angle1->Config_kD(0,0.1);
    Angle1->Set(ControlMode::Position, 720);

    Angle2->Config_kP(0,0.5);
    Angle2->Config_kI(0,0);
    Angle2->Config_kD(0,0.1);
    Angle2->Set(ControlMode::Position, 720);

    Angle3->Config_kP(0,0.5);
    Angle3->Config_kI(0,0);
    Angle3->Config_kD(0,0.1);
    Angle3->Set(ControlMode::Position, 720);

    Angle4->Config_kP(0,0.5);
    Angle4->Config_kI(0,0);
    Angle4->Config_kD(0,0.1);
    Angle4->Set(ControlMode::Position, 720);
  }
};



#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
