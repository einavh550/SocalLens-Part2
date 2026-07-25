#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Equipment.h"

class Aircraft : virtual public Equipment {
    int maxAltitudeMeters;

public:
    Aircraft(int id, const char* modelName,
        int maxAltitudeMeters, bool available = true);
    Aircraft(const Aircraft& other);
    virtual ~Aircraft();
    Aircraft& operator=(const Aircraft& other);

    int getMaxAltitude() const;
    void setMaxAltitude(int meters);

    void printSpecs() const override;
};

#endif // AIRCRAFT_H
