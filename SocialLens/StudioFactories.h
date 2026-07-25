#ifndef STUDIO_FACTORIES_H
#define STUDIO_FACTORIES_H

#include <memory>
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
    virtual std::unique_ptr<DigitalAsset> create(int id, const char* fileName, double basePrice) const = 0;
};

class StillPhotoFactory : public AssetFactory {
    StillPhoto::Orientation orientation;
    StillPhoto::EditStyle editStyle;

public:
    StillPhotoFactory(StillPhoto::Orientation orientation, StillPhoto::EditStyle editStyle)
        : orientation(orientation), editStyle(editStyle)
    {
    }

    std::unique_ptr<DigitalAsset> create(int id, const char* fileName, double basePrice) const
    {
        return std::make_unique<StillPhoto>(id, fileName, basePrice, orientation, editStyle);
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

    std::unique_ptr<DigitalAsset> create(int id, const char* fileName, double basePrice) const
    {
        return std::make_unique<VideoClip>(id, fileName, basePrice, durationInSeconds, videoType);
    }
};

class EquipmentFactory {
public:
    virtual ~EquipmentFactory() {}
    virtual std::unique_ptr<Equipment> create(int id, const char* modelName) const = 0;
};

class CameraFactory : public EquipmentFactory {
    Camera::CamType camType;
    bool hasTripod;

public:
    CameraFactory(Camera::CamType camType, bool hasTripod)
        : camType(camType), hasTripod(hasTripod)
    {
    }

    std::unique_ptr<Equipment> create(int id, const char* modelName) const
    {
        return std::make_unique<Camera>(id, modelName, camType, hasTripod);
    }
};

class AircraftFactory : public EquipmentFactory {
    int maxAltitudeMeters;

public:
    AircraftFactory(int maxAltitudeMeters)
        : maxAltitudeMeters(maxAltitudeMeters)
    {
    }

    std::unique_ptr<Equipment> create(int id, const char* modelName) const
    {
        return std::make_unique<Aircraft>(id, modelName, maxAltitudeMeters);
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

    std::unique_ptr<Equipment> create(int id, const char* modelName) const
    {
        return std::make_unique<Drone>(id, modelName, camType, hasTripod, maxAltitudeMeters, batteryLifeMinutes);
    }
};

#endif
