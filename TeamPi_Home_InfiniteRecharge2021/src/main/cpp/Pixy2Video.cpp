#include "Pixy2Video.h"


/**
 * Constructs RGB container
 * 
 * @param r R value
 * @param g G value
 * @param b B value
 */
RGB::RGB(int r, int g, int b) {
    // Limits rgb values between the min and max
    this->r = (r >= 255 ? 255 : (r <= 0 ? 0 : r));
    this->g = (g >= 255 ? 255 : (g <= 0 ? 0 : g));
    this->b = (b >= 255 ? 255 : (b <= 0 ? 0 : b));
}

/**
 * @return R value
 */
uint8_t RGB::getR() {
    return this->r;
}

/**
 * @return G value
 */
uint8_t RGB::getG() {
    return this->g;
}

/**
 * @return B value
 */
uint8_t RGB::getB() {
    return this->b;
}

/**
 * Sets R value between 0-255
 * 
 * @param r R value
 */
void RGB::setR(int r) {
    // Limits r value between the min and max
    this->r = (r >= 255 ? 255 : (r <= 0 ? 0 : r));
}

/**
 * Sets G value between 0-255
 * 
 * @param g G value
 */
void RGB::setG(int g) {
    // Limits g value between the min and max
    this->g = (g >= 255 ? 255 : (g <= 0 ? 0 : g));
}

/**
 * Sets B value between 0-255
 * 
 * @param b B value
 */
void RGB::setB(int b) {
    // Limits b value between the min and max
    this->b = (b >= 255 ? 255 : (b <= 0 ? 0 : b));
}

/**
 * Sets RGB value
 * 
 * @param rgb RGB value
 */
void RGB::setRGB(int rgb) {
    this->r = (rgb >> 16) & 0xff;
    this->g = (rgb >> 8) & 0xff;
    this->b = rgb & 0xff;
}

/**
 * Sets RGB values between 0-255
 * 
 * @param r R value
 * @param g G value
 * @param b B value
 */
void RGB::setRGB(int r, int g, int b) {
    // Limits r value between the min and max
    this->r = (r >= 255 ? 255 : (r <= 0 ? 0 : r));
    this->g = (g >= 255 ? 255 : (g <= 0 ? 0 : g));
    this->b = (b >= 255 ? 255 : (b <= 0 ? 0 : b));
}




Pixy2Video::Pixy2Video(Pixy2 *pixy)
{
    this->pixy = pixy;
}

Pixy2Video::~Pixy2Video()
{
}

/**
 * Gets average RGB value at 5x5 area around specified coordinates in the image
 * 
 * <p>Defaults to saturating response color</p>
 * 
 * @param x        X value
 * @param y        Y value
 * @param rgb      RGB container to return values in
 * 
 * @return Pixy2 error code
 */
int Pixy2Video::getRGB(int x, int y, RGB* rgb) {
    return getRGB(x, y, rgb, true);
}

/**
 * Gets average RGB value at 5x5 area around specified coordinates in the image
 * 
 * @param x        X value
 * @param y        Y value
 * @param rgb      RGB container to return values in
 * @param saturate Whether or not to scale all RGB values to maximize the
 *                 greatest value at 255
 * 
 * @return Pixy2 error code
 */
int Pixy2Video::getRGB(int x, int y, RGB* rgb, bool saturate) {
    long start = frc::GetTime();

    while (true) {
        pixy->bufferPayload[0] = (x & 0xff);
        pixy->bufferPayload[1] = ((x >> 8) & 0xff);
        pixy->bufferPayload[2] = (y & 0xff);
        pixy->bufferPayload[3] = ((y >> 8) & 0xff);
        pixy->bufferPayload[4] = (saturate == true ? 1 : 0);
        pixy->length = 5;
        pixy->type = VIDEO_REQUEST_GET_RGB;
        pixy->sendPacket();
        if (pixy->receivePacket() == 0) {
            if (pixy->type == PIXY_TYPE_RESPONSE_RESULT && pixy->length == 4) {
                rgb->setRGB(pixy->buffer[0], pixy->buffer[1], pixy->buffer[2]);
                return 0; // Success
            } else if (pixy->type == PIXY_TYPE_RESPONSE_ERROR
                    && pixy->buffer[0] == PIXY_RESULT_PROG_CHANGING) {
                // Deal with program changing by waiting
                frc::Wait(0.000500);
            }
        }
        if (frc::GetTime() - start > 500) {
            return PIXY_RESULT_ERROR; // Timeout to prevent lockup
        }
        return PIXY_RESULT_ERROR;
    }
}


