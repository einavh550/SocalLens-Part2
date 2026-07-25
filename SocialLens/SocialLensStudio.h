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
    static SocialLensStudio& getInstance(const char* studioName = "SocialLens Studio");

    SocialLensStudio(const SocialLensStudio& other) = delete;
    SocialLensStudio(SocialLensStudio&& other) = delete;
    ~SocialLensStudio();
    SocialLensStudio& operator=(const SocialLensStudio& other) = delete;
    SocialLensStudio& operator=(SocialLensStudio&& other) = delete;

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
    SocialLensStudio(const char* studioName);
    void releaseAll();
};

#endif
