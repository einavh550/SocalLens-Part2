#ifndef DRONE_H
#define DRONE_H

#include "Camera.h"
#include "Aircraft.h"

// Drone inherits Camera and Aircraft; Equipment is shared via virtual inheritance
class Drone : public Camera, public Aircraft {
    int batteryLifeMinutes;

public:
    Drone(int id, const char* modelName, CamType camType,
        bool hasTripod, int maxAltitudeMeters,
        int batteryLifeMinutes, bool available = true);
    Drone(const Drone& other);
    ~Drone();
    Drone& operator=(const Drone& other);

    int  getBatteryLife() const;
    void setBatteryLife(int minutes);

    void printSpecs() const override;
};

#endif // DRONE_H
