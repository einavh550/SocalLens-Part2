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
	char* title;
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

	Campaign& operator=(const Campaign& other) = delete;

	int getCampaignId() const;
	const char* getTitle() const;
	const Client& getCampaignOwner() const;
	const Date& getCreationDate() const;
	int getAssetCount() const;
	double getTotalPrice() const;

	void reserveEquipment(Equipment* eq);

	Campaign& operator+=(DigitalAsset* asset);

	bool operator>(const Campaign& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Campaign& c);

	void print() const;

private:

};



#endif


