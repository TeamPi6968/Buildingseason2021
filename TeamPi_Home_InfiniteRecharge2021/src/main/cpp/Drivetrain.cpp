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
//    SwerveModule module_frontLeft{LFMotorDrive, LFMotor};
//   SwerveModule module_frontRight{RFMotorDrive, RFMotor};
//   SwerveModule module_backLeft{LBMotorDrive, LBMotor};
//   SwerveModule module_backRight{RBMotorDrive, RBMotor};
// }

void Drivetrain::MathSwerve(double xValue, double yValue, double rot){
    // calc the rot speed
    double rotVel = rot * MaxRad;

    // vector calc per module  (x, y)
    double VectorFL[2] = {rotVel * DistanceMod[0] * cos(RotVecInRad) + xValue * MaxSpeed, rotVel * DistanceMod[0] * sin(RotVecInRad) + yValue * MaxSpeed};
    double VectorFR[2] = {rotVel * DistanceMod[1] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[1] * sin(RotVecInRad) + yValue * MaxSpeed};
    double VectorBL[2] = {-rotVel * DistanceMod[2] * cos(RotVecInRad) + xValue * MaxSpeed, rotVel * DistanceMod[2] * sin(RotVecInRad) + yValue * MaxSpeed};
    double VectorBR[2] = {-rotVel * DistanceMod[3] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[3] * sin(RotVecInRad) + yValue * MaxSpeed};

    // calc the speed and oriantation of the mod  (speed, direction)
    double SwerveModValRot [4][2] = {{sqrt(pow(VectorFL[0], 2)+ pow(VectorFL[1], 2)), atan2(VectorFL[1], VectorFL[0])},
                                        {sqrt(pow(VectorFR[0], 2)+ pow(VectorFR[1], 2)), atan2(VectorFR[1], VectorFR[0])},
                                        {sqrt(pow(VectorBL[0], 2)+ pow(VectorBL[1], 2)), atan2(VectorBL[1], VectorBL[0])},
                                        {sqrt(pow(VectorBR[0], 2)+ pow(VectorBR[1], 2)), atan2(VectorBR[1], VectorBR[0])}};

    Speedfl = SwerveModValRot[0][0]*(180/pi);
    Directionfl = SwerveModValRot[0][1]*(180/pi) -90;
    Speedfr = SwerveModValRot[1][0]*(180/pi);
    Directionfr = SwerveModValRot[1][1]*(180/pi) -90;
    Speedbl = SwerveModValRot[2][0]*(180/pi);
    Directionbl = SwerveModValRot[2][1]*(180/pi) -90;
    Speedbr = SwerveModValRot[3][0]*(180/pi);
    Directionbr = SwerveModValRot[3][1]*(180/pi) -90;

}

// zero all the modules.
void Drivetrain::ZeroDrivetrain(){

  prevX = 0;
  prevY = 0;
  prevRotation = 0;
  Move = 0;

    PrevDirectionfl = 0;
    PrevDirectionfr = 0;
    PrevDirectionbl = 0;
    PrevDirectionbr = 0;

    AngleCorrectionFl = 0;
    AngleCorrectionFr = 0;
    AngleCorrectionBl = 0;
    AngleCorrectionBr = 0;

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
    // Get rid of deadzone controller
    if (rotation < 0.1 && rotation > 0 || rotation > -0.1 && rotation < 0 ){rotation = 0;}
    if (xValue < 0.1 && xValue > 0 || xValue > -0.1 && xValue < 0 ){xValue = 0;}
    if (yValue < 0.1 && yValue > 0 || yValue > -0.1 && yValue < 0 ){yValue = 0;}

    if (xValue == 0 && yValue == 0 && rotation == 0){xValue = prevX; yValue = prevY; rotation = prevRotation; Move = 0;}
    else
    {
        prevX = xValue;
        prevY = yValue;
        prevRotation = rotation;
        Move = 1;
    }


    // math
    MathSwerve(xValue, yValue, rotation);
    AngleCorrection();

    static double setpoint = 0;

    //visualisation rotation speed
    frc::SmartDashboard::PutNumber("Direction_FL", Directionfl + AngleCorrectionFl);
    frc::SmartDashboard::PutNumber("Direction_FR", Directionfr + AngleCorrectionFr);
    frc::SmartDashboard::PutNumber("Direction_BL", Directionbl + AngleCorrectionBl);
    frc::SmartDashboard::PutNumber("Direction_BR", Directionbr + AngleCorrectionBr);

    // setpoint= frc::SmartDashboard::GetNumber("Setpoint", setpoint);


    cout << Speedfl << ' '  << Directionfl << ' '  << Speedfr << ' '  << Directionfr  << ' '  << Speedbl << ' '  << Directionbl << ' '  << Speedbr << ' '  << Directionbr << "\n";
    module_frontLeft.SetDesiredState(Speedfl * Move, Directionfl + AngleCorrectionFl);
    // cout << "thing: " << Directionfl + AngleCorrectionFl << "\n";
    module_frontRight.SetDesiredState(Speedfr * Move, Directionfr + AngleCorrectionFr);
    module_backLeft.SetDesiredState(Speedbl * Move, Directionbl + AngleCorrectionBl);
    module_backRight.SetDesiredState(Speedbr * Move, Directionbr + AngleCorrectionBr);

}

void Drivetrain::AngleCorrection(){
// clean this code up
int idk1 = -180;
int idk2 = 0;
    cout << PrevDirectionfl << "\n";

        if(PrevDirectionfl > idk2 && Directionfl < 0){
            AngleCorrectionFl = AngleCorrectionFl + 360 ;
        }
        else if (PrevDirectionfl < idk1 && Directionfl > 0){
            AngleCorrectionFl = AngleCorrectionFl - 360 ;
        }
        PrevDirectionfl = Directionfl;
//-------------------------------------------------------
        if(PrevDirectionfr > idk2 && Directionfr < 0){
            AngleCorrectionFr = AngleCorrectionFr + 360 ;
        }
        else if (PrevDirectionfr < idk1 && Directionfr > 0){
            AngleCorrectionFr = AngleCorrectionFr - 360 ;
        }
        PrevDirectionfr = Directionfr;
//------------------------------------------------------
        if(PrevDirectionbl > idk2 && Directionbl < 0){
            AngleCorrectionBl = AngleCorrectionBl + 360 ;
        }
        else if (PrevDirectionbl < idk1 && Directionbl > 0){
            AngleCorrectionBl = AngleCorrectionBl - 360 ;
        }
        PrevDirectionbl = Directionbl;
//-----------------------------------------------------
        if(PrevDirectionbr > idk2 && Directionbr < 0){
            AngleCorrectionBr = AngleCorrectionBr + 360 ;
        }
        else if (PrevDirectionbr < idk1 && Directionbr > 0){
            AngleCorrectionBr = AngleCorrectionBr - 360 ;
        }
        PrevDirectionbr = Directionbr;

}
