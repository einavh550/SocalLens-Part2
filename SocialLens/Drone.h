#ifndef DRONE_H
#define DRONE_H

#include "Camera.h"
#include "Aircraft.h"

class Drone : public Camera, public Aircraft {
    int batteryLifeMinutes;

public:
    Drone(int id, const char* modelName, CamType camType,
        bool hasTripod, int maxAltitudeMeters,
        int batteryLifeMinutes, bool available = true);

    int  getBatteryLife() const;
    void setBatteryLife(int minutes);

    void printSpecs() const override;
    Equipment* clone() const override;
};

#endif

