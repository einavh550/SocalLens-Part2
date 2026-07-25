#include "SocialLensStudio.h"
#include <iostream>
#include <utility>

SocialLensStudio::SocialLensStudio(const char* studioName)
    : studioName(studioName == nullptr ? "" : studioName)
{
}

SocialLensStudio& SocialLensStudio::getInstance(const char* studioName)
{
    static SocialLensStudio instance(studioName);
    return instance;
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

void SocialLensStudio::registerClient(std::unique_ptr<Client> client)
{
    if (client == nullptr)
        return;

    clients.push_back(std::move(client));
}

void SocialLensStudio::addEquipment(std::unique_ptr<Equipment> eq)
{
    if (eq == nullptr)
        return;

    equipmentList.push_back(std::move(eq));
}

Client* SocialLensStudio::findClient(int clientId) const
{
    for (size_t i = 0; i < clients.size(); ++i)
        if (clients[i]->getClientId() == clientId)
            return clients[i].get();
    return nullptr;
}

Equipment* SocialLensStudio::findEquipment(int equipmentId) const
{
    for (size_t i = 0; i < equipmentList.size(); ++i)
        if (equipmentList[i]->getEquipmentId() == equipmentId)
            return equipmentList[i].get();
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
