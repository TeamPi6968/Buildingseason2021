/**
 * Made for Robotics TeamPi 2021 Build Season
 * Date: 10/02/2021
 * 
 * Author: Caleb Kyei
 * 
 * Date: 04/03/2021 01:00
 * Remarks: This contains the brains of the intake system
 *          - Storage, loader and intake (motors, pixy and pneumatics)
 * 
 **/ 

#pragma once

#include "LoaderStorage.h"


class Intake_System
{
private:

    int nrOfCells;
    void cellAdded();

public:
    Loader *loader;
    Storage *storage;
    

    Intake_System(Motors* m_loader, Motors* m_storage); // Without the IR sensor
    ~Intake_System();

    void cellGone();
    bool isAvailable();
};


