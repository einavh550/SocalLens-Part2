#include "Client.h"
#include "Campaign.h"
#include "StringUtil.h"
#include <iostream>

Client::Client(int id, const char* name, const char* phone)
    : clientId(id), name(cloneString(name)), phone(cloneString(phone))
{
}

Client::Client(const Client& other)
    : clientId(other.clientId),
      name(cloneString(other.name)),
      phone(cloneString(other.phone))
{
}

Client::~Client()
{
    delete[] name;
    delete[] phone;
}

Client& Client::operator=(const Client& other)
{
    if (this != &other) {
        // Free the old buffers before taking copies of the new ones,
        // otherwise the previous allocations would leak.
        delete[] name;
        delete[] phone;

        clientId = other.clientId;
        name = cloneString(other.name);
        phone = cloneString(other.phone);
    }
    return *this;
}

int Client::getClientId() const
{
    return clientId;
}

const char* Client::getName() const
{
    return name;
}

const char* Client::getPhone() const
{
    return phone;
}

void Client::setName(const char* newName)
{
    delete[] name;
    name = cloneString(newName);
}

void Client::setPhone(const char* newPhone)
{
    delete[] phone;
    phone = cloneString(newPhone);
}

Campaign* Client::openCampaign(int campaignId, const char* title, const Date& date) const
{
    // The client is the natural owner of the "create a campaign" action, so the
    // Campaign is built here rather than with a raw 'new Campaign' out in main.
    return new Campaign(campaignId, title, *this, date);
}

bool Client::operator==(const Client& other) const
{
    // Two clients are considered the same when they share the same unique ID.
    return clientId == other.clientId;
}

void Client::print() const
{
    std::cout << "Client #" << clientId << ": " << name
              << " (" << phone << ")";
}
