#include "Equipment.h"

Equipment::Equipment(int id, const char* modelName, bool available)
    : equipmentid(id),
      modelName(modelName == nullptr ? "" : modelName),
      isAvailable(available)
{
}

Equipment::Equipment(const Equipment& other)
    : equipmentid(other.equipmentid), modelName(other.modelName), isAvailable(other.isAvailable)
{
}

Equipment::~Equipment()
{
}

Equipment& Equipment::operator=(const Equipment& other)
{
    if (this != &other) {
        equipmentid = other.equipmentid;
        modelName = other.modelName;
        isAvailable = other.isAvailable;
    }
    return *this;
}

int Equipment::getEquipmentId() const
{
    return equipmentid;
}

const char* Equipment::getModelName() const
{
    return modelName.c_str();
}

bool Equipment::getIsAvailable() const
{
    return isAvailable;
}

void Equipment::setModelName(const char* name)
{
    modelName = (name == nullptr ? "" : name);
}

void Equipment::setIsAvailable(bool available)
{
    isAvailable = available;
}
