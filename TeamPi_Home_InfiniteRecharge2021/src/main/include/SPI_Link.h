/* * 
 * 
 * Made for Robotics TeamPi 2021 Build Season
 * Author: Caleb Kyei
 * Date: 27/02/2021 20:00
 * 
 * Remarks: This is the low level SPI ported Library 
 * 
 * 
 * 
 * */


#pragma once

#include <frc/SPI.h>
#include "Link2Roborio.h"

using namespace frc;

class SPI_Link : virtual public Link2Roborio
{
private:
    static const int PIXY_SPI_CLOCKRATE = 2000000;

    SPI *spi;
    SPI::Port *port;

public:
    
        /**
     * Opens link
     *
     * @param arg Link argument
     * 
     * @return Returns state
     */
    virtual int open(int arg) override;


    /**
     * Receives and reads specified length of bytes over link
     *
     * @param buffer Byte buffer to return value
     * @param length Length of value to read
     * @param cs     Checksum
     * 
     * @return Length of value read
     */
    virtual int receive(uint8_t *buffer, int length, Checksum *cs ) override;


    /**
     * Receives and reads specified length of bytes over link
     *
     * @param buffer Byte buffer to return value
     * @param length Length of value to read
     * 
     * @return Length of value read
     */    
    virtual int receive(uint8_t *buffer, int length) override;



    /**
     * Writes and sends buffer over link
     *
     * @param buffer Byte buffer to send
     * @param length Length of value to send
     * 
     * @return Length of value sent
     */
    virtual int send(uint8_t *buffer, int length) override;




    SPI_Link(/* args */);
    ~SPI_Link();
};


