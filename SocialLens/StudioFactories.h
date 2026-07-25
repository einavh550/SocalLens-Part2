#ifndef STUDIO_FACTORIES_H
#define STUDIO_FACTORIES_H

#include "DigitalAsset.h"
#include "StillPhoto.h"
#include "VideoClip.h"
#include "Equipment.h"
#include "Camera.h"
#include "Aircraft.h"
#include "Drone.h"

class AssetFactory {
public:
    virtual ~AssetFactory() {}
    virtual DigitalAsset* create(int id, const char* fileName, double basePrice) const = 0;
};

class StillPhotoFactory : public AssetFactory {
    StillPhoto::Orientation orientation;
    StillPhoto::EditStyle editStyle;

public:
    StillPhotoFactory(StillPhoto::Orientation orientation, StillPhoto::EditStyle editStyle)
        : orientation(orientation), editStyle(editStyle)
    {
    }

    DigitalAsset* create(int id, const char* fileName, double basePrice) const
    {
        return new StillPhoto(id, fileName, basePrice, orientation, editStyle);
    }
};

class VideoClipFactory : public AssetFactory {
    int durationInSeconds;
    VideoClip::VideoType videoType;

public:
    VideoClipFactory(int durationInSeconds, VideoClip::VideoType videoType)
        : durationInSeconds(durationInSeconds), videoType(videoType)
    {
    }

    DigitalAsset* create(int id, const char* fileName, double basePrice) const
    {
        return new VideoClip(id, fileName, basePrice, durationInSeconds, videoType);
    }
};

class EquipmentFactory {
public:
    virtual ~EquipmentFactory() {}
    virtual Equipment* create(int id, const char* modelName) const = 0;
};

class CameraFactory : public EquipmentFactory {
    Camera::CamType camType;
    bool hasTripod;

public:
    CameraFactory(Camera::CamType camType, bool hasTripod)
        : camType(camType), hasTripod(hasTripod)
    {
    }

    Equipment* create(int id, const char* modelName) const
    {
        return new Camera(id, modelName, camType, hasTripod);
    }
};

class AircraftFactory : public EquipmentFactory {
    int maxAltitudeMeters;

public:
    AircraftFactory(int maxAltitudeMeters)
        : maxAltitudeMeters(maxAltitudeMeters)
    {
    }

    Equipment* create(int id, const char* modelName) const
    {
        return new Aircraft(id, modelName, maxAltitudeMeters);
    }
};

class DroneFactory : public EquipmentFactory {
    Camera::CamType camType;
    bool hasTripod;
    int maxAltitudeMeters;
    int batteryLifeMinutes;

public:
    DroneFactory(Camera::CamType camType, bool hasTripod, int maxAltitudeMeters, int batteryLifeMinutes)
        : camType(camType), hasTripod(hasTripod), maxAltitudeMeters(maxAltitudeMeters), batteryLifeMinutes(batteryLifeMinutes)
    {
    }

    Equipment* create(int id, const char* modelName) const
    {
        return new Drone(id, modelName, camType, hasTripod, maxAltitudeMeters, batteryLifeMinutes);
    }
};

#endif
