#include "SocialLensStudio.h"
#include "StringUtil.h"
#include <iostream>

SocialLensStudio::SocialLensStudio(const char* studioName)
    : studioName(cloneString(studioName)),
      clients(new Client*[INITIAL_CAPACITY]),
      clientCount(0),
      clientCapacity(INITIAL_CAPACITY),
      equipmentList(new Equipment*[INITIAL_CAPACITY]),
      equipmentCount(0),
      equipmentCapacity(INITIAL_CAPACITY)
{
}

SocialLensStudio::SocialLensStudio(const SocialLensStudio& other)
    : studioName(cloneString(other.studioName)),
      clients(new Client*[other.clientCapacity]),
      clientCount(other.clientCount),
      clientCapacity(other.clientCapacity),
      equipmentList(new Equipment*[other.equipmentCapacity]),
      equipmentCount(other.equipmentCount),
      equipmentCapacity(other.equipmentCapacity)
{
    // The studio OWNS its clients and equipment, so both are deep-copied:
    // clients via their copy constructor, equipment via polymorphic clone().
    for (int i = 0; i < clientCount; ++i)
        clients[i] = new Client(*other.clients[i]);
    for (int i = 0; i < equipmentCount; ++i)
        equipmentList[i] = other.equipmentList[i]->clone();
}

SocialLensStudio::~SocialLensStudio()
{
    for (int i = 0; i < clientCount; ++i)
        delete clients[i];
    delete[] clients;

    for (int i = 0; i < equipmentCount; ++i)
        delete equipmentList[i];
    delete[] equipmentList;

    delete[] studioName;
}

SocialLensStudio& SocialLensStudio::operator=(const SocialLensStudio& other)
{
    if (this != &other) {
        // Release everything we currently own before taking fresh copies.
        for (int i = 0; i < clientCount; ++i)
            delete clients[i];
        delete[] clients;
        for (int i = 0; i < equipmentCount; ++i)
            delete equipmentList[i];
        delete[] equipmentList;
        delete[] studioName;

        studioName = cloneString(other.studioName);

        clientCount = other.clientCount;
        clientCapacity = other.clientCapacity;
        clients = new Client*[clientCapacity];
        for (int i = 0; i < clientCount; ++i)
            clients[i] = new Client(*other.clients[i]);

        equipmentCount = other.equipmentCount;
        equipmentCapacity = other.equipmentCapacity;
        equipmentList = new Equipment*[equipmentCapacity];
        for (int i = 0; i < equipmentCount; ++i)
            equipmentList[i] = other.equipmentList[i]->clone();
    }
    return *this;
}

const char* SocialLensStudio::getStudioName() const
{
    return studioName;
}

int SocialLensStudio::getClientCount() const
{
    return clientCount;
}

int SocialLensStudio::getEquipmentCount() const
{
    return equipmentCount;
}

void SocialLensStudio::registerClient(Client* client)
{
    if (client == nullptr)
        return;

    if (clientCount == clientCapacity) {
        int newCapacity = clientCapacity * 2;
        Client** bigger = new Client*[newCapacity];
        for (int i = 0; i < clientCount; ++i)
            bigger[i] = clients[i];
        delete[] clients;
        clients = bigger;
        clientCapacity = newCapacity;
    }

    clients[clientCount++] = client; // studio takes ownership
}

void SocialLensStudio::addEquipment(Equipment* eq)
{
    if (eq == nullptr)
        return;

    if (equipmentCount == equipmentCapacity) {
        int newCapacity = equipmentCapacity * 2;
        Equipment** bigger = new Equipment*[newCapacity];
        for (int i = 0; i < equipmentCount; ++i)
            bigger[i] = equipmentList[i];
        delete[] equipmentList;
        equipmentList = bigger;
        equipmentCapacity = newCapacity;
    }

    equipmentList[equipmentCount++] = eq; // studio takes ownership
}

Client* SocialLensStudio::findClient(int clientId) const
{
    for (int i = 0; i < clientCount; ++i)
        if (clients[i]->getClientId() == clientId)
            return clients[i];
    return nullptr;
}

Equipment* SocialLensStudio::findEquipment(int equipmentId) const
{
    for (int i = 0; i < equipmentCount; ++i)
        if (equipmentList[i]->getEquipmentId() == equipmentId)
            return equipmentList[i];
    return nullptr;
}

SocialLensStudio& SocialLensStudio::operator++()
{
    // End of the work day: every piece of equipment becomes available again.
    for (int i = 0; i < equipmentCount; ++i)
        equipmentList[i]->setIsAvailable(true);
    return *this;
}

void SocialLensStudio::print() const
{
    std::cout << "Studio: " << studioName << "\n";

    std::cout << "Clients (" << clientCount << "):\n";
    for (int i = 0; i < clientCount; ++i) {
        std::cout << "  - ";
        clients[i]->print();
        std::cout << "\n";
    }

    std::cout << "Equipment (" << equipmentCount << "):\n";
    for (int i = 0; i < equipmentCount; ++i) {
        std::cout << "  - ";
        equipmentList[i]->printSpecs();
        std::cout << (equipmentList[i]->getIsAvailable() ? " [available]" : " [reserved]")
                  << "\n";
    }
}
