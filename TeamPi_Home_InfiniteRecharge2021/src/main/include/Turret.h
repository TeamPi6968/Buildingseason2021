#include <ctre/Phoenix.h>
#include "rev/CANSparkMax.h"
// #include "const.h"
#include <frc/DigitalInput.h>
#include "RobotConstants.h"

using namespace rev;

class Turret {

 public:
    Turret();
    void Shoot(bool shoot, float speed_turret);
    void Rotate(float speed_Rotation);
    void Angle(float speed_Angle);
    bool HomeAngle();
    bool HomeRotation();

    int state_angle = 0;
    int state_rotate = 0;



  private:
    // Config motors
    WPI_TalonFX shoot_motor_master;
    WPI_TalonFX shoot_motor_slave;
    CANSparkMax rotate_motor;
    CANSparkMax angle_motor;
    
    // Digital inputs
    frc::DigitalInput switch_Rotation_1;
    frc::DigitalInput switch_Rotation_2;
    frc::DigitalInput switch_Angle;

    // Config encoders
    // CANEncoder rotate_encoder;
    // CANEncoder angle_encoder;
    
};