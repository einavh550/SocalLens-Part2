#include "Client.h"
#include "Campaign.h"
#include <iostream>

Client::Client(int id, const char* name, const char* phone)
    : clientId(id),
      name(name == nullptr ? "" : name),
      phone(phone == nullptr ? "" : phone)
{
}

int Client::getClientId() const
{
    return clientId;
}

const char* Client::getName() const
{
    return name.c_str();
}

const char* Client::getPhone() const
{
    return phone.c_str();
}

void Client::setName(const char* newName)
{
    name = (newName == nullptr ? "" : newName);
}

void Client::setPhone(const char* newPhone)
{
    phone = (newPhone == nullptr ? "" : newPhone);
}

Campaign* Client::openCampaign(int campaignId, const char* title, const Date& date) const
{
    return new Campaign(campaignId, title, *this, date);
}

bool Client::operator==(const Client& other) const
{
    return clientId == other.clientId;
}

void Client::print() const
{
    std::cout << "Client #" << clientId << ": " << name
              << " (" << phone << ")";
}
