#include "Equipment.h"
#include "StringUtil.h"

Equipment::Equipment(int id, const char* modelName, bool available)
    : equipmentid(id), modelName(cloneString(modelName)), isAvailable(available)
{
}

Equipment::Equipment(const Equipment& other)
    : equipmentid(other.equipmentid),
      modelName(cloneString(other.modelName)),
      isAvailable(other.isAvailable)
{
}

Equipment::~Equipment()
{
    delete[] modelName;
}

Equipment& Equipment::operator=(const Equipment& other)
{
    if (this != &other) {
        delete[] modelName;
        equipmentid = other.equipmentid;
        modelName = cloneString(other.modelName);
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
    return modelName;
}

bool Equipment::getIsAvailable() const
{
    return isAvailable;
}

void Equipment::setModelName(const char* name)
{
    delete[] modelName;
    modelName = cloneString(name);
}

void Equipment::setIsAvailable(bool available)
{
    isAvailable = available;
}
