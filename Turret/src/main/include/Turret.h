#include <ctre/Phoenix.h>
#include "rev/CANSparkMax.h"
// #include "const.h"
#include <frc/DigitalInput.h>

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

    // Motor ID's 
    int const shoot_master_CAN = 0;
    int const shoot_slave_CAN = 1;
    int const rotate_motor_CAN = 2;
    int const angle_motor_CAN = 3;

    // Roborio ID's
    int const switch_rotation_port_1 = 0;
    int const switch_rotation_port_2 = 1;
    int const switch_angle_port = 2;

    // var
    int const homing_speed = 0.2;



    // Config encoders
    // CANEncoder rotate_encoder;
    // CANEncoder angle_encoder;
    
};