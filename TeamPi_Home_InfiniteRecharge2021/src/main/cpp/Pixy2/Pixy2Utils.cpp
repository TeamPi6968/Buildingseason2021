#include "Pixy2/Pixy2Utils.h"

/**
 * Adds byte to checksum
 * 
 * @param b Byte to be added
 */
void Checksum::updateChecksum(int b){
    cs += b;
}

/**
 * Returns calculated checksum
 * 
 * @return Calculated checksum
 */
int Checksum::getChecksum() {
    return cs;
}

/**
 * 
 * Resets cs to 0
 * 
 */
void Checksum::reset() {
    cs = 0;
}


//-------------------------- Version class
Version::Version(uint8_t* version) {
    hardware = ((int) (version[1] & 0xff) << 8) | (int) (version[0] & 0xff);
    firmwareMajor = version[2];
    firmwareMinor = version[3];
    firmwareBuild = ((int) (version[5] & 0xff) << 8) | (int) (version[4] & 0xff);
    for (int i = 0; i < 10; i++) {
        firmwareType[i] = (char) (version[i + 6] & 0xFF);
    }
}

Version::~Version()
{
}



//------------------------ Block class
Block::Block(int signature, int x, int y, int width, int height, int angle, int index, int age) {
    this->signature = signature;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->angle = angle;
    this->index = index;
    this->age = age;
}

std::string Block::blockInfo(int CCC_MAX_SIGNATURE) {
    int i, j;
    char *sig = new char[6];
    int d;
    bool flag;
    std::string out = "";
    if (signature > CCC_MAX_SIGNATURE) {
        // Color code! (CC)
        // Convert signature number to an octal string
        for (i = 12, j = 0, flag = false; i >= 0; i -= 3) {
            d = (signature >> i) & 0x07;
            if (d > 0 && !flag)
                flag = true;
            if (flag)
                sig[j++] = (char)d + '0';
        }
        sig[j] = '\0';
        std::string temp; temp.append(sig);
        out = "CC block sig: " + temp + " (" + (char)signature + " decimal) x: " + (char)x + " y: " + (char)y
                + " width: " + (char)width + " height: " + (char)height + " angle: " + (char)angle + " index: " + (char)index + " age: "
                + (char)age;

    } 
    else{ // Regular block. Note, angle is always zero, so no need to print
            std::string temp = "";
            out = "sig: "+ temp + "" + (char)signature + " x: " + (char)x + " y: " + (char)y + " width: " + (char)width + " height: " + (char)height
                + " index: " + (char)index + " age: " + (char)age;
        }
    return out;
}

int Block::getSignature(){
    return signature;
}
int Block::getX(){
    return x;
}
int Block::getY(){
    return y;
}
int Block::getWidth(){
    return width;
}
int Block::getHeight(){
    return height;
}
int Block::getAngle(){
    return angle;
}
int Block::getIndex(){
    return index;
}
int Block::getAge(){
    return age;
}


Block::~Block()
{
}


