#pragma once

#include "Drivetrain.h"
#include "vector"
#include <iostream>
#include <fstream>
#include <frc/Joystick.h>
#include <frc/Timer.h>

using namespace frc;

class DrivePattern{
    public:
        DrivePattern();
        void Bounce();
        void RecBounce();
        void RecordDrivePattern(string DriveName, string AngleName);
        void StoreDrivePattern(string DriveName, string AngleName);

    private:
        Drivetrain Swerve;
        Joystick m_stick{0};

        Timer *time = new Timer();
        
        bool StoreData = false;
        bool DataCollected = false;
        bool Drive = false;
        bool Zero = false;

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