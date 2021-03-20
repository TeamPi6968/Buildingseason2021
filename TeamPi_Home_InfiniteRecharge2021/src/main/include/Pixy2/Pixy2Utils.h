 /* * Made for Robotics TeamPi 2021 Build Season
 * Author: Caleb Kyei
 * Date: 28/02/2021 18:00
 * 
 * Remarks: This includes all the utility classes and code snippets 
 *          for connecting pixy to the roborio
 * 
 * */


#pragma once
#include <stdint.h>
#include <string>

class Checksum
{
private:
    int cs = 0;
public:
    void updateChecksum(int b);
    int getChecksum();
    void reset();
};

class Version
{
protected:
    int hardware = 0;
    int firmwareMajor = 0;
    int firmwareMinor = 0;
    int firmwareBuild = 0;
    char *firmwareType = new char[10];

private:

    ~Version();
    /* data */
public:
    Version(uint8_t* version);

};

class Block
{
private:
    int signature, x, y, width, height, angle, index, age;

public:
    Block(int signature, int x, int y, int width, int height, int angle, int index, int age);
    std::string blockInfo(int CCC_MAX_SIGNATURE);
    int getSignature();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    int getAngle();
    int getIndex();
    int getAge();
    ~Block();

};






