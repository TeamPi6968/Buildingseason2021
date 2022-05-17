/** Made for Robotics TeamPi 2021 Build Season
  * Author: Martijn van de Sande
  * Year: 2021
  * Date: 06-03-2021 // created
  *
  * Edit: 07-03-2021 // added some basic math to test driving the swerve bot.
  *
  * Remarks: Create the modules and functions to drive with the swerve bot.
**/

#include "SwerveDrive/Drivetrain.h"

void Drivetrain::MathSwerve(double xValue, double yValue, double rot){
    // calc the rotation speed
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

    // assing all the values of the calculations to the correct module.
    Speedfl = SwerveModValRot[0][0]*(180/pi);
    Directionfl = SwerveModValRot[0][1]*(180/pi) -90; // <- fix this thing. (-90)
    Speedfr = SwerveModValRot[1][0]*(180/pi);
    Directionfr = SwerveModValRot[1][1]*(180/pi) -90;
    Speedbl = SwerveModValRot[2][0]*(180/pi);
    Directionbl = SwerveModValRot[2][1]*(180/pi) -90;
    Speedbr = SwerveModValRot[3][0]*(180/pi);
    Directionbr = SwerveModValRot[3][1]*(180/pi) -90;

}

// zero all the modules.
void Drivetrain::ZeroDrivetrain(){
// define values for the driving function.
{
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
}
    
    // Set all the encoders to 0.
    module_frontLeft.SwerveZero();
    module_frontRight.SwerveZero();
    module_backLeft.SwerveZero();
    module_backRight.SwerveZero();
}

//Stop
void Drivetrain::Stop(){
    module_frontLeft.StopMotor();
    module_frontRight.StopMotor();
    module_backLeft.StopMotor();
    module_backRight.StopMotor();   
}

//Stop drive movement
void Drivetrain::StopDrive(){
    module_frontLeft.StopDriving();
    module_frontRight.StopDriving();
    module_backLeft.StopDriving();
    module_backRight.StopDriving();   
}

// home all the modules.
void Drivetrain::DrivetrainHome(){
    module_frontLeft.SwerveHome();
    module_frontRight.SwerveHome();
    module_backLeft.SwerveHome();
    module_backRight.SwerveHome();
}

// Set all PID values for each module.
void Drivetrain::SetAllPID(){
    module_frontLeft.SetPID();
    module_frontRight.SetPID();
    module_backLeft.SetPID();
    module_backRight.SetPID();
}

// Set all PID values for each module.
void Drivetrain::SetDrivePID(double kp, double ki, double kd){
    module_frontLeft.SetPIDDrive(kp,ki,kd);
    module_frontRight.SetPIDDrive(kp,ki,kd);
    module_backLeft.SetPIDDrive(kp,ki,kd);
    module_backRight.SetPIDDrive(kp,ki,kd);
}

// Set all PID values for each module.
void Drivetrain::SetTurnPID(double kp, double ki, double kd){
    module_frontLeft.SetPIDTurning(kp, ki, kd);
    module_frontRight.SetPIDTurning(kp, ki, kd);
    module_backLeft.SetPIDTurning(kp, ki, kd);
    module_backRight.SetPIDTurning(kp, ki, kd);
}

// Drive with the swerve drive.
void Drivetrain::Drive(double xValue, double yValue, double rotation){

    // Get rid of deadzone controller
    if (rotation < 0.1 && rotation > 0 || rotation > -0.1 && rotation < 0 ){rotation = 0;}
    if (xValue < 0.1 && xValue > 0 || xValue > -0.1 && xValue < 0 ){xValue = 0;}
    if (yValue < 0.1 && yValue > 0 || yValue > -0.1 && yValue < 0 ){yValue = 0;}

    // function so when the stick is zero the wheels keep the same angle.
    if (xValue == 0 && yValue == 0 && rotation == 0){xValue = prevX; yValue = prevY; rotation = prevRotation; Move = 0;}
    else
    {
        prevX = xValue;
        prevY = yValue;
        prevRotation = rotation;
        Move = 1;
    }


    // math, calculate the angele and speed of each module
    MathSwerve(xValue, yValue, rotation);
    AngleCorrection();

    //visualisation rotation speed
    frc::SmartDashboard::PutNumber("Direction_FL", Directionfl + AngleCorrectionFl);
    frc::SmartDashboard::PutNumber("Direction_FR", Directionfr + AngleCorrectionFr);
    frc::SmartDashboard::PutNumber("Direction_BL", Directionbl + AngleCorrectionBl);
    frc::SmartDashboard::PutNumber("Direction_BR", Directionbr + AngleCorrectionBr);
    cout << Speedfl << ' '  << Directionfl << ' '  << Speedfr << ' '  << Directionfr  << ' '  << Speedbl << ' '  << Directionbl << ' '  << Speedbr << ' '  << Directionbr << "\n";
   
    // Set the desired state of the position and speed of each module.
    module_frontLeft.SetDesiredState(Speedfl * Move, Directionfl + AngleCorrectionFl);
    module_frontRight.SetDesiredState(Speedfr * Move, Directionfr + AngleCorrectionFr);
    module_backLeft.SetDesiredState(Speedbl * Move, Directionbl + AngleCorrectionBl);
    module_backRight.SetDesiredState(Speedbr * Move, Directionbr + AngleCorrectionBr);
}

// This function makes the rotation of the stick continous. 
void Drivetrain::AngleCorrection(){
// clean this code up
int idk1 = -180;
int idk2 = 0;
    cout << PrevDirectionfl << "\n";
// corection for module 1 ------------------------------
        if(PrevDirectionfl > idk2 && Directionfl < 0){
            AngleCorrectionFl = AngleCorrectionFl + 360 ;
        }
        else if (PrevDirectionfl < idk1 && Directionfl > 0){
            AngleCorrectionFl = AngleCorrectionFl - 360 ;
        }
        PrevDirectionfl = Directionfl;
// corection for module 2 ------------------------------
        if(PrevDirectionfr > idk2 && Directionfr < 0){
            AngleCorrectionFr = AngleCorrectionFr + 360 ;
        }
        else if (PrevDirectionfr < idk1 && Directionfr > 0){
            AngleCorrectionFr = AngleCorrectionFr - 360 ;
        }
        PrevDirectionfr = Directionfr;
// corection for module 3 ------------------------------
        if(PrevDirectionbl > idk2 && Directionbl < 0){
            AngleCorrectionBl = AngleCorrectionBl + 360 ;
        }
        else if (PrevDirectionbl < idk1 && Directionbl > 0){
            AngleCorrectionBl = AngleCorrectionBl - 360 ;
        }
        PrevDirectionbl = Directionbl;
// corection for module 4 ------------------------------
        if(PrevDirectionbr > idk2 && Directionbr < 0){
            AngleCorrectionBr = AngleCorrectionBr + 360 ;
        }
        else if (PrevDirectionbr < idk1 && Directionbr > 0){
            AngleCorrectionBr = AngleCorrectionBr - 360 ;
        }
        PrevDirectionbr = Directionbr;
}

// Set the robot to a determent position on the field 
void Drivetrain::SetDesiredPositionRobot (double Distance, double Angle){
    module_frontLeft.SetDesiredPosition(Distance, Angle);
    module_frontRight.SetDesiredPosition(Distance, Angle);
    module_backLeft.SetDesiredPosition(Distance, Angle);
    module_backRight.SetDesiredPosition(Distance, Angle);
}

void Drivetrain::SetDesiredStateRobot(double speed, double angle){
    module_frontLeft.SetDesiredState(speed, angle);
    module_frontRight.SetDesiredState(speed, angle);
    module_backLeft.SetDesiredState(speed, angle);
    module_backRight.SetDesiredState(speed, angle);
}

double Drivetrain::GetPositionDrive(){
    return module_frontLeft.GetModulePositionDrive();
}

double Drivetrain::GetVelocityDrive(){
    return module_frontLeft.GetModuleVelocityDrive();
}

double Drivetrain::GetPositionAngle(){
    return module_frontLeft.GetModulePositionAngle();
}