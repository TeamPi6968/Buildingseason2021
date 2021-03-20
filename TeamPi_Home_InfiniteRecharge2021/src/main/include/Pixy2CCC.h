 /* * Made for Robotics TeamPi 2021 Build Season
 * Author: Caleb Kyei
 * Date: 29/02/2021 00:00
 * 
 * Remarks: This is the colour connected component library 
 *          for connecting pixy to the roborio
 * 
 * */

#pragma once

#include "Pixy2.h"
#include <vector>

class Pixy2CCC
{
private:
Pixy2 *pixy;
//Block *blocks;
std::vector<Block> *blocks;
    /* data */
public:

    const int CCC_MAX_SIGNATURE = 7;

    const uint8_t CCC_RESPONSE_BLOCKS = 0x21;
    const uint8_t CCC_REQUEST_BLOCKS = 0x20;

    // Defines for sigmap:
    // You can bitwise "or" these together to make a custom sigmap.
    // For example if you're only interested in receiving blocks
    // with signatures 1 and 5, you could use a sigmap of
    // PIXY_SIG1 | PIXY_SIG5
    const uint8_t CCC_SIG1 = 0x01;
    const uint8_t CCC_SIG2 = 0x02;
    const uint8_t CCC_SIG3 = 0x04;
    const uint8_t CCC_SIG4 = 0x08;
    const uint8_t CCC_SIG5 = 0x10;
    const uint8_t CCC_SIG6 = 0x20;
    const uint8_t CCC_SIG7 = 0x40;
    const uint8_t CCC_COLOR_CODES = 0x80;

    const uint8_t CCC_SIG_ALL = 0xff; // All bits or'ed together

    int numBlocks;
    std::vector<Block> *getBlockCache();

    int getBlocks();
    int getBlocks(bool wait);
    int getBlocks(bool wait, int sigmap);
    int getBlocks(bool wait, int sigmap, int maxBlocks);

    Pixy2CCC(Pixy2 *pixy);
    ~Pixy2CCC();
};



