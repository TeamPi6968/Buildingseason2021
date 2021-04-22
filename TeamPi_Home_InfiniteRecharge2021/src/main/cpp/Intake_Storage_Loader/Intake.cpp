

#include "Intake_Storage_Loader/Intake.h"
#include <iostream> 

using namespace std;

/*
button controller
bttnNo. - bttnType
1 - A
2 - B
3 - X
4 - Y
5 - LB
6 - RB
7 - 'BACK'
8 - 'START'
*/


/*
Intake::Intake(){
Comp.SetClosedLoopControl(true);

}
*/

void Intake::IntakeSolonoids (bool buttonPressed, int cellAmount){
  if (buttonPressed){
        if  (StatusIntake == 0 && cellAmount <4) {
        //change status to go out
        StatusIntake = 1;
        //cylinder is out
        SolonoidLeft.Set(frc::DoubleSolenoid::Value::kReverse);
        //spin spark motorscontrollers for intake 
        SparkMaxIntake.Set(IntakeMotorSpeed);
        
        cout<< "going in" << endl; 
        }


    else if (StatusIntake == 1){
        //change status to go in
        StatusIntake = 0;
        //cylinder is in
        SolonoidLeft.Set(frc::DoubleSolenoid::Value::kForward);
        //stop motor
        SparkMaxIntake.Set(0);
        cout<< "going out" << endl;

        }
    }
    frc::SmartDashboard::PutNumber("Status intake", StatusIntake);
}


 



