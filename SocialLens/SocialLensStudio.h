#ifndef SOCIAL_LENS_STUDIO_H
#define SOCIAL_LENS_STUDIO_H

#include <string>
#include <vector>
#include <memory>
#include "Client.h"
#include "Equipment.h"

class Campaign;
class Date;
class DigitalAsset;

class SocialLensStudio {
    std::string studioName;
    std::vector<std::unique_ptr<Client>> clients;
    std::vector<std::unique_ptr<Equipment>> equipmentList;
    std::unique_ptr<Campaign> activeCampaign;
    std::unique_ptr<Campaign> previousCampaign;

public:
    static SocialLensStudio& getInstance(const char* studioName = "SocialLens Studio");

    SocialLensStudio(const SocialLensStudio& other) = delete;
    SocialLensStudio(SocialLensStudio&& other) = delete;
    ~SocialLensStudio() = default;
    SocialLensStudio& operator=(const SocialLensStudio& other) = delete;
    SocialLensStudio& operator=(SocialLensStudio&& other) = delete;

    const char* getStudioName() const;
    int getClientCount() const;
    int getEquipmentCount() const;

    void registerClient(std::unique_ptr<Client> client);

    void addEquipment(std::unique_ptr<Equipment> eq);

    Client* findClient(int clientId) const;

    Equipment* findEquipment(int equipmentId) const;

    Campaign* openCampaign(int clientId, int campaignId, const char* title, const Date& date);
    Campaign* getActiveCampaign() const;
    Campaign* getPreviousCampaign() const;
    void addAssetToActiveCampaign(std::unique_ptr<DigitalAsset> asset);

    SocialLensStudio& operator++();

    void print() const;

private:
    SocialLensStudio(const char* studioName);
};

#endif
