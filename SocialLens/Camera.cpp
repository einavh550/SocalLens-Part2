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

Camera::Camera(const Camera& other)
    : Equipment(other), camType(other.camType), hasTripod(other.hasTripod)
{
}

Camera::~Camera()
{
}

Camera& Camera::operator=(const Camera& other)
{
    if (this != &other) {
        Equipment::operator=(other);
        camType = other.camType;
        hasTripod = other.hasTripod;
    }
    return *this;
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
