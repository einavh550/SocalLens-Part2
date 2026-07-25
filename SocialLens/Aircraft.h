#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Equipment.h"

class Aircraft : virtual public Equipment {
    int maxAltitudeMeters;

public:
    Aircraft(int id, const char* modelName,
        int maxAltitudeMeters, bool available = true);

    int getMaxAltitude() const;
    void setMaxAltitude(int meters);

    void printSpecs() const override;
    Equipment* clone() const override;
};

#endif

