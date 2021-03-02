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


Pixy2* pixy = new Pixy2(Pixy2::LinkType::SPI);
Pixy2CCC* ccc = new Pixy2CCC(pixy);
Pixy2Video* video = new Pixy2Video(pixy);

//Connected Components predefined details
bool wait = true;
uint8_t sigmap = ccc->CCC_SIG_ALL;
uint8_t maxBlocks = 0xff;

//General logic
void Pixy2_Init();
Block *trackBlock(uint8_t index);
int acquireBlock();

//intake ball logic
void runPixy2Intake();
