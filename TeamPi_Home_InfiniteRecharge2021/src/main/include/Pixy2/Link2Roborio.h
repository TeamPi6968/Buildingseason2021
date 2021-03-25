
 /* * Made for Robotics TeamPi 2021 Build Season
 * Author: Caleb Kyei
 * Date: 27/02/2021 23:00
 * 
 * Remarks: This is a template Link-2-Roborio 
 *          for connecting pixy to the roborio
 * 
 * */



#pragma once

#include <stdint.h>
#include "Pixy2Utils.h"



class Link2Roborio
{
private:
    /* data */
public:

    /**
     * Opens link
     *
     * @param arg Link argument
     * 
     * @return Returns state
     */
    virtual int open(int arg) = 0;


    /**
     * Receives and reads specified length of bytes over link
     *
     * @param buffer Byte buffer to return value
     * @param length Length of value to read
     * @param cs     Checksum
     * 
     * @return Length of value read
     */
    virtual int receive(uint8_t *buffer, int length, Checksum *cs) = 0;


    /**
     * Receives and reads specified length of bytes over link
     *
     * @param buffer Byte buffer to return value
     * @param length Length of value to read
     * 
     * @return Length of value read
     */    
    virtual int receive(uint8_t *buffer, int length) = 0;



    /**
     * Writes and sends buffer over link
     *
     * @param buffer Byte buffer to send
     * @param length Length of value to send
     * 
     * @return Length of value sent
     */
    virtual int send(uint8_t *buffer, int length) = 0;


};


