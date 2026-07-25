#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include <ostream>
#include <string>
#include <vector>
#include <memory>
#include "Client.h"
#include "Date.h"
#include "DigitalAsset.h"
#include "Equipment.h"
#include "LinkedList.h"

class Campaign
{
	int campaignId;
	std::string title;
	const Client& campaignOwner;
	std::vector<std::unique_ptr<DigitalAsset>> assets;
	Date creationDate;
	LinkedList<Equipment*> reservedEquipment;

	
public:
	Campaign(int id, const char* title, const Client& owner, const Date& date);
	Campaign(const Campaign& other);

	Campaign& operator=(const Campaign& other) = delete;

	int getCampaignId() const;
	const char* getTitle() const;
	const Client& getCampaignOwner() const;
	const Date& getCreationDate() const;
	int getAssetCount() const;
	double getTotalPrice() const;

	void reserveEquipment(Equipment* eq);

	Campaign& operator+=(std::unique_ptr<DigitalAsset> asset);

	bool operator>(const Campaign& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Campaign& c);

	void print() const;

private:

};



#endif


