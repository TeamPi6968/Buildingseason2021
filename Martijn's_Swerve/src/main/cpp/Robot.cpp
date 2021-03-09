/** Made for Robotics TeamPi 2021 Build Season
  * Author: Martijn van de Sande
  * Year: 2021
  * Date: 06-03-2021 // created
  * 
  * Remarks: Drive with the swerve bot.
**/

#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/Joystick.h>
#include "Drivetrain.h"



class Robot : public frc::TimedRobot {
  private:
  Drivetrain Swerve;
  frc::Joystick m_stick{0};
  public:
  void RobotInit() override{
    
  }
  void RobotPeriodic() override{}

  // void Robot::AutonomousInit() {}
  // void Robot::AutonomousPeriodic() {}

  void TeleopInit() override{
    Swerve.SetAllPID();
    Swerve.ZeroDrivetrain();
  }

  void TeleopPeriodic() override{
    Swerve.Drive(m_stick.GetX(), m_stick.GetY(), m_stick.GetRawAxis(5));
  }

  // void Robot::DisabledInit() {}
  // void Robot::DisabledPeriodic() {}

  // void Robot::TestInit() {}
  // void Robot::TestPeriodic() {}
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
