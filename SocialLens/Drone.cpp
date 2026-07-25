#include "Drone.h"
#include <iostream>

Drone::Drone(int id, const char* modelName, CamType camType,
    bool hasTripod, int maxAltitudeMeters,
    int batteryLifeMinutes, bool available)
    : Equipment(id, modelName, available),
      Camera(id, modelName, camType, hasTripod, available),
      Aircraft(id, modelName, maxAltitudeMeters, available),
      batteryLifeMinutes(batteryLifeMinutes)
{
}

int Drone::getBatteryLife() const
{
    return batteryLifeMinutes;
}

void Drone::setBatteryLife(int minutes)
{
    batteryLifeMinutes = minutes;
}

void Drone::printSpecs() const
{
    std::cout << "Drone \"" << getModelName() << "\" ["
              << (getCamType() == VIDEO ? "Video" : "Stills") << "], tripod: "
              << (getHasTripod() ? "yes" : "no")
              << ", max altitude: " << getMaxAltitude() << "m"
              << ", battery: " << batteryLifeMinutes << " min";
}

std::unique_ptr<Equipment> Drone::clone() const
{
    return std::make_unique<Drone>(*this);
}
