#ifndef DIGITAL_ASSET_H
#define DIGITAL_ASSET_H

#include <ostream>
#include <string>
#include <memory>

class DigitalAsset
{
	int assetId;
	std::string fileName;
	double basePrice;

public:
	DigitalAsset(int id, const char* fileName, double basePrice);
	DigitalAsset(const DigitalAsset& other) = default;
	virtual ~DigitalAsset() = default;
	DigitalAsset& operator=(const DigitalAsset& other) = default;

	int getAssetId() const;
	const char* getFileName() const;
	double getBasePrice() const;

	void setFileName(const char* fileName);
	void setBasePrice(double price);

	virtual double calculatePrice() const = 0;
	virtual std::unique_ptr<DigitalAsset> clone() const = 0;
	virtual void print() const;

private:

};




#endif


