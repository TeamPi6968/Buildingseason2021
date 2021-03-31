#include "Pixy2/Pixy2.h"

/**
 * Constructs Pixy2 object with supplied communication link
 * 
 * @param link {@link Link} to communicate with Pixy2
 */
Pixy2::Pixy2(SPI_Link *link) {
    this->Link = link;
    // Initializes send/return buffer and payload buffer
    buffer = (uint8_t*)malloc(PIXY_BUFFERSIZE);
    bufferPayload = buffer + PIXY_SEND_HEADER_SIZE;
    // Initializes tracker objects
    // This is done separately then pass the pixy2 object
}

/**
 * Initializes Pixy2 and waits for startup to complete
 * 
 * @param argument Argument to setup {@link Link}
 * 
 * @return Pixy2 error code
 */
int Pixy2::init(int argument) {
    // Opens link
    //int ret = Link->open(argument);
    if (true) {
        //Tries to connect, times out if unable to communicate after 5 seconds
        for (long t = frc::GetTime(); frc::GetTime() - t < 5000;) {
            // Gets version and resolution to check if communication is successful and stores for future use
            // if (getVersion() >= 0) {
            //     getResolution();
            //     return PIXY_RESULT_OK;
            // }
            frc::Wait(0.005);
        }
        return PIXY_RESULT_TIMEOUT;
    }
    return PIXY_RESULT_ERROR;
}

/**
 * Initializes Pixy2 and waits for startup to complete using default link argument
 * value
 * 
 * @return Pixy2 error code
 */
int Pixy2::init() {
    std::cout<<"init";
    return init(PIXY_DEFAULT_ARGVAL);
}

/**
 * Gets Pixy2 instance with supplied communication link type
 * 
 * @param type Communication {@link LinkType} to Pixy2
 * 
 * @return Pixy2 instance
 */
Pixy2::Pixy2(LinkType type) {

    switch (type) {
    case SPI:
        this->Link = new SPI_Link();
        break;
     case I2C:
    //     Link = new I2CLink();
        break;
     case UART:
    //     Link = new UARTLink();
        break;
     default:
    //     return NULL;
        break;
    }
    Pixy2(this->Link);
}


/**
 * Get width of the pixy's visual frame after initialization
 * 
 * @return Pixy2 Frame Width
 */
int Pixy2::getFrameWidth() {
    return frameWidth;
}

/**
 * Get height of the pixy's visual frame after initialization
 * 
 * @return Pixy2 Frame Height
 */
int Pixy2::getFrameHeight() {
    return frameHeight;
}



uint8_t Pixy2::getSync() {
    int i, attempts, cprev, res, start, ret;
    uint8_t* c = new uint8_t[1];

    // Parse incoming bytes until sync bytes are found
    for (i = attempts = cprev = 0; true; i++) {
        res = Link->receive(c, 1) & 0xff;
        if (res >= PIXY_RESULT_OK) {
            ret = c[0] & 0xff;
            // Since we're using little endian, previous byte is least significant byte
            start = cprev;
            // Current byte is most significant byte
            start |= ret << 8;
            cprev = ret;
            if (start == PIXY_CHECKSUM_SYNC) {
                m_cs = true;
                return PIXY_RESULT_OK;
            }
            if (start == PIXY_NO_CHECKSUM_SYNC) {
                m_cs = false;
                return PIXY_RESULT_OK;
            }
        }
        // If we've read some bytes and no sync, then wait and try again.
        // And do that several more times before we give up.
        // Pixy2 guarantees to respond within 100us.
        if (i >= 4) {
            if (attempts >= 4)
                return PIXY_RESULT_ERROR;

            frc::Wait(0.000025);
            attempts++;
            i = 0;
        }
    }
}

/**
 * Gets stored Pixy2 {@link Version} info or retrieves from Pixy2 if not present
 * 
 * @return Pixy2 Version Info
 */
Version* Pixy2::getVersionInfo() {
    if (this->version == NULL)
        getVersion();
    return this->version;
}


int Pixy2::sendPacket() {
    // Write header info at beginning of buffer
    buffer[0] = (PIXY_NO_CHECKSUM_SYNC & 0xff);
    buffer[1] = ((PIXY_NO_CHECKSUM_SYNC >> 8) & 0xff);
    buffer[2] = type;
    buffer[3] = length;
    // Add payload data to buffer
    for (int i = 0; i < length; i++) {
        buffer[4 + i] = bufferPayload[i];
    }
    // Send buffer
    return Link->send(buffer, (length + PIXY_SEND_HEADER_SIZE));
}

int Pixy2::receivePacket() {
    int csSerial, res;
    Checksum *csCalc = new Checksum();

    // Waits for sync bytes
    res = getSync();
    if (res < 0)
        // Sync not found
        return res;
    if (m_cs) {
        // Checksum sync
        res = Link->receive(buffer, 4);
        if (res < 0)
            return res;

        type = buffer[0] & 0xff;
        length = buffer[1] & 0xff;

        csSerial = ((buffer[3] & 0xff) << 8) | (buffer[2] & 0xff);

        // Receives message from buffer
        res = Link->receive(buffer, length, csCalc);

        if (res < 0)
            return res;
        // Checks for accuracy with checksum
        if (csSerial != csCalc->getChecksum())
            return PIXY_RESULT_CHECKSUM_ERROR;
    } else {
        // Non-checksum sync
        res = Link->receive(buffer, 2);
        if (res < 0)
            return res;

        type = buffer[0] & 0xff;
        length = buffer[1] & 0xff;

        // Receives message from buffer
        res = Link->receive(buffer, length);

        if (res < 0)
            return res;
    }
    return PIXY_RESULT_OK;
}

/**
 * Gets version info from Pixy2
 * 
 * @return Buffer length or Pixy2 error code
 */
int Pixy2::getVersion() {
    length = 0;
    type = PIXY_TYPE_REQUEST_VERSION;
    sendPacket();
    if (receivePacket() == 0) {
        if (type == PIXY_TYPE_RESPONSE_VERSION) {
            version = new Version(buffer);
            return length; // Success
        } else if (type == PIXY_TYPE_RESPONSE_ERROR)
            return PIXY_RESULT_BUSY;
    }
    return PIXY_RESULT_ERROR; // Some kind of bitstream error
}

/**
 * Sends change program packet to Pixy2
 * 
 * @param prog Program name
 * 
 * @return Pixy2 error code
 */
uint8_t Pixy2::changeProg(const char *prog) {
    int res = 0;

    // Poll for program to change
    while (true) {
        // Truncates supplied program name, or adds empty characters after to indicate end of string
        strncpy((char *)bufferPayload, prog, PIXY_MAX_PROGNAME);

        length = PIXY_MAX_PROGNAME;
        type = PIXY_TYPE_REQUEST_CHANGE_PROG;
        sendPacket();
        if (receivePacket() == 0) {
            res = ((buffer[3] & 0xff) << 24) | ((buffer[2] & 0xff) << 16) | ((buffer[1] & 0xff) << 8)
                    | (buffer[0] & 0xff);
            if (res > 0) {
                getResolution(); // Get resolution for future use
                return PIXY_RESULT_OK; // Success
            }
        } else
            return PIXY_RESULT_ERROR; // Some kind of bitstream error
        frc::Wait(0.001);
    }
}


uint8_t Pixy2::getResolution() {
    length = 1;
    bufferPayload[0] = 0; // Adds empty byte to payload as placeholder for future queries
    type = PIXY_TYPE_REQUEST_RESOLUTION;
    sendPacket();
    if (receivePacket() == 0) {
        if (type == PIXY_TYPE_RESPONSE_RESOLUTION) {
            frameWidth = ((buffer[1] & 0xff) << 8) | (buffer[0] & 0xff);
            frameHeight = ((buffer[3] & 0xff) << 8) | (buffer[2] & 0xff);
            return PIXY_RESULT_OK; // Success
        } else
            return PIXY_RESULT_ERROR;
    } else
        return PIXY_RESULT_ERROR; // Some kind of bitstream error
}

/**
 * Sets Pixy2 camera brightness between 0-255
 * 
 * @param brightness Byte representing camera brightness
 * 
 * @return Pixy2 error code
 */
uint8_t Pixy2::setCameraBrightness(int brightness) {
    int res;

    // Limits brightness between the 0 and 255
    brightness = (brightness >= 255 ? 255 : (brightness <= 0 ? 0 : brightness));

    bufferPayload[0] = brightness;
    length = 1;
    type = PIXY_TYPE_REQUEST_BRIGHTNESS;
    sendPacket();
    if (receivePacket() == 0 && type == PIXY_TYPE_RESPONSE_RESULT && length == 4) {
        res = ((buffer[3] & 0xff) << 24) | ((buffer[2] & 0xff) << 16) | ((buffer[1] & 0xff) << 8)
                | (buffer[0] & 0xff);
        return res; // Success
    } else
        return PIXY_RESULT_ERROR; // Some kind of bitstream error
}

/**
 * Sets Pixy2 servo positions between 0-1000
 * 
 * @param pan  Pan servo position
 * @param tilt Tilt servo position
 * 
 * @return Pixy2 error code
 */
uint8_t Pixy2::setServos(int pan, int tilt) {
    int res;

    // Limits servo values between 0 and 1000
    pan = (pan >= PIXY_RCS_MAX_POS ? PIXY_RCS_MAX_POS : (pan <= PIXY_RCS_MIN_POS ? PIXY_RCS_MIN_POS : pan));
    tilt = (tilt >= PIXY_RCS_MAX_POS ? PIXY_RCS_MAX_POS : (tilt <= PIXY_RCS_MIN_POS ? PIXY_RCS_MIN_POS : tilt));

    bufferPayload[0] = (pan & 0xff);
    bufferPayload[1] = ((pan >> 8) & 0xff);
    bufferPayload[2] = (tilt & 0xff);
    bufferPayload[3] = ((tilt >> 8) & 0xff);
    length = 4;
    type = PIXY_TYPE_REQUEST_SERVO;
    sendPacket();
    if (receivePacket() == 0 && type == PIXY_TYPE_RESPONSE_RESULT && length == 4) {
        res = ((buffer[3] & 0xff) << 24) | ((buffer[2] & 0xff) << 16) | ((buffer[1] & 0xff) << 8)
                | (buffer[0] & 0xff);
        return res; // Success
    } else
        return PIXY_RESULT_ERROR; // Some kind of bitstream error
}

/**
 * Sets Pixy2 LED color to specified RGB value
 * 
 * @param rgb RGB value
 * 
 * @return Pixy2 error code
 */
uint8_t Pixy2::setLED(int rgb) {
    return setLED((rgb >> 16) & 0xff, (rgb >> 8) & 0xff, rgb & 0xff);
}

/**
 * Sets Pixy2 LED color to specified RGB values between 0-255
 * 
 * @param r R value
 * @param g G value
 * @param b B value
 * 
 * @return Pixy2 error code
 */
uint8_t Pixy2::setLED(int r, int g, int b) {
    int res;

    // Limits rgb values between 0 and 255
    r = (r >= 255 ? 255 : (r <= 0 ? 0 : r));
    g = (g >= 255 ? 255 : (g <= 0 ? 0 : g));
    b = (b >= 255 ? 255 : (b <= 0 ? 0 : b));

    bufferPayload[0] = r;
    bufferPayload[1] = g;
    bufferPayload[2] = b;
    length = 3;
    type = PIXY_TYPE_REQUEST_LED;
    sendPacket();
    if (receivePacket() == 0 && type == PIXY_TYPE_RESPONSE_RESULT && length == 4) {
        res = ((buffer[3] & 0xff) << 24) | ((buffer[2] & 0xff) << 16) | ((buffer[1] & 0xff) << 8)
                | (buffer[0] & 0xff);
        return res; // Success
    } else
        return PIXY_RESULT_ERROR; // Some kind of bitstream error
}

/**
 * Turns Pixy2 light source on/off
 * 
 * Use 1 to indicate on, 0 to indicate off
 * 
 * @param upper Byte indicating status of white LEDs
 * @param lower Byte indicating status of RGB LED
 * 
 * @return Pixy2 error code
 */
uint8_t Pixy2::setLamp(uint8_t upper, uint8_t lower) {
    int res;

    bufferPayload[0] = upper;
    bufferPayload[1] = lower;
    length = 2;
    type = PIXY_TYPE_REQUEST_LAMP;
    sendPacket();
    if (receivePacket() == 0 && type == PIXY_TYPE_RESPONSE_RESULT && length == 4) {
        res = ((buffer[3] & 0xff) << 24) | ((buffer[2] & 0xff) << 16) | ((buffer[1] & 0xff) << 8)
                | (buffer[0] & 0xff);
        return res; // Success
    } else
        return PIXY_RESULT_ERROR; // Some kind of bitstream error
}

/**
 * Gets Pixy2 camera framerate between 2-62fps
 * 
 * @return Framerate or Pixy2 error code
 */
uint8_t Pixy2::getFPS() {
    int res;

    length = 0; // no args
    type = PIXY_TYPE_REQUEST_FPS;
    sendPacket();
    if (receivePacket() == 0 && type == PIXY_TYPE_RESPONSE_RESULT && length == 4) {
        res = ((buffer[3] & 0xff) << 24) | ((buffer[2] & 0xff) << 16) | ((buffer[1] & 0xff) << 8)
                | (buffer[0] & 0xff);
        return res; // Success
    } else
        return PIXY_RESULT_ERROR; // Some kind of bitstream error
}

Pixy2::~Pixy2()
{
}

