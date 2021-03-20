#include "SPI_Link.h"


SPI_Link::SPI_Link(/* args */)
{
}

SPI_Link::~SPI_Link()
{
}

int SPI_Link::open(int arg){

    switch (arg)
    {
    case 1:
        *port = SPI::Port::kOnboardCS1;
        break;
    case 2:
        *port = SPI::Port::kOnboardCS2;
        break;
    case 3:
        *port = SPI::Port::kOnboardCS3;
        break;
    case 4:
        *port = SPI::Port::kMXP;
        break;
    case 0:
    default:
        *port = SPI::Port::kOnboardCS0;
    }
    
    spi = new SPI(*port);
    spi->SetClockRate(PIXY_SPI_CLOCKRATE);
    spi->SetMSBFirst();
    spi->SetSampleDataOnTrailingEdge();
    spi->SetClockActiveLow();
    spi->SetChipSelectActiveLow();
    return 0;
}


int SPI_Link::receive(uint8_t *buffer, int length, Checksum *cs)
{
    if (cs != nullptr)
    {
        cs->reset();
    }
    spi->Read(false, buffer, length);
    if (cs != nullptr)
    {
        for (int i = 0; i < length; i++)
        {
            int csb = buffer[i] & 0xff;
            cs->updateChecksum(csb);
        }
    }
    return length;
}

int SPI_Link::receive(uint8_t *buffer, int length)
{
    return receive(buffer, length, nullptr);
}

int SPI_Link::send(uint8_t *buffer, int length)
{
    spi->Write(buffer, length);
    return length;
}