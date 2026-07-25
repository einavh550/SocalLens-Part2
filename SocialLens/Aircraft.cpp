#include "Aircraft.h"
#include <iostream>

Aircraft::Aircraft(int id, const char* modelName,
    int maxAltitudeMeters, bool available)
    : Equipment(id, modelName, available), maxAltitudeMeters(maxAltitudeMeters)
{
}

int Aircraft::getMaxAltitude() const
{
    return maxAltitudeMeters;
}

void Aircraft::setMaxAltitude(int meters)
{
    maxAltitudeMeters = meters;
}

void Aircraft::printSpecs() const
{
    std::cout << "Aircraft \"" << getModelName() << "\", max altitude: "
              << maxAltitudeMeters << "m";
}

Equipment* Aircraft::clone() const
{
    return new Aircraft(*this);
}
