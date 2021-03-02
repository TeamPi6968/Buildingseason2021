#include "PixyProgram.h"

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