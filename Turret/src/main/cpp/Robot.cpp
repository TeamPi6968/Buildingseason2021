// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/SlewRateLimiter.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/Joystick.h>
#include "Turret.h"

class Robot : public frc::TimedRobot, Turret {
 public:


  frc::Joystick m_stick{0};

  float Stick_limx(){
    float xvalue;
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

  float Stick_limy(){
    float yvalue;
    if(m_stick.GetY() < -limy){
      yvalue = -limy;
    } 
    else if(m_stick.GetY() > limy){
      yvalue = limy;
    } 
    else {
      yvalue = m_stick.GetY();
    }
    return yvalue;
  }


  void TeleopInit() override {
    H_angle = HomeAngle();
    H_rotation = HomeRotation();
  }


  void TeleopPeriodic() override {
    if (H_angle == true and H_rotation == true){
      // code here
      Shoot(true, m_stick.GetRawAxis(3));
      Rotate(Stick_limy());
      Angle(Stick_limx());

    }


    // Homing robot
    else if (H_angle == false){
     H_angle = HomeAngle();
    }

    else if (H_angle == true and H_rotation == false){
     H_rotation = HomeRotation();
    }
  }

 private:
  bool H_angle;
  bool H_rotation;
  float limx = 0.1;
  float limy = 0.1;
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
