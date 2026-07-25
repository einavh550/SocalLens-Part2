#ifndef __CAMERA_H
#define __CAMERA_H

#include <ostream>
#include "Equipment.h"

class Camera : virtual public Equipment
{
public:
    enum CamType
    {
        STILLS,
        VIDEO
    };

    private:
        CamType camType;
        bool hasTripod;

    public:
        Camera();
        Camera(int id, const char* modelName, CamType type,
            bool hasTripod, bool available = true);

        CamType getCamType() const;
        bool getHasTripod() const;

        void printSpecs() const override;
        std::unique_ptr<Equipment> clone() const override;

        void setCamType(CamType);
        void setHasTripod(bool tripod);

   
};

#endif
