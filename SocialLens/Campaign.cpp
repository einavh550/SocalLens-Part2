#include "Campaign.h"
#include "StringUtil.h"
#include <iostream>

// Starting size for the two dynamic arrays. They grow (double) on demand, so
// this is only the initial allocation, not a hard limit.
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
      campaignOwner(other.campaignOwner), // bind to the same client
      assets(new DigitalAsset*[other.assetCapacity]),
      assetCount(other.assetCount),
      assetCapacity(other.assetCapacity),
      creationDate(other.creationDate),
      reservedEquipment(new Equipment*[other.equipmentCapacity]),
      equipmentCount(other.equipmentCount),
      equipmentCapacity(other.equipmentCapacity)
{
    // Assets are OWNED by the campaign, so they must be deep-copied. clone()
    // gives us a real copy of the correct concrete type (StillPhoto/VideoClip).
    for (int i = 0; i < assetCount; ++i)
        assets[i] = other.assets[i]->clone();

    // Reserved equipment is OWNED by the studio, not the campaign, so we copy
    // only the pointers (shallow) — the campaign just references them.
    for (int i = 0; i < equipmentCount; ++i)
        reservedEquipment[i] = other.reservedEquipment[i];
}

Campaign::~Campaign()
{
    // Delete the assets we own, then the array that held them.
    for (int i = 0; i < assetCount; ++i)
        delete assets[i];
    delete[] assets;

    // Only the pointer array is ours here; the Equipment objects belong to the studio.
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
        int newCapacity = equipmentCapacity * 2;
        Equipment** bigger = new Equipment*[newCapacity];
        for (int i = 0; i < equipmentCount; ++i)
            bigger[i] = reservedEquipment[i];
        delete[] reservedEquipment;
        reservedEquipment = bigger;
        equipmentCapacity = newCapacity;
    }

    reservedEquipment[equipmentCount++] = eq;
    eq->setIsAvailable(false); // booked for this campaign's shoot day
}

Campaign& Campaign::operator+=(DigitalAsset* asset)
{
    if (asset == nullptr)
        return *this;

    if (assetCount == assetCapacity) {
        int newCapacity = assetCapacity * 2;
        DigitalAsset** bigger = new DigitalAsset*[newCapacity];
        for (int i = 0; i < assetCount; ++i)
            bigger[i] = assets[i];
        delete[] assets;
        assets = bigger;
        assetCapacity = newCapacity;
    }

    assets[assetCount++] = asset; // campaign now owns this pointer
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
        c.assets[i]->print(); // polymorphic, prints to std::cout
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
