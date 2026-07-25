#include <iostream>
#include "SocialLensStudio.h"
#include "Client.h"
#include "Campaign.h"
#include "StillPhoto.h"
#include "VideoClip.h"
#include "Camera.h"
#include "Aircraft.h"
#include "Drone.h"
#include "Date.h"
using namespace std;

//input helpers

static int readInt(const char* input) {
    int value;
    cout << input;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. " << input;
    }
    cin.ignore(10000, '\n');
    return value;
}

static double readDouble(const char* input) {
    double value;
    cout << input;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. " << input;
    }
    cin.ignore(10000, '\n');
    return value;
}

static void readString(const char* input, char* buf, int maxLen) {
    cout << input;
    cin.getline(buf, maxLen);
    if (!cin) {
        cin.clear();
        cin.ignore(10000, '\n');
        buf[0] = '\0';
    }
}

static Date readDate(const char* input) {
    cout << input << endl;
    int d = readInt("  Day:   ");
    int m = readInt("  Month: ");
    int y = readInt("  Year:  ");
    return Date(d, m, y);
}

//menu operations


static void doRegisterClient(SocialLensStudio& studio) {
    char name[100], phone[30];
    //Reads an ID
    int id = readInt("Client ID: ");
    //Reads a name
    readString("Client name: ", name, 100);
    //Reads a phone number
    readString("Phone number: ", phone, 30);
    //Creates a new Client and stores it in the clients array
    studio.registerClient(new Client(id, name, phone));
    cout << "Client registered successfully.\n";
}


static Campaign* doOpenCampaign(SocialLensStudio& studio) {
    //Ask for a client ID
    int clientId = readInt("Client ID to open campaign for: ");
    //Search for that client in the studio 
    Client* owner = studio.findClient(clientId);
    if (owner == nullptr) {
        cout << "Error: client not found.\n";
        return nullptr;
    }
    //read campaign ID, title, and date
    int  campId = readInt("Campaign ID:    ");
    char title[200];
    readString("Campaign title: ", title, 200);
    Date date = readDate("Creation date:");
    //reate a new Campaign
    Campaign* camp = new Campaign(campId, title, *owner, date);
    cout << "Campaign opened successfully.\n";
    return camp;
}


static void doAddAsset(Campaign* campaign) {
    //Check that there is an active campaign
    if (campaign == nullptr) {
        cout << "Error: no active campaign. Open a campaign first.\n";
        return;
    }
    //Ask if it's a photo or video
    cout << "Asset type: 1=Photo  2=Video\n";
    int type = readInt("Choice: ");
    //Read the common data
    int id = readInt("Asset ID:    ");
    char fileName[200];
    readString("File name:   ", fileName, 200);
    double base = readDouble("Base price:  ");
    //read extra data base on type
    if (type == 1) {
        cout << "Orientation: 1=Feed  2=Story\n";
        int o = readInt("Choice: ");
        cout << "Edit style:  1=Filter  2=Natural\n";
        int e = readInt("Choice: ");
        StillPhoto::Orientation orient = (o == 2) ? StillPhoto::STORY : StillPhoto::FEED;
        StillPhoto::EditStyle   style = (e == 2) ? StillPhoto::NATURAL : StillPhoto::FILTER;
        //Add the new asset
        *campaign += new StillPhoto(id, fileName, base, orient, style);
    }
    else if (type == 2) {
        int dur = readInt("Duration (seconds): ");
        cout << "Video type: 1=Feed  2=Story\n";
        int v = readInt("Choice: ");
        VideoClip::VideoType vtype = (v == 2) ? VideoClip::STORY : VideoClip::FEED;
        //Add the new asset
        *campaign += new VideoClip(id, fileName, base, dur, vtype);
    }
    else {
        cout << "Invalid asset type.\n";
    }
}


static void doAddEquipment(SocialLensStudio& studio) {
    //Ask what type of equipment
    cout << "Equipment type: 1=Camera  2=Aircraft  3=Drone\n";
    int type = readInt("Choice: ");
    //Read the common data
    int id = readInt("Equipment ID:  ");
    char model[100];
    readString("Model name:    ", model, 100);
    //read extra data base on type
    if (type == 1) {
        cout << "Camera type: 1=Stills  2=Video\n";
        int ct = readInt("Choice: ");
        cout << "Has tripod:  1=Yes  2=No\n";
        int ht = readInt("Choice: ");
        Camera::CamType camType = (ct == 2) ? Camera::VIDEO : Camera::STILLS;
        bool tripod = (ht == 1);
        //Create object and add to Equipment
        studio.addEquipment(new Camera(id, model, camType, tripod));
    }
    else if (type == 2) {
        int alt = readInt("Max altitude (m): ");
        //Create object and add to Equipment
        studio.addEquipment(new Aircraft(id, model, alt));
    }
    else if (type == 3) {
        cout << "Camera type: 1=Stills  2=Video\n";
        int ct = readInt("Choice: ");
        cout << "Has tripod:  1=Yes  2=No\n";
        int ht = readInt("Choice: ");
        int alt = readInt("Max altitude (m):   ");
        int bat = readInt("Battery life (min): ");
        Camera::CamType camType = (ct == 2) ? Camera::VIDEO : Camera::STILLS;
        bool tripod = (ht == 1);
        //Create object and add to Equipment
        studio.addEquipment(new Drone(id, model, camType, tripod, alt, bat));
    }
    else {
        cout << "Invalid equipment type.\n";
    }
}


static void doReserveEquipment(SocialLensStudio& studio, Campaign* campaign) {
    //Check there is an active campaign
    if (campaign == nullptr) {
        cout << "Error: no active campaign. Open a campaign first.\n";
        return;
    }
    //Read the equipment ID
    int eqId = readInt("Equipment ID to reserve: ");
    //Search for it in the studio
    Equipment* eq = studio.findEquipment(eqId);
    if (eq == nullptr) {
        cout << "Error: equipment not found.\n";
        return;
    }
    //reserve it for the campaign
    campaign->reserveEquipment(eq);
    cout << "Equipment reserved for campaign.\n";
}


static void doCompareCampaigns(Campaign* camp1, Campaign* camp2) {
    //Check that both campaigns exist
    if (camp1 == nullptr || camp2 == nullptr) {
        cout << "Error: need two campaigns to compare.\n";
        return;
    }
    //compares total price of both campaigns
    if (*camp1 > *camp2)
        cout << "Campaign \"" << camp1->getTitle() << "\" is more profitable.\n";
    else if (*camp2 > *camp1)
        cout << "Campaign \"" << camp2->getTitle() << "\" is more profitable.\n";
    else
        cout << "Both campaigns have equal total price.\n";
}


//operator++ loops through every piece of equipment and sets isAvailable = true
static void doCloseDay(SocialLensStudio& studio) {
    ++studio;
    cout << "Work day closed. All equipment is now available.\n";
}

//main 

int main() {
    SocialLensStudio studio("SocialLens Studio");

    Campaign* activeCampaign = nullptr;
    Campaign* previousCampaign = nullptr;

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
        case 2:
            previousCampaign = activeCampaign;
            activeCampaign = doOpenCampaign(studio);
            if (activeCampaign != nullptr)
                cout << *activeCampaign;
            break;
        case 3:
            doAddAsset(activeCampaign);
            break;
        case 4:
            doAddEquipment(studio);
            break;
        case 5:
            doReserveEquipment(studio, activeCampaign);
            break;
        case 6:
            doCompareCampaigns(activeCampaign, previousCampaign);
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

    delete activeCampaign;
    delete previousCampaign;
    return 0;
}
