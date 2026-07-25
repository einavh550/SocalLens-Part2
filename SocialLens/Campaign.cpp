#include "Campaign.h"
#include "StringUtil.h"
#include "ArrayUtil.h"
#include <iostream>

#define CAMPAIGN_INITIAL_CAPACITY 8

namespace {
struct EquipmentListCopyContext {
    LinkedList<Equipment*>* target;
};

struct EquipmentListPrintContext {
    std::ostream* output;
};

void copyEquipmentPointer(Equipment* const& equipment, void* rawContext)
{
    EquipmentListCopyContext* context = static_cast<EquipmentListCopyContext*>(rawContext);
    if (context != nullptr && context->target != nullptr) {
        context->target->addToEnd(equipment);
    }
}

void printEquipmentPointer(Equipment* const& equipment, void* rawContext)
{
    EquipmentListPrintContext* context = static_cast<EquipmentListPrintContext*>(rawContext);
    if (context != nullptr && context->output != nullptr && equipment != nullptr) {
        *(context->output) << "  - ";
        equipment->printSpecs();
        *(context->output) << "\n";
    }
}
}

Campaign::Campaign(int id, const char* title, const Client& owner, const Date& date)
    : campaignId(id),
      title(cloneString(title)),
      campaignOwner(owner),
      assets(new DigitalAsset*[CAMPAIGN_INITIAL_CAPACITY]),
      assetCount(0),
      assetCapacity(CAMPAIGN_INITIAL_CAPACITY),
    creationDate(date)
{
}

Campaign::Campaign(const Campaign& other)
    : campaignId(other.campaignId),
      title(cloneString(other.title)),
      campaignOwner(other.campaignOwner),
      assets(new DigitalAsset*[other.assetCapacity]),
      assetCount(other.assetCount),
      assetCapacity(other.assetCapacity),
      creationDate(other.creationDate)
{
    for (int i = 0; i < assetCount; ++i)
        assets[i] = other.assets[i]->clone();

    EquipmentListCopyContext copyContext;
    copyContext.target = &reservedEquipment;
    other.reservedEquipment.forEach(copyEquipmentPointer, &copyContext);
}

Campaign::~Campaign()
{
    for (int i = 0; i < assetCount; ++i)
        delete assets[i];
    delete[] assets;

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

    if (reservedEquipment.addToEnd(eq)) {
        eq->setIsAvailable(false);
    }
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

    os << "Reserved equipment (" << c.reservedEquipment.size() << "):\n";
    EquipmentListPrintContext printContext;
    printContext.output = &os;
    c.reservedEquipment.forEach(printEquipmentPointer, &printContext);

    os << "TOTAL: $" << c.getTotalPrice() << "\n";
    os << "==========================\n";
    return os;
}

void Campaign::print() const
{
    std::cout << *this;
}
