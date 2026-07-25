#include "Camera.h"
#include <iostream>

Camera::Camera()
    : Equipment(0, "", true), camType(STILLS), hasTripod(false)
{
}

Camera::Camera(int id, const char* modelName, CamType type,
    bool hasTripod, bool available)
    : Equipment(id, modelName, available), camType(type), hasTripod(hasTripod)
{
}

Camera::CamType Camera::getCamType() const
{
    return camType;
}

bool Camera::getHasTripod() const
{
    return hasTripod;
}

void Camera::printSpecs() const
{
    std::cout << "Camera \"" << getModelName() << "\" ["
              << (camType == VIDEO ? "Video" : "Stills") << "], tripod: "
              << (hasTripod ? "yes" : "no");
}

Equipment* Camera::clone() const
{
    return new Camera(*this);
}

void Camera::setCamType(CamType type)
{
    camType = type;
}

void Camera::setHasTripod(bool tripod)
{
    hasTripod = tripod;
}
