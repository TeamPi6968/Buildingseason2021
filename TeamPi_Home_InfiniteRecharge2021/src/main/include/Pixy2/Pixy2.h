 /* * Made for Robotics TeamPi 2021 Build Season
 * Author: Caleb Kyei
 * Date: 28/02/2021 01:00
 * 
 * Remarks: This is a ported Pixy 2 library from Java 
 *          for connecting pixy to the roborio
 * 
 * */

#pragma once

#include "frc/Timer.h"
#include "SPI_Link.h"

const int PIXY_BUFFERSIZE = 0x104;
const int PIXY_SEND_HEADER_SIZE = 4;
const int PIXY_MAX_PROGNAME = 33;
const int PIXY_DEFAULT_ARGVAL = 0x0;
const int PIXY_CHECKSUM_SYNC = 0xc1af;
const int PIXY_NO_CHECKSUM_SYNC = 0xc1ae;

// Packet types
const uint8_t PIXY_TYPE_REQUEST_CHANGE_PROG = 0x02;
const uint8_t PIXY_TYPE_REQUEST_RESOLUTION = 0x0c;
const uint8_t PIXY_TYPE_RESPONSE_RESOLUTION = 0x0d;
const uint8_t PIXY_TYPE_REQUEST_VERSION = 0x0e;
const uint8_t PIXY_TYPE_RESPONSE_VERSION = 0x0f;
const uint8_t PIXY_TYPE_RESPONSE_RESULT = 0x01;
const uint8_t PIXY_TYPE_RESPONSE_ERROR = 0x03;
const uint8_t PIXY_TYPE_REQUEST_BRIGHTNESS = 0x10;
const uint8_t PIXY_TYPE_REQUEST_SERVO = 0x12;
const uint8_t PIXY_TYPE_REQUEST_LED = 0x14;
const uint8_t PIXY_TYPE_REQUEST_LAMP = 0x16;
const uint8_t PIXY_TYPE_REQUEST_FPS = 0x18;

// Return result values
const int PIXY_RESULT_OK = 0;
const int PIXY_RESULT_ERROR = -1;
const int PIXY_RESULT_BUSY = -2;
const int PIXY_RESULT_CHECKSUM_ERROR = -3;
const int PIXY_RESULT_TIMEOUT = -4;
const int PIXY_RESULT_BUTTON_OVERRIDE = -5;
const int PIXY_RESULT_PROG_CHANGING = -6;

// RC-servo values
const int PIXY_RCS_MIN_POS = 0;
const int PIXY_RCS_MAX_POS = 1000;
const int PIXY_RCS_CENTER_POS = ((PIXY_RCS_MAX_POS - PIXY_RCS_MIN_POS) / 2);



class Pixy2
{
private:
    SPI_Link* Link;
	uint8_t getSync();
	Pixy2(SPI_Link *link);

	int frameWidth = -1;
	int frameHeight = -1;

    /* data */
public:

    uint8_t* buffer;
	int length = 0;
	int type = 0;
	uint8_t* bufferPayload;


	Version* version;
	Version* getVersionInfo();

	// Pixy2CCC* ccc;
	// Pixy2Line* line;
	// Pixy2Video* video;

	bool m_cs = false;
    
	int init();
	int sendPacket();	
	int receivePacket();
	int getVersion();
	uint8_t getResolution();
	int getFrameWidth();
	int getFrameHeight();
	uint8_t changeProg(const char *prog);
    enum LinkType {
    SPI, I2C, UART
	};

	uint8_t setCameraBrightness(int brightness);
	uint8_t setServos(int pan, int tilt);
	uint8_t setLED(int rgb);
	uint8_t setLED(int r, int g, int b);
	uint8_t setLamp(uint8_t upper, uint8_t lower);
	uint8_t getFPS();
	int init(int argument);

	Pixy2(LinkType type);
    

    ~Pixy2();


};

