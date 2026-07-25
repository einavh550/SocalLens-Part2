#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include <ostream>
#include "Client.h"
#include "Date.h"
#include "DigitalAsset.h"
#include "Equipment.h"

class Campaign
{
	int campaignId;
	char* titel;
	const Client& campaignOwner;
	DigitalAsset** assets;
	int assetCount;
	int assetCapacity;
	Date creationDate;
	Equipment** reservedEquipment;
	int equipmentCount;
	int equipmentCapacity;

	
public:
	Campaign(int id, const char* title, const Client& owner, const Date& date);
	Campaign(const Campaign& other);
	~Campaign();

	// Assignment is deleted: a reference member cannot be rebound after construction
	Campaign& operator=(const Campaign& other) = delete;

	int getCampaignId() const;
	const char* getTitle() const;
	const Client& getCampaignOwner() const;
	const Date& getCreationDate() const;
	int getAssetCount() const;
	double getTotalPrice() const;

	// Reserve a piece of equipment for this campaign's shoot day
	void reserveEquipment(Equipment* eq);

	// Add a media asset (Campaign takes ownership of the pointer)
	Campaign& operator+=(DigitalAsset* asset);

	// True if this campaign's total price is higher than other's
	bool operator>(const Campaign& other) const;

	// Print a price quote / receipt for the campaign
	friend std::ostream& operator<<(std::ostream& os, const Campaign& c);

	void print() const;

private:

};



#endif // CAMPAIGN_H

