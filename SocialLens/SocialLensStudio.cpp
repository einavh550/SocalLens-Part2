#include "SocialLensStudio.h"
#include <iostream>

SocialLensStudio::SocialLensStudio(const char* studioName)
    : studioName(studioName == nullptr ? "" : studioName)
{
}

SocialLensStudio::SocialLensStudio(const SocialLensStudio& other)
{
    copyFrom(other);
}

SocialLensStudio::~SocialLensStudio()
{
    releaseAll();
}

SocialLensStudio& SocialLensStudio::operator=(const SocialLensStudio& other)
{
    if (this != &other) {
        releaseAll();
        copyFrom(other);
    }
    return *this;
}

void SocialLensStudio::releaseAll()
{
    for (size_t i = 0; i < clients.size(); ++i)
        delete clients[i];
    clients.clear();

    for (size_t i = 0; i < equipmentList.size(); ++i)
        delete equipmentList[i];
    equipmentList.clear();
}

void SocialLensStudio::copyFrom(const SocialLensStudio& other)
{
    studioName = other.studioName;

    clients.reserve(other.clients.size());
    for (size_t i = 0; i < other.clients.size(); ++i)
        clients.push_back(new Client(*other.clients[i]));

    equipmentList.reserve(other.equipmentList.size());
    for (size_t i = 0; i < other.equipmentList.size(); ++i)
        equipmentList.push_back(other.equipmentList[i]->clone());
}

const char* SocialLensStudio::getStudioName() const
{
    return studioName.c_str();
}

int SocialLensStudio::getClientCount() const
{
    return static_cast<int>(clients.size());
}

int SocialLensStudio::getEquipmentCount() const
{
    return static_cast<int>(equipmentList.size());
}

void SocialLensStudio::registerClient(Client* client)
{
    if (client == nullptr)
        return;

    clients.push_back(client);
}

void SocialLensStudio::addEquipment(Equipment* eq)
{
    if (eq == nullptr)
        return;

    equipmentList.push_back(eq);
}

Client* SocialLensStudio::findClient(int clientId) const
{
    for (size_t i = 0; i < clients.size(); ++i)
        if (clients[i]->getClientId() == clientId)
            return clients[i];
    return nullptr;
}

Equipment* SocialLensStudio::findEquipment(int equipmentId) const
{
    for (size_t i = 0; i < equipmentList.size(); ++i)
        if (equipmentList[i]->getEquipmentId() == equipmentId)
            return equipmentList[i];
    return nullptr;
}

SocialLensStudio& SocialLensStudio::operator++()
{
    for (size_t i = 0; i < equipmentList.size(); ++i)
        equipmentList[i]->setIsAvailable(true);
    return *this;
}

void SocialLensStudio::print() const
{
    std::cout << "Studio: " << studioName << "\n";

    std::cout << "Clients (" << clients.size() << "):\n";
    for (size_t i = 0; i < clients.size(); ++i) {
        std::cout << "  - ";
        clients[i]->print();
        std::cout << "\n";
    }

    std::cout << "Equipment (" << equipmentList.size() << "):\n";
    for (size_t i = 0; i < equipmentList.size(); ++i) {
        std::cout << "  - ";
        equipmentList[i]->printSpecs();
        std::cout << (equipmentList[i]->getIsAvailable() ? " [available]" : " [reserved]")
                  << "\n";
    }
}
