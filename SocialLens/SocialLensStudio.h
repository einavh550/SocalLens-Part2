#ifndef SOCIAL_LENS_STUDIO_H
#define SOCIAL_LENS_STUDIO_H

#include "Client.h"
#include "Equipment.h"

class SocialLensStudio {
    static const int INITIAL_CAPACITY = 20;

    char* studioName;
    Client** clients;
    int clientCount;
    int clientCapacity;
    Equipment** equipmentList;
    int equipmentCount;
    int equipmentCapacity;

public:
    SocialLensStudio(const char* studioName);
    SocialLensStudio(const SocialLensStudio& other);
    ~SocialLensStudio();
    SocialLensStudio& operator=(const SocialLensStudio& other);

    const char* getStudioName() const;
    int getClientCount() const;
    int getEquipmentCount() const;

    // Add a new client to the studio roster
    void registerClient(Client* client);

    // Add new equipment to the studio inventory
    void addEquipment(Equipment* eq);

    // Find a client by ID; returns nullptr if not found
    Client* findClient(int clientId) const;

    // Find equipment by ID; returns nullptr if not found
    Equipment* findEquipment(int equipmentId) const;

    // Close the work day: mark all equipment as available for the next day
    SocialLensStudio& operator++();

    void print() const;
};

#endif // SOCIAL_LENS_STUDIO_H