#include "Intake_System.h"

Intake_System::Intake_System(Motors* m_loader, Motors* m_storage)
{
    this->loader = new Loader(m_loader);
    this->storage = new Storage(m_storage);
}

Intake_System::~Intake_System()
{
}