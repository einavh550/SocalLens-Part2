#include "Campaign.h"
#include <iostream>
#include <utility>

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
            title(title == nullptr ? "" : title),
      campaignOwner(owner),
            creationDate(date)
{
        assets.reserve(8);
}

Campaign::Campaign(const Campaign& other)
    : campaignId(other.campaignId),
            title(other.title),
      campaignOwner(other.campaignOwner),
      creationDate(other.creationDate)
{
        assets.reserve(other.assets.size());
        for (size_t i = 0; i < other.assets.size(); ++i)
                assets.push_back(other.assets[i]->clone());

    EquipmentListCopyContext copyContext;
    copyContext.target = &reservedEquipment;
    other.reservedEquipment.forEach(copyEquipmentPointer, &copyContext);
}

int Campaign::getCampaignId() const
{
    return campaignId;
}

const char* Campaign::getTitle() const
{
    return title.c_str();
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
    return static_cast<int>(assets.size());
}

double Campaign::getTotalPrice() const
{
    double total = 0.0;
    for (size_t i = 0; i < assets.size(); ++i)
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

Campaign& Campaign::operator+=(std::unique_ptr<DigitalAsset> asset)
{
    if (asset == nullptr)
        return *this;

    assets.push_back(std::move(asset));
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

    os << "Date: " << c.creationDate << "\n";

    os << "Assets (" << c.assets.size() << "):\n";
    for (size_t i = 0; i < c.assets.size(); ++i) {
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
