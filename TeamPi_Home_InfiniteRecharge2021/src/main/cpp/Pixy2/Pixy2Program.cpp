#include "Pixy2/Pixy2Program.h"

Pixy2Program::Pixy2Program(Pixy2 *pixy, Pixy2CCC *ccc, Pixy2Video* video)
{
    this->pixy = pixy;
    this->ccc = ccc;
    this->video = video;
    this->pixy->init();
    this->pixy->changeProg("color_connected_components");
    pixyTimer.Start();
}

Pixy2Program::~Pixy2Program()
{
}
//Initialise Pixy2
void Pixy2Program::Pixy2_Init(){

    pixyTimer.Start();
}

// Find the block with the given index.  In other words, find the same object in the current
// frame -- not the biggest object, but he object we've locked onto in acquireBlock()
// If it's not in the current frame, return NULL
Block* Pixy2Program::trackBlock(uint8_t index)
{
    pixyTimer.Reset();
    uint8_t i;

    for (i=0; i< this->ccc->numBlocks; i++)
    {
    if (index == this->ccc->getBlockCache()[i].data()->getIndex())
    return this->ccc->getBlockCache()[i].data();
        if (pixyTimer.HasPeriodPassed(0.01))
        {
            return NULL;
        }
    
    }

    return NULL;
}

// Take the biggest block (blocks[0]) that's been around for at least 15 frames (1/2 second)
// and return its index, otherwise return -1
int Pixy2Program::acquireBlock()
{
  if (this->ccc->numBlocks && this->ccc->getBlockCache()[0].data()->getAge()>15)
    return this->ccc->getBlockCache()[0].data()->getIndex();

  return -1;
}

//Intake Logic
void Pixy2Program::runPixy2Intake(){

    static int index = -1;

    //Each time it runs, block is NULL until we say something is found,
    //then it changes but defaults to NULL.
    Block *block = NULL;
    
    this->ccc->getBlocks();

    if (index==-1) // search....
    {
        std::cout<< "Searching for block...\n";
        index = acquireBlock();

         //if something is found
        if (index>=0){
           std::cout<<"Found block! with index: \n";
           std::cout<< (index);
        }
    }


    // If we've found a block, find it, track it
    if (index>=0)
        block = trackBlock(index); 
    
    //if we find something, track... But do this while tracking   
    if (block)
    {
        if (block->getY()>180)
        {
            std::cout << "Almost at edge.\n";
        }
        index = -1;
    }
}