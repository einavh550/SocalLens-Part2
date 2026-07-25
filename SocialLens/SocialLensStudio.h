#ifndef SOCIAL_LENS_STUDIO_H
#define SOCIAL_LENS_STUDIO_H

#include <string>
#include <vector>
#include "Client.h"
#include "Equipment.h"

class SocialLensStudio {
    std::string studioName;
    std::vector<Client*> clients;
    std::vector<Equipment*> equipmentList;

public:
    SocialLensStudio(const char* studioName);
    SocialLensStudio(const SocialLensStudio& other);
    ~SocialLensStudio();
    SocialLensStudio& operator=(const SocialLensStudio& other);

    const char* getStudioName() const;
    int getClientCount() const;
    int getEquipmentCount() const;

    void registerClient(Client* client);

    void addEquipment(Equipment* eq);

    Client* findClient(int clientId) const;

    Equipment* findEquipment(int equipmentId) const;

    SocialLensStudio& operator++();

    void print() const;

private:
    void releaseAll();
    void copyFrom(const SocialLensStudio& other);
};

#endif
