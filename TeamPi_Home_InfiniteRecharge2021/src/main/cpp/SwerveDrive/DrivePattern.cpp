#include "SwerveDrive/DrivePattern.h"


DrivePattern::DrivePattern(){
  time->Start();
}


void DrivePattern::Bounce(){

 if(DataCollected == false){
  std::vector<double> AngleArr = {0};
  ifstream inputFile("./home/lvuser/BounceAngle.txt");        // Input file stream object

  // Check if exists and then open the file.
  if (inputFile.good()) {
    // Push items into a vector
    double current_number = 0;
    while (inputFile >> current_number){
      AngleArr.push_back(current_number);
    }
    // Close the file.
    inputFile.close();
        for (int i = 0; i < AngleArr.size(); i++) {
        std::cout << AngleArr.at(i) << ' ';
    }
    cout << "-------" << AngleArr [5] << "\n";
    }
    	else cout << "Error in opening angle file" << "\n";


  std::vector<double> DriveArr = {0};
  ifstream inputFile2("./home/lvuser/BounceDrive.txt");        // Input file stream object

  // Check if exists and then open the file.
  if (inputFile2.good()) {
    // Push items into a vector
    double current_number = 0;
    while (inputFile2 >> current_number){
      DriveArr.push_back(current_number);
    }
    // Close the file.
    inputFile2.close();
    DataCollected = true;
    cout << "--------" << DriveArr [5] << "\n";
    }
    	else cout << "Error in opening angle file" << "\n";
 
  }
 else if(DataCollected == true && Zero == false) {
   Swerve.ZeroDrivetrain();
   Zero = true;
 }

 else if(Zero == true) {
  // Drive = true;
  int size = AngleArr.size();
  Swerve.SetDesiredPositionRobot(DriveArr[i],AngleArr[i]);
  // if (AngleArr[i] - AngleArr[i] * 0.01 < Swerve.GetPositionAngle() && AngleArr[i] + AngleArr[i] * 0.01 > Swerve.GetPositionAngle() )
  //     // && DriveArr[i] - DriveArr[i] * 0.01 < Swerve.GetPositionDrive() && DriveArr[i] + DriveArr[i] * 0.01 > Swerve.GetPositionDrive())
  //     {
  if (AngleArr[i] - (AngleArr[i] * 0.05) < Swerve.GetPositionAngle() && AngleArr[i] + (AngleArr[i] * 0.05) > Swerve.GetPositionAngle()){
    i = i + 1;
    cout << "i + 1" << "\n";
  }
  else if (size < i){
    cout << "pattern done" << "\n";
  }

  double currentPos = Swerve.GetPositionAngle();

  cout << "Pos = " << currentPos << "   " << AngleArr[i] <<  "\n";
 }
}


void DrivePattern::RecBounce(){
  if (m_stick.GetRawButtonPressed(ButtonBACK) || StoreData == true){
    cout << "rec";
    StoreData = true;
    Drive = false;
    RecordDrivePattern("BounceDrive.txt", "BounceAngle.txt");
  }
}

// Rec data
void DrivePattern::RecordDrivePattern(string DriveName, string AngleName){
  Swerve.Drive(m_stick.GetX(), -m_stick.GetY(), m_stick.GetRawAxis(4));

  if (time->HasPeriodPassed(0.1)){

    AngleArr.push_back(Swerve.GetPositionAngle());
    DriveArr.push_back(Swerve.GetPositionDrive());
    cout << "stored data into array" << "\n";
    time->Reset();
  }
  if (m_stick.GetRawButtonPressed(ButtonSTART)){
    StoreDrivePattern(DriveName, AngleName);
  }
}

// Store data
void DrivePattern::StoreDrivePattern(string DriveName, string AngleName){
  int size = AngleArr.size();
  
  ofstream myfile ("./home/lvuser/BounceAngle.txt");
  if (myfile.is_open())
  {
    for(int count = 0; count < size; count ++){
        myfile << AngleArr[count] << " " ;
    }
    StoreData = false;
    DataCollected = false;
    myfile.close();
  }
  else cout << "Unable to open file" << "\n";

  size = DriveArr.size();
  ofstream myfile2 ("./home/lvuser/BounceDrive.txt");
  if (myfile2.is_open())
  {
    for(int count = 0; count < size; count ++){
        myfile2 << DriveArr[count] << " " ;
    }
    StoreData = false;
    DataCollected = false;
    myfile2.close();
  }
  else cout << "Unable to open file" << "\n";
}

