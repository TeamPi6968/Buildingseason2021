/** Made for Robotics TeamPi 2021 Build Season
  * Author: Martijn van de Sande
  * Year: 2021
  * Date: 06-03-2021 // created
  * 
  * Edit: 07-03-2021 // added some basic math to test driving the swerve bot.
  * 
  * Remarks: Create the modules and functions to drive with the swerve bot.
**/

#include "Drivetrain.h" 

// Drivetrain::Drivetrain(){
// // create the swervedrive modules.
//   SwerveModule module_frontLeft{LFMotorDrive, LFMotor};
//   SwerveModule module_frontRight{RFMotorDrive, RFMotor};
//   SwerveModule module_backLeft{LBMotorDrive, LBMotor};
//   SwerveModule module_backRight{RBMotorDrive, RBMotor};
// }

auto Drivetrain::MathSwerve(float xValue, float yValue, float rot){
    if (rot == 0){
        // calc the speed and oriantation of the mod  (speed, direction)
        float SwerveModVal [4][2] = {{sqrt(pow(xValue, 2)+ pow(yValue, 2)) * MaxSpeed, atan(xValue/yValue)},
                                        {sqrt(pow(xValue, 2)+ pow(yValue, 2)) * MaxSpeed, atan(xValue/yValue)},
                                        {sqrt(pow(xValue, 2)+ pow(yValue, 2)) * MaxSpeed, atan(xValue/yValue)},
                                        {sqrt(pow(xValue, 2)+ pow(yValue, 2)) * MaxSpeed, atan(xValue/yValue)}};

        return SwerveModVal;
    }
    else{
        // calc the rot speed
        rot = rot * MaxRad;

        // vector calc per module  (x, y) 
        float VectorFL[2] = {rot * DistanceMod[0] * cos(RotVecInRad) + xValue * MaxSpeed, rot * DistanceMod[0] * sin(RotVecInRad) + yValue * MaxSpeed};
        float VectorFR[2] = {rot * DistanceMod[1] * cos(RotVecInRad) + xValue * MaxSpeed, -rot * DistanceMod[1] * sin(RotVecInRad) + yValue * MaxSpeed};
        float VectorBL[2] = {-rot * DistanceMod[2] * cos(RotVecInRad) + xValue * MaxSpeed, -rot * DistanceMod[2] * sin(RotVecInRad) + yValue * MaxSpeed};
        float VectorBR[2] = {-rot * DistanceMod[3] * cos(RotVecInRad) + xValue * MaxSpeed, rot * DistanceMod[3] * sin(RotVecInRad) + yValue * MaxSpeed};

        // calc the speed and oriantation of the mod  (speed, direction)
        float SwerveModValRot [4][2] = {{sqrt(pow(VectorFL[0], 2)+ pow(VectorFL[1], 2)), atan(VectorFL[0]/VectorFL[1])},
                                            {sqrt(pow(VectorFR[0], 2)+ pow(VectorFR[1], 2)), atan(VectorFR[0]/VectorFR[1])},
                                            {sqrt(pow(VectorBL[0], 2)+ pow(VectorBL[1], 2)), atan(VectorBL[0]/VectorBL[1])},
                                            {sqrt(pow(VectorBR[0], 2)+ pow(VectorBR[1], 2)), atan(VectorBR[0]/VectorBR[1])}};

        return SwerveModValRot;
    }
}

// zero all the modules.
void Drivetrain::ZeroDrivetrain(){
    module_frontLeft.SwerveZero();
    module_frontRight.SwerveZero();
    module_backLeft.SwerveZero();
    module_backRight.SwerveZero();
}

// home all the modules.
void Drivetrain::DrivetrainHome(){
    module_frontLeft.SwerveHome();
    module_frontRight.SwerveHome();
    module_backLeft.SwerveHome();
    module_backRight.SwerveHome();
}

void Drivetrain::SetAllPID(){
    module_frontLeft.SetPID();
    module_frontRight.SetPID();
    module_backLeft.SetPID();
    module_backRight.SetPID();
}

// Drive with the swerve drive.
void Drivetrain::Drive(float xValue, float yValue, float rotation){
    // math 
    // double Speed = MathSpeed(xValue, yValue);
    // double Direction = MathDirection(xValue, yValue);
    // prevDirection = Direction;

    auto Speed_Direction = MathSwerve(xValue, yValue, rotation);

    float Speedfl = Speed_Direction[0][0];
    float Directionfl = Speed_Direction[0][1];
    float Speedfr = Speed_Direction[1][0];
    float Directionfr = Speed_Direction[1][1];
    float Speedbl = Speed_Direction[2][0];
    float Directionbl = Speed_Direction[2][1];
    float Speedbr = Speed_Direction[3][0];
    float Directionbr = Speed_Direction[3][1];
  
    // // set var to calc var, this needs to change in the futere when the rot will be integrated to the sys.
    // Speedfl = Speedfr = Speedbl = Speedbr = Speed;
    // Directionfl = Directionfr = Directionbl = Directionbr = Direction; 

    module_frontLeft.SetDesiredState(Speedfl, Directionfl);
    module_frontRight.SetDesiredState(Speedfr, Directionfr);
    module_backLeft.SetDesiredState(Speedbl, Directionbl);
    module_backRight.SetDesiredState(Speedbr, Directionbr);
}

// // math for driving with the serve.
// double Drivetrain::MathSpeed(double xVal, double yVal){
//     if (xVal < 0){xVal = -xVal;}
//     if (yVal < 0){yVal = -yVal;}

//     double speed = sqrt(pow(xVal,2) + pow(yVal,2));
//     // do some math here

//     speed = speed * MaxSpeed;

//     cout << "speed = " << speed << "\n";
//     return speed;
// }

// // math for driving with the serve.
// double Drivetrain::MathDirection(double xVal, double yVal){
//     double Angle = 0;
    
//     if (xVal == 0 && yVal == 0){
//         Angle = prevDirection;
//     }

//     else if (xVal > 0 && yVal > 0){
//         Angle = atan(yVal/xVal);
//     }

//     else if (xVal > 0 && yVal < 0){
//         Angle = atan(-yVal/xVal) + 90;
//     }

//     else if (xVal < 0 && yVal < 0){
//         Angle = atan(-yVal/-xVal) + 180;
//     }

//     else if (xVal < 0 && yVal > 0){
//         Angle = atan(yVal/-xVal) + 270;
//     }

//     cout << "Angle = " << Angle << "\n";
//     return Angle;
// }

