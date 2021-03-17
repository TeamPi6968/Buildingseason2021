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
   SwerveModule module_frontLeft{LFMotorDrive, LFMotor};
//   SwerveModule module_frontRight{RFMotorDrive, RFMotor};
//   SwerveModule module_backLeft{LBMotorDrive, LBMotor};
//   SwerveModule module_backRight{RBMotorDrive, RBMotor};
// }

void Drivetrain::MathSwerve(double xValue, double yValue, double rot){
    if (rot == 0){
        // calc the speed and oriantation of the mod  (speed, direction)
        double SwerveModVal [4][2] = {{sqrt(pow(xValue, 2)+ pow(yValue, 2)) * MaxSpeed, atan(xValue/yValue)},
                                        {sqrt(pow(xValue, 2)+ pow(yValue, 2)) * MaxSpeed, atan(xValue/yValue)},
                                        {sqrt(pow(xValue, 2)+ pow(yValue, 2)) * MaxSpeed, atan(xValue/yValue)},
                                        {sqrt(pow(xValue, 2)+ pow(yValue, 2)) * MaxSpeed, atan(xValue/yValue)}};
        
            Speedfl = SwerveModVal[0][0]*(180/pi);
            Directionfl = SwerveModVal[0][1]*(180/pi);
            Speedfr = SwerveModVal[1][0]*(180/pi);
            Directionfr = SwerveModVal[1][1]*(180/pi);
            Speedbl = SwerveModVal[2][0]*(180/pi);
            Directionbl = SwerveModVal[2][1]*(180/pi);
            Speedbr = SwerveModVal[3][0]*(180/pi);
            Directionbr = SwerveModVal[3][1]*(180/pi);

        
    }
    else{
        // calc the rot speed
        double rotVel = rot * MaxRad;

        // vector calc per module  (x, y) 
        double VectorFL[2] = {rotVel * DistanceMod[0] * cos(RotVecInRad) + xValue * MaxSpeed, rotVel * DistanceMod[0] * sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorFR[2] = {rotVel * DistanceMod[1] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[1] * sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorBL[2] = {-rotVel * DistanceMod[2] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[2] * sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorBR[2] = {-rotVel * DistanceMod[3] * cos(RotVecInRad) + xValue * MaxSpeed, rotVel * DistanceMod[3] * sin(RotVecInRad) + yValue * MaxSpeed};

        // calc the speed and oriantation of the mod  (speed, direction)
        double SwerveModValRot [4][2] = {{sqrt(pow(VectorFL[0], 2)+ pow(VectorFL[1], 2)), atan(VectorFL[0]/VectorFL[1])},
                                            {sqrt(pow(VectorFR[0], 2)+ pow(VectorFR[1], 2)), atan(VectorFR[0]/VectorFR[1])},
                                            {sqrt(pow(VectorBL[0], 2)+ pow(VectorBL[1], 2)), atan(VectorBL[0]/VectorBL[1])},
                                            {sqrt(pow(VectorBR[0], 2)+ pow(VectorBR[1], 2)), atan(VectorBR[0]/VectorBR[1])}};

            Speedfl = SwerveModValRot[0][0]*(180/pi);
            Directionfl = SwerveModValRot[0][1]*(180/pi);
            Speedfr = SwerveModValRot[1][0]*(180/pi);
            Directionfr = SwerveModValRot[1][1]*(180/pi);
            Speedbl = SwerveModValRot[2][0]*(180/pi);
            Directionbl = SwerveModValRot[2][1]*(180/pi);
            Speedbr = SwerveModValRot[3][0]*(180/pi);
            Directionbr = SwerveModValRot[3][1]*(180/pi);
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
void Drivetrain::Drive(double xValue, double yValue, double rotation){
    // math 
    // double Speed = MathSpeed(xValue, yValue);
    // double Direction = MathDirection(xValue, yValue);
    // prevDirection = Direction;
    MathSwerve(xValue, yValue, rotation);
    // cout <<  Speed_Direction << "\n";
    // Speedfl = Speed_Direction[0][0];
    // cout << "after set val1" << "\n";
    // Directionfl = Speed_Direction[0][1];
    // cout << "after set val1" << "\n";
    // Speedfr = Speed_Direction[1][0];
    // cout << "after set val2" << "\n";
    // Directionfr = Speed_Direction[1][1];
    // cout << "after set val2" << "\n";
    // Speedbl = Speed_Direction[2][0];
    // cout << "after set val3" << "\n";
    // Directionbl = Speed_Direction[2][1];
    // cout << "after set val3" << "\n";
    // Speedbr = Speed_Direction[3][0];
    // cout << "after set val4" << "\n";
    // Directionbr = Speed_Direction[3][1];

  
    // // set var to calc var, this needs to change in the futere when the rot will be integrated to the sys.
    // Speedfl = Speedfr = Speedbl = Speedbr = Speed;
    // Directionfl = Directionfr = Directionbl = Directionbr = Direction; 
 
    // cout << Speedfl << ' '  << Directionfl << ' '  << Speedfr << ' '  << Directionfr  << ' '  << Speedbl << ' '  << Directionbl << ' '  << Speedbr << ' '  << Directionbr << "\n"; 
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

