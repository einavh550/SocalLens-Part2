#include "Campaign.h"
#include "StringUtil.h"
#include "ArrayUtil.h"
#include <iostream>

#define CAMPAIGN_INITIAL_CAPACITY 8

Campaign::Campaign(int id, const char* title, const Client& owner, const Date& date)
    : campaignId(id),
      title(cloneString(title)),
      campaignOwner(owner),
      assets(new DigitalAsset*[CAMPAIGN_INITIAL_CAPACITY]),
      assetCount(0),
      assetCapacity(CAMPAIGN_INITIAL_CAPACITY),
      creationDate(date),
      reservedEquipment(new Equipment*[CAMPAIGN_INITIAL_CAPACITY]),
      equipmentCount(0),
      equipmentCapacity(CAMPAIGN_INITIAL_CAPACITY)
{
}

Campaign::Campaign(const Campaign& other)
    : campaignId(other.campaignId),
      title(cloneString(other.title)),
      campaignOwner(other.campaignOwner),
      assets(new DigitalAsset*[other.assetCapacity]),
      assetCount(other.assetCount),
      assetCapacity(other.assetCapacity),
      creationDate(other.creationDate),
      reservedEquipment(new Equipment*[other.equipmentCapacity]),
      equipmentCount(other.equipmentCount),
      equipmentCapacity(other.equipmentCapacity)
{
    for (int i = 0; i < assetCount; ++i)
        assets[i] = other.assets[i]->clone();

    for (int i = 0; i < equipmentCount; ++i)
        reservedEquipment[i] = other.reservedEquipment[i];
}

Campaign::~Campaign()
{
    for (int i = 0; i < assetCount; ++i)
        delete assets[i];
    delete[] assets;

    delete[] reservedEquipment;

    delete[] title;
}

int Campaign::getCampaignId() const
{
    return campaignId;
}

const char* Campaign::getTitle() const
{
    return title;
}

const Client& Campaign::getCampaignOwner() const
{
    return campaignOwner;
}

const Date& Campaign::getCreationDate() const
{
    return creationDate;
}

int Campaign::getAssetCount() const
{
    return assetCount;
}

double Campaign::getTotalPrice() const
{
    double total = 0.0;
    for (int i = 0; i < assetCount; ++i)
        total += assets[i]->calculatePrice();
    return total;
}

void Campaign::reserveEquipment(Equipment* eq)
{
    if (eq == nullptr)
        return;

    if (equipmentCount == equipmentCapacity) {
        equipmentCapacity *= 2;
        reservedEquipment = reinterpret_cast<Equipment**>(
            growPointerArray(reinterpret_cast<void**>(reservedEquipment), equipmentCount, equipmentCapacity));
    }

    reservedEquipment[equipmentCount++] = eq;
    eq->setIsAvailable(false);
}

Campaign& Campaign::operator+=(DigitalAsset* asset)
{
    if (asset == nullptr)
        return *this;

    if (assetCount == assetCapacity) {
        assetCapacity *= 2;
        assets = reinterpret_cast<DigitalAsset**>(
            growPointerArray(reinterpret_cast<void**>(assets), assetCount, assetCapacity));
    }

    assets[assetCount++] = asset;
    return *this;
}

bool Campaign::operator>(const Campaign& other) const
{
    return getTotalPrice() > other.getTotalPrice();
}

std::ostream& operator<<(std::ostream& os, const Campaign& c)
{
    os << "===== Campaign Quote =====\n";
    os << "Campaign #" << c.campaignId << ": " << c.title << "\n";
    os << "Owner: " << c.campaignOwner.getName()
       << " (ID " << c.campaignOwner.getClientId() << ")\n";

    char* dateText = c.creationDate.toString();
    os << "Date: " << dateText << "\n";
    delete[] dateText;

    os << "Assets (" << c.assetCount << "):\n";
    for (int i = 0; i < c.assetCount; ++i) {
        os << "  - ";
        c.assets[i]->print();
        os << "\n";
    }

    os << "Reserved equipment (" << c.equipmentCount << "):\n";
    for (int i = 0; i < c.equipmentCount; ++i) {
        os << "  - ";
        c.reservedEquipment[i]->printSpecs();
        os << "\n";
    }

    os << "TOTAL: $" << c.getTotalPrice() << "\n";
    os << "==========================\n";
    return os;
}

void Campaign::print() const
{
    std::cout << *this;
}
