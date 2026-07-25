#ifndef CLIENT_H
#define CLIENT_H

class Campaign; // forward declaration 

class Client {
    int clientId;
    char* name;
    char* phone;

public:
    Client(int id, const char* name, const char* phone);
    Client(const Client& other);
    ~Client();
    Client& operator=(const Client& other);

    int getClientId() const;
    const char* getName() const;
    const char* getPhone() const;
    void setName(const char* name);
    void setPhone(const char* phone);

    // creates a new campaign
    Campaign* openCampaign(int campaignId, const char* title) const;

    bool operator==(const Client& other) const;
    void print() const;
};

#endif // CLIENT_H

