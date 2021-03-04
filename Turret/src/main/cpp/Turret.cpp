// #include "const.h"
#include "Turret.h"

Turret::Turret() 
            :shoot_motor_master(shoot_master_CAN), shoot_motor_slave(shoot_slave_CAN), switch_Rotation_1(switch_rotation_port_1),
                switch_Rotation_2(switch_rotation_port_2),rotate_motor(rotate_motor_CAN, rev::CANSparkMax::MotorType::kBrushless), 
                    angle_motor(angle_motor_CAN, rev::CANSparkMax::MotorType::kBrushless), switch_Angle(switch_angle_port){

            // Config followers
            shoot_motor_slave.Follow(shoot_motor_master);

            // Config Rotation default 
            shoot_motor_master.SetInverted(TalonFXInvertType::Clockwise);
	        shoot_motor_slave.SetInverted(TalonFXInvertType::CounterClockwise); //CounterClockwise?FollowMaster
            }


void Turret::Shoot(bool shoot, float speed_turret){
    if (shoot == true){
        shoot_motor_master.Set(speed_turret);
    }
    else if (shoot == false){
        shoot_motor_master.Set(0);
    }
}


void Turret::Rotate(float speed_Rotation){
    if (switch_Rotation_1.Get() == true || switch_Rotation_2.Get() == true){
        rotate_motor.Set(0);
    }
    else {
        rotate_motor.Set(speed_Rotation);
    }
}


void Turret::Angle(float speed_Angle){
    if (switch_Angle.Get() == true){
        rotate_motor.Set(0);
    }
    else {
        angle_motor.Set(speed_Angle);
    }
}

// homing angle turret
bool Turret::HomeAngle(){
    switch(state_angle) {
        // init step 
        case 0:
            state_angle = 1;
            return false;
        
        // check if the limit switch is free, if not rotate the motor so the limitswitch is free
        case 1:
            if (switch_Angle.Get() == true){
                angle_motor.Set(homing_speed);
                return false;}

            else {
                angle_motor.Set(0);
                state_angle = 2;
                return false;}
            break;

        // rotate the motors to hit the limit switch
        case 2:
            if (switch_Angle.Get() == false){
                angle_motor.Set(-homing_speed);
                state_angle = 3;
                return false;}
            break;

        // if the limitswitch is activated, set this as the zero position in the encoder. also enable the soft limits.
        case 3:
            if (switch_Angle.Get() == true){
                angle_motor.Set(0);
               
                CANEncoder angle_encoder = angle_motor.GetEncoder();
                angle_encoder.SetPosition(0);

                std::cout << angle_encoder.GetPosition();

                angle_motor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
                angle_motor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);

                angle_motor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 15);
                angle_motor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 5);
                return true;}
            
            else return false;
            break;
    }
}

// homing rotation turret
bool Turret::HomeRotation(){
    switch(state_rotate) {
        // init step 
        case 0:
            state_rotate = 1;
            return false;
        
        // check if the limit switch is free, if not rotate the motor so the limitswitch is free
        case 1:
            if (switch_Rotation_1.Get() == true){
                rotate_motor.Set(homing_speed);
                return false;}

            else {
                rotate_motor.Set(0);
                state_rotate = 2;
                return false;}
         break;

        // rotate the motors to hit the limit switch
        case 2:
            if (switch_Rotation_1.Get() == false){
                rotate_motor.Set(-homing_speed);
                state_rotate = 3;
                return false;}
         break;

        // if the limitswitch is activated, set this as the zero position in the encoder. also enable the soft limits.
        case 3:
            if (switch_Rotation_1.Get() == true){
                rotate_motor.Set(0);
               
                CANEncoder rotate_encoder = rotate_motor.GetEncoder();
                rotate_encoder.SetPosition(0);

                std::cout << rotate_encoder.GetPosition();

                rotate_motor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
                rotate_motor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);

                rotate_motor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 15);
                rotate_motor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 5);
                return true;}
            
            else return false;
         break;
    }
}