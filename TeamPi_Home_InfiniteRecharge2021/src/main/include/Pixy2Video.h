 /* * Made for Robotics TeamPi 2021 Build Season
 * Author: Caleb Kyei
 * Date: 02/03/2021 18:00
 * 
 * Remarks: This is the raw video library 
 *          for connecting pixy to the roborio
 * 
 * */

#pragma once
#include "Pixy2.h"


class RGB 
{
private:
int r, g, b;

public:
    RGB(int r, int g, int b);
    uint8_t getR();
    uint8_t getG();
    uint8_t getB();

    void setR(int r);
    void setG(int g);
    void setB(int b);

    void setRGB(int rgb);
    void setRGB(int r, int g, int b);

};



class Pixy2Video
{
private:
Pixy2 *pixy;


public:

	uint8_t VIDEO_REQUEST_GET_RGB = 0x70;


    Pixy2Video(Pixy2 *pixy);
    ~Pixy2Video();

    int getRGB(int x, int y, RGB* rgb);
    int getRGB(int x, int y, RGB* rgb, bool saturate);

};
