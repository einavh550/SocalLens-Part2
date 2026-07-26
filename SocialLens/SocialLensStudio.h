#ifndef SOCIAL_LENS_STUDIO_H
#define SOCIAL_LENS_STUDIO_H

#include "Client.h"
#include "Equipment.h"

class Campaign;
class Date;
class DigitalAsset;

class SocialLensStudio {
    static const int INITIAL_CAPACITY = 20;

    char* studioName;
    Client** clients;
    int clientCount;
    int clientCapacity;
    Equipment** equipmentList;
    int equipmentCount;
    int equipmentCapacity;
    Campaign* activeCampaign;
    Campaign* previousCampaign;

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

    Campaign* openCampaign(int clientId, int campaignId, const char* title, const Date& date);
    Campaign* getActiveCampaign() const;
    Campaign* getPreviousCampaign() const;
    void addAssetToActiveCampaign(DigitalAsset* asset);

    SocialLensStudio& operator++();

    void print() const;

private:
    void releaseAll();
    void copyFrom(const SocialLensStudio& other);
};

#endif
