#include "SocialLensStudio.h"
#include "StringUtil.h"
#include "ArrayUtil.h"
#include "Campaign.h"
#include "Date.h"
#include "DigitalAsset.h"
#include <iostream>

SocialLensStudio::SocialLensStudio(const char* studioName)
    : studioName(cloneString(studioName)),
      clients(new Client*[INITIAL_CAPACITY]),
      clientCount(0),
      clientCapacity(INITIAL_CAPACITY),
      equipmentList(new Equipment*[INITIAL_CAPACITY]),
      equipmentCount(0),
    equipmentCapacity(INITIAL_CAPACITY),
    activeCampaign(nullptr),
    previousCampaign(nullptr)
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
    if (previousCampaign != nullptr) {
        delete previousCampaign;
        previousCampaign = nullptr;
    }
    if (activeCampaign != nullptr) {
        delete activeCampaign;
        activeCampaign = nullptr;
    }

    for (int i = 0; i < clientCount; ++i)
        delete clients[i];
    delete[] clients;

    for (int i = 0; i < equipmentCount; ++i)
        delete equipmentList[i];
    delete[] equipmentList;

    delete[] studioName;
}

void SocialLensStudio::copyFrom(const SocialLensStudio& other)
{
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

    activeCampaign = nullptr;
    previousCampaign = nullptr;
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
        clientCapacity *= 2;
        clients = reinterpret_cast<Client**>(
            growPointerArray(reinterpret_cast<void**>(clients), clientCount, clientCapacity));
    }

    clients[clientCount++] = client;
}

void SocialLensStudio::addEquipment(Equipment* eq)
{
    if (eq == nullptr)
        return;

    if (equipmentCount == equipmentCapacity) {
        equipmentCapacity *= 2;
        equipmentList = reinterpret_cast<Equipment**>(
            growPointerArray(reinterpret_cast<void**>(equipmentList), equipmentCount, equipmentCapacity));
    }

    equipmentList[equipmentCount++] = eq;
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

Campaign* SocialLensStudio::openCampaign(int clientId, int campaignId, const char* title, const Date& date)
{
    Client* owner = findClient(clientId);
    if (owner == nullptr)
        return nullptr;

    Campaign* campaign = owner->openCampaign(campaignId, title, date);

    if (previousCampaign != nullptr)
        delete previousCampaign;

    previousCampaign = activeCampaign;
    activeCampaign = campaign;
    return activeCampaign;
}

Campaign* SocialLensStudio::getActiveCampaign() const
{
    return activeCampaign;
}

Campaign* SocialLensStudio::getPreviousCampaign() const
{
    return previousCampaign;
}

void SocialLensStudio::addAssetToActiveCampaign(DigitalAsset* asset)
{
    if (activeCampaign == nullptr || asset == nullptr)
        return;

    *activeCampaign += asset;
}

SocialLensStudio& SocialLensStudio::operator++()
{
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
