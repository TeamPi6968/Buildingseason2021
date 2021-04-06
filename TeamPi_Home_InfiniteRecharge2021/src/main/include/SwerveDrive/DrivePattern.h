#pragma once

#include "Drivetrain.h"
#include "vector"
#include <iostream>
#include <fstream>
#include <frc/Joystick.h>
#include <frc/Timer.h>
// #include "Workbook.h"
// #include "Worksheet.h"
// #include "Cell.h"

// using namspeace 
using namespace frc;

class DrivePattern{
    public:
        DrivePattern();
        void Bounce();
        void RecBounce();
        void ClearFile();
        void RecordDrivePattern(string DriveName, string AngleName);
        void StoreDrivePattern(string DriveName, string AngleName);

    private:
        Drivetrain Swerve;
        Joystick m_stick{0};

        ofstream *myfile;
        ofstream *myfile2;

        // Declare PID values
        const double kP_Drive = 1.5;
        const double kI_Drive = 0.0001;
        const double kD_Drive = 0.1;

        const double kP_Turning = 4;
        const double kI_Turning = 0.0015;
        // test
        // const double kP_Turning = 6;
        // const double kI_Turning = 0.01;
        const double kD_Turning = 0.1;

        Timer *time = new Timer();
        
        bool StoreData = false;
        bool DataCollected = false;
        bool Drive = false;
        bool Zero = false;
        bool Done = false;

        std::vector<double> AngleArr = {0};
        std::vector<double> DriveArr = {0};

        int i = 0;

        int ButtonA = 1;
        int ButtonB = 2;
        int ButtonX = 3;
        int ButtonY = 4;
        int ButtonLB = 5;
        int ButtonRB = 6;
        int ButtonBACK = 7;
        int ButtonSTART = 8;    

};