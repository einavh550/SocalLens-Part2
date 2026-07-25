#include <iostream>
#include <climits>
#include <memory>
#include <utility>
#include "SocialLensStudio.h"
#include "Client.h"
#include "Campaign.h"
#include "StillPhoto.h"
#include "VideoClip.h"
#include "Camera.h"
#include "Aircraft.h"
#include "Drone.h"
#include "Date.h"
#include "StudioFactories.h"
#include "CampaignComparisonStrategy.h"
using namespace std;

static int readInt(const char* prompt, int minValue = INT_MIN, int maxValue = INT_MAX) {
    int value;
    cout << prompt;
    while (!(cin >> value) || value < minValue || value > maxValue) {
        if (cin.eof()) {
            cin.clear();
            return minValue;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input, please try again. " << prompt;
    }
    cin.ignore(10000, '\n');
    return value;
}

static double readDouble(const char* prompt, double minValue = 0.0) {
    double value;
    cout << prompt;
    while (!(cin >> value) || value < minValue) {
        if (cin.eof()) {
            cin.clear();
            return minValue;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input, please try again. " << prompt;
    }
    cin.ignore(10000, '\n');
    return value;
}

static void readString(const char* prompt, char* buffer, int maxLength) {
    cout << prompt;
    cin.getline(buffer, maxLength);
    while (!cin || buffer[0] == '\0') {
        if (cin.eof()) {
            cin.clear();
            buffer[0] = '\0';
            return;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input, please try again. " << prompt;
        cin.getline(buffer, maxLength);
    }
}

static Date readDate(const char* prompt) {
    cout << prompt << endl;
    int day = readInt("  Day (1-31):   ", 1, 31);
    int month = readInt("  Month (1-12): ", 1, 12);
    int year = readInt("  Year:         ", 1, 9999);
    return Date(day, month, year);
}

static void doRegisterClient(SocialLensStudio& studio) {
    int id = readInt("Client ID: ", 1);
    if (studio.findClient(id) != nullptr) {
        cout << "Error: a client with this ID already exists.\n";
        return;
    }
    char name[100];
    char phone[30];
    readString("Client name: ", name, 100);
    readString("Phone number: ", phone, 30);
    studio.registerClient(std::make_unique<Client>(id, name, phone));
    cout << "Client registered successfully.\n";
}

static std::unique_ptr<Campaign> doOpenCampaign(SocialLensStudio& studio) {
    int clientId = readInt("Client ID to open campaign for: ", 1);
    Client* owner = studio.findClient(clientId);
    if (owner == nullptr) {
        cout << "Error: client not found.\n";
        return nullptr;
    }
    int campaignId = readInt("Campaign ID:    ", 1);
    char title[200];
    readString("Campaign title: ", title, 200);
    Date date = readDate("Creation date:");
    std::unique_ptr<Campaign> campaign = owner->openCampaign(campaignId, title, date);
    cout << "Campaign opened successfully.\n";
    return campaign;
}


static void doAddAsset(Campaign* campaign) {
    if (campaign == nullptr) {
        cout << "Error: no active campaign. Open a campaign first.\n";
        return;
    }
    cout << "Asset type: 1=Photo  2=Video\n";
    int type = readInt("Choice: ", 1, 2);
    int id = readInt("Asset ID:    ", 1);
    char fileName[200];
    readString("File name:   ", fileName, 200);
    double basePrice = readDouble("Base price:  ", 0.0);
    if (type == 1) {
        cout << "Orientation: 1=Feed  2=Story\n";
        int orientationChoice = readInt("Choice: ", 1, 2);
        cout << "Edit style:  1=Filter  2=Natural\n";
        int styleChoice = readInt("Choice: ", 1, 2);
        StillPhoto::Orientation orientation = (orientationChoice == 2) ? StillPhoto::STORY : StillPhoto::FEED;
        StillPhoto::EditStyle style = (styleChoice == 2) ? StillPhoto::NATURAL : StillPhoto::FILTER;
        StillPhotoFactory factory(orientation, style);
        *campaign += factory.create(id, fileName, basePrice);
    }
    else {
        int duration = readInt("Duration (seconds): ", 0);
        cout << "Video type: 1=Feed  2=Story\n";
        int videoChoice = readInt("Choice: ", 1, 2);
        VideoClip::VideoType videoType = (videoChoice == 2) ? VideoClip::STORY : VideoClip::FEED;
        VideoClipFactory factory(duration, videoType);
        *campaign += factory.create(id, fileName, basePrice);
    }
    cout << "Asset added to campaign.\n";
}

static void doAddEquipment(SocialLensStudio& studio) {
    cout << "Equipment type: 1=Camera  2=Aircraft  3=Drone\n";
    int type = readInt("Choice: ", 1, 3);
    int id = readInt("Equipment ID:  ", 1);
    if (studio.findEquipment(id) != nullptr) {
        cout << "Error: equipment with this ID already exists.\n";
        return;
    }
    char model[100];
    readString("Model name:    ", model, 100);
    if (type == 1) {
        cout << "Camera type: 1=Stills  2=Video\n";
        int camChoice = readInt("Choice: ", 1, 2);
        cout << "Has tripod:  1=Yes  2=No\n";
        int tripodChoice = readInt("Choice: ", 1, 2);
        Camera::CamType camType = (camChoice == 2) ? Camera::VIDEO : Camera::STILLS;
        CameraFactory factory(camType, tripodChoice == 1);
        studio.addEquipment(factory.create(id, model));
    }
    else if (type == 2) {
        int altitude = readInt("Max altitude (m): ", 0);
        AircraftFactory factory(altitude);
        studio.addEquipment(factory.create(id, model));
    }
    else {
        cout << "Camera type: 1=Stills  2=Video\n";
        int camChoice = readInt("Choice: ", 1, 2);
        cout << "Has tripod:  1=Yes  2=No\n";
        int tripodChoice = readInt("Choice: ", 1, 2);
        int altitude = readInt("Max altitude (m):   ", 0);
        int battery = readInt("Battery life (min): ", 0);
        Camera::CamType camType = (camChoice == 2) ? Camera::VIDEO : Camera::STILLS;
        DroneFactory factory(camType, tripodChoice == 1, altitude, battery);
        studio.addEquipment(factory.create(id, model));
    }
    cout << "Equipment added to studio.\n";
}

static void doReserveEquipment(SocialLensStudio& studio, Campaign* campaign) {
    if (campaign == nullptr) {
        cout << "Error: no active campaign. Open a campaign first.\n";
        return;
    }
    int equipmentId = readInt("Equipment ID to reserve: ", 1);
    Equipment* equipment = studio.findEquipment(equipmentId);
    if (equipment == nullptr) {
        cout << "Error: equipment not found.\n";
        return;
    }
    if (!equipment->getIsAvailable()) {
        cout << "Error: equipment is already reserved.\n";
        return;
    }
    campaign->reserveEquipment(equipment);
    cout << "Equipment reserved for campaign.\n";
}

static void doCompareCampaigns(Campaign* first, Campaign* second) {
    if (first == nullptr || second == nullptr) {
        cout << "Error: need two campaigns to compare.\n";
        return;
    }
    HigherProfitComparisonStrategy strategy;
    const Campaign* selected = strategy.pick(first, second);
    if (selected == nullptr)
        cout << "Both campaigns have equal total price.\n";
    else
        cout << "Campaign \"" << selected->getTitle() << "\" is more profitable.\n";
}

static void doCloseDay(SocialLensStudio& studio) {
    ++studio;
    cout << "Work day closed. All equipment is now available.\n";
}

int main() {
    SocialLensStudio& studio = SocialLensStudio::getInstance("SocialLens Studio");

    std::unique_ptr<Campaign> activeCampaign;
    std::unique_ptr<Campaign> previousCampaign;

    bool running = true;
    while (running) {
        cout << "\n=== SocialLens Studio Menu ===\n"
            << "1. Register new client\n"
            << "2. Open new campaign\n"
            << "3. Add media asset to active campaign\n"
            << "4. Add equipment to studio\n"
            << "5. Reserve equipment for active campaign\n"
            << "6. Compare campaign profitability\n"
            << "7. Close business day\n"
            << "8. Exit\n";
        int choice = readInt("Choice: ");
        switch (choice) {
        case 1:
            doRegisterClient(studio);
            break;
        case 2: {
            std::unique_ptr<Campaign> opened = doOpenCampaign(studio);
            if (opened != nullptr) {
                previousCampaign = std::move(activeCampaign);
                activeCampaign = std::move(opened);
                cout << *activeCampaign;
            }
            break;
        }
        case 3:
            doAddAsset(activeCampaign.get());
            break;
        case 4:
            doAddEquipment(studio);
            break;
        case 5:
            doReserveEquipment(studio, activeCampaign.get());
            break;
        case 6:
            doCompareCampaigns(activeCampaign.get(), previousCampaign.get());
            break;
        case 7:
            doCloseDay(studio);
            break;
        case 8:
            running = false;
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please enter 1-8.\n";
        }
    }

    return 0;
}
