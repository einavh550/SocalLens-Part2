#include "Drone.h"
#include <iostream>

// Because Equipment is a *virtual* base of both Camera and Aircraft, the most
// derived class (Drone) is responsible for constructing the single shared
// Equipment sub-object. The Equipment(...) calls inside Camera/Aircraft are
// ignored while building a Drone, so it is initialized exactly once here.
Drone::Drone(int id, const char* modelName, CamType camType,
    bool hasTripod, int maxAltitudeMeters,
    int batteryLifeMinutes, bool available)
    : Equipment(id, modelName, available),
      Camera(id, modelName, camType, hasTripod, available),
      Aircraft(id, modelName, maxAltitudeMeters, available),
      batteryLifeMinutes(batteryLifeMinutes)
{
}

Drone::Drone(const Drone& other)
    : Equipment(other),
      Camera(other),
      Aircraft(other),
      batteryLifeMinutes(other.batteryLifeMinutes)
{
}

Drone::~Drone()
{
}

Drone& Drone::operator=(const Drone& other)
{
    if (this != &other) {
        // Assign the Camera and Aircraft parts through their own operator=.
        // Each also re-copies the shared Equipment part; the final state is
        // correct, and there is no leak because operator= frees before copying.
        Camera::operator=(other);
        Aircraft::operator=(other);
        batteryLifeMinutes = other.batteryLifeMinutes;
    }
    return *this;
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

Equipment* Drone::clone() const
{
    return new Drone(*this);
}
