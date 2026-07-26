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
        Camera(int id, const char* modelName, CamType type,
            bool hasTripod, bool available = true);
        Camera(const Camera& other);
        ~Camera();
        Camera& operator=(const Camera& other);

        CamType getCamType() const;
        bool getHasTripod() const;

        void printSpecs() const override;
        Equipment* clone() const override;

        void setCamType(CamType);
        void setHasTripod(bool tripod);

   
};

#endif
