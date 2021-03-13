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

void Drivetrain::MathSwerve(double xValue, double yValue, double rot){
    if (yValue < 0){
        // calc the rot speed
        double rotVel = rot * MaxRad;

        // vector calc per module  (x, y) 
        double VectorFL[2] = {rotVel * DistanceMod[0] * cos(RotVecInRad) + xValue * MaxSpeed, rotVel * DistanceMod[0] * sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorFR[2] = {rotVel * DistanceMod[1] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[1] * -sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorBL[2] = {-rotVel * DistanceMod[2] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[2] * -sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorBR[2] = {-rotVel * DistanceMod[3] * cos(RotVecInRad) + xValue * MaxSpeed, rotVel * DistanceMod[3] * sin(RotVecInRad) + yValue * MaxSpeed};

        // calc the speed and oriantation of the mod  (speed, direction)
        double SwerveModValRot [4][2] = {{sqrt(pow(VectorFL[0], 2)+ pow(VectorFL[1], 2)), atan(VectorFL[0]/VectorFL[1])},
                                            {sqrt(pow(VectorFR[0], 2)+ pow(VectorFR[1], 2)), atan(VectorFR[0]/VectorFR[1])},
                                            {sqrt(pow(VectorBL[0], 2)+ pow(VectorBL[1], 2)), atan(VectorBL[0]/VectorBL[1])},
                                            {sqrt(pow(VectorBR[0], 2)+ pow(VectorBR[1], 2)), atan(VectorBR[0]/VectorBR[1])}};

            Speedfl = SwerveModValRot[0][0]*(180/pi);
            Directionfl = SwerveModValRot[0][1]*(180/pi)+180;
            Speedfr = SwerveModValRot[1][0]*(180/pi);
            Directionfr = SwerveModValRot[1][1]*(180/pi)+180;
            Speedbl = SwerveModValRot[2][0]*(180/pi);
            Directionbl = SwerveModValRot[2][1]*(180/pi)+180;
            Speedbr = SwerveModValRot[3][0]*(180/pi);
            Directionbr = SwerveModValRot[3][1]*(180/pi)+180;

        
    }
    else if (rot < 0){
        // calc the rot speed
        double rotVel = rot * MaxRad;

        // vector calc per module  (x, y) 
        double VectorFL[2] = {rotVel * DistanceMod[0] * cos(RotVecInRad) + xValue * MaxSpeed, rotVel * DistanceMod[0] * sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorFR[2] = {rotVel * DistanceMod[1] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[1] * -sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorBL[2] = {-rotVel * DistanceMod[2] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[2] * -sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorBR[2] = {-rotVel * DistanceMod[3] * cos(RotVecInRad) + xValue * MaxSpeed, rotVel * DistanceMod[3] * sin(RotVecInRad) + yValue * MaxSpeed};

        // calc the speed and oriantation of the mod  (speed, direction)
        double SwerveModValRot [4][2] = {{sqrt(pow(VectorFL[0], 2)+ pow(VectorFL[1], 2)), atan(VectorFL[0]/VectorFL[1])},
                                            {sqrt(pow(VectorFR[0], 2)+ pow(VectorFR[1], 2)), atan(VectorFR[0]/VectorFR[1])},
                                            {sqrt(pow(VectorBL[0], 2)+ pow(VectorBL[1], 2)), atan(VectorBL[0]/VectorBL[1])},
                                            {sqrt(pow(VectorBR[0], 2)+ pow(VectorBR[1], 2)), atan(VectorBR[0]/VectorBR[1])}};

            Speedfl = SwerveModValRot[0][0]*(180/pi);
            Directionfl = SwerveModValRot[0][1]*(180/pi)+180;
            Speedfr = SwerveModValRot[1][0]*(180/pi);
            Directionfr = SwerveModValRot[1][1]*(180/pi)+180;
            Speedbl = SwerveModValRot[2][0]*(180/pi);
            Directionbl = SwerveModValRot[2][1]*(180/pi)+180;
            Speedbr = SwerveModValRot[3][0]*(180/pi);
            Directionbr = SwerveModValRot[3][1]*(180/pi)+180;
    }

    else{
        // calc the rot speed
        double rotVel = rot * MaxRad;

        // vector calc per module  (x, y) 
        double VectorFL[2] = {rotVel * DistanceMod[0] * cos(RotVecInRad) + xValue * MaxSpeed, rotVel * DistanceMod[0] * sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorFR[2] = {rotVel * DistanceMod[1] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[1] * -sin(RotVecInRad) + yValue * MaxSpeed};
        double VectorBL[2] = {-rotVel * DistanceMod[2] * cos(RotVecInRad) + xValue * MaxSpeed, -rotVel * DistanceMod[2] * -sin(RotVecInRad) + yValue * MaxSpeed};
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
    // Get rid of deadzone controller
    if (rotation < 0.1 && rotation > 0 || rotation > -0.1 && rotation < 0 ){rotation = 0;}
    if (xValue < 0.1 && xValue > 0 || xValue > -0.1 && xValue < 0 ){xValue = 0;}
    if (yValue < 0.1 && yValue > 0 || yValue > -0.1 && yValue < 0 ){yValue = 0;}

    // math
    MathSwerve(xValue, yValue, rotation);
    // AngleCorrection();

    cout << Speedfl << ' '  << Directionfl << ' '  << Speedfr << ' '  << Directionfr  << ' '  << Speedbl << ' '  << Directionbl << ' '  << Speedbr << ' '  << Directionbr << "\n"; 
    module_frontLeft.SetDesiredState(Speedfl, Directionfl + AngleCorrectionFl);
     cout << AngleCorrectionFl << "\n";
    module_frontRight.SetDesiredState(Speedfr, Directionfr);
    module_backLeft.SetDesiredState(Speedbl, Directionbl);
    module_backRight.SetDesiredState(Speedbr, Directionbr);
}

void Drivetrain::AngleCorrection(){
// clean this code up
    cout << PrevDirectionfl << "\n";

        if(PrevDirectionfl > 180 && Directionfl < 0){
            AngleCorrectionFl = AngleCorrectionFl + 360 ;
        }
        else if (PrevDirectionfl < 0 && Directionfl > 180){
            AngleCorrectionFl = AngleCorrectionFl - 360 ;
        }
        PrevDirectionfl = Directionfl;
//-------------------------------------------------------
        if(PrevDirectionfr > 240 && Directionfr < -70){
            AngleCorrectionFr = AngleCorrectionFr + 360 ;
        }
        else if (PrevDirectionfr < -60 && Directionfr > 250){
            AngleCorrectionFr = AngleCorrectionFr - 360 ;
        }
        PrevDirectionfl = Directionfl;
//------------------------------------------------------
        if(PrevDirectionbl > 240 && Directionbl < -70){
            AngleCorrectionBl = AngleCorrectionBl + 360 ;
        }
        else if (PrevDirectionbl < -60 && Directionbl > 250){
            AngleCorrectionFl = AngleCorrectionFl - 360 ;
        }
        PrevDirectionbl = Directionbl;
//-----------------------------------------------------
        if(PrevDirectionbr > 240 && Directionbr < -70){
            AngleCorrectionBr = AngleCorrectionBr + 360 ;
        }
        else if (PrevDirectionbr < -60 && Directionbr > 250){
            AngleCorrectionBr = AngleCorrectionBr - 360 ;
        }
        PrevDirectionbr = Directionbr;

}