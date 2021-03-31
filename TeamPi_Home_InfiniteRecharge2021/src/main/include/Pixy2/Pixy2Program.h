 /* * Made for Robotics TeamPi 2021 Build Season
 * Author: Caleb Kyei
 * Date: 02/03/2021 17:00
 * 
 * Remarks: This is the top level program/logic for controlling the pixy 
 * 
 * */

#pragma once
#include "Pixy2CCC.h"
#include "Pixy2Video.h"
#include <iostream>

class Pixy2Program
{
private:
    Pixy2* pixy;
    Pixy2CCC* ccc;
    Pixy2Video* video;
    frc::Timer pixyTimer;

//Connected Components predefined details
// bool wait = true;
// uint8_t sigmap = ccc->CCC_SIG_ALL;
// uint8_t maxBlocks = 0xff;

    //General logic
    void Pixy2_Init();
    Block *trackBlock(uint8_t index);
    int acquireBlock();

public:
    Pixy2Program();
    ~Pixy2Program();

    void runPixy2Intake();
};








//General logic
void Pixy2_Init();
Block *trackBlock(uint8_t index);
int acquireBlock();

//intake ball logic
void runPixy2Intake();
