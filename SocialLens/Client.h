#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <memory>

class Campaign;
class Date;

class Client {
    int clientId;
    std::string name;
    std::string phone;

public:
    Client(int id, const char* name, const char* phone);
    Client(const Client& other) = default;
    ~Client() = default;
    Client& operator=(const Client& other) = default;

    int getClientId() const;
    const char* getName() const;
    const char* getPhone() const;
    void setName(const char* name);
    void setPhone(const char* phone);

    std::unique_ptr<Campaign> openCampaign(int campaignId, const char* title, const Date& date) const;

    bool operator==(const Client& other) const;
    void print() const;
};

#endif


