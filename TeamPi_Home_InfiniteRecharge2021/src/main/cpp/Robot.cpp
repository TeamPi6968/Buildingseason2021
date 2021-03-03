// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

  Pixy2* pixy = new Pixy2(Pixy2::LinkType::SPI);
  Pixy2CCC* ccc = new Pixy2CCC(pixy);
  //Pixy2Video* video = new Pixy2Video(pixy);

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {

  //Connected Components predefined details
  // bool wait = true;
  // uint8_t sigmap = ccc->CCC_SIG_ALL;
  // uint8_t maxBlocks = 0xff;

}

//Initialise Pixy2
void Pixy2_Init(){
    pixy->init();
    pixy->changeProg("color_connected_components");
}

// Find the block with the given index.  In other words, find the same object in the current
// frame -- not the biggest object, but he object we've locked onto in acquireBlock()
// If it's not in the current frame, return NULL
Block *trackBlock(uint8_t index)
{
    uint8_t i;

    for (i=0; i< ccc->numBlocks; i++)
    {
    if (index == ccc->getBlockCache()[i].data()->getIndex())
    return ccc->getBlockCache()[i].data();
    }

    return NULL;
}

// Take the biggest block (blocks[0]) that's been around for at least 15 frames (1/2 second)
// and return its index, otherwise return -1
int acquireBlock()
{
  if (ccc->numBlocks && ccc->getBlockCache()[0].data()->getAge()>15)
    return ccc->getBlockCache()[0].data()->getIndex();

  return -1;
}

//Intake Logic
void runPixy2Intake(){

    static int index = -1;

    //Each time it runs, block is NULL until we say something is found,
    // then it changes but defaults to NULL.
    Block *block = NULL;
    
    ccc->getBlocks();

    if (index==-1) // search....
    {
        //Serial.println("Searching for block...");
        index = acquireBlock();

    //     //if something is found
    //     if (index>=0){
    //       Serial.print("Found block! with index: ");
    //       Serial.println(index);
    //     }
    }


    // If we've found a block, find it, track it
    if (index>=0)
        block = trackBlock(index);
    
    //if we find something, track... But do this while tracking   
    if (block)
    {
        if (block->getY()>180)
        {
            //Serial.println("Almost at edge.");
        }
        index = -1;
        
    }
    

}
void Robot::AutonomousPeriodic() {
  runPixy2Intake();
}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
