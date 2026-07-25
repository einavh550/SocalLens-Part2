#ifndef DIGITAL_ASSET_H
#define DIGITAL_ASSET_H

#include <ostream>

class DigitalAsset
{
	int assetId;
	char* fileName;
	double basePrice;

public:
	DigitalAsset(int id, const char* fileName, double basePrice);
	DigitalAsset(const DigitalAsset& other);
	virtual ~DigitalAsset();
	DigitalAsset& operator=(const DigitalAsset& other);

	int getAssetId() const;
	const char* getFileName() const;
	double getBasePrice() const;

	void setFileName(const char* fileName);
	void setBasePrice(double price);

	virtual double calculatePrice() const = 0;
	virtual DigitalAsset* clone() const = 0;
	virtual void print() const;

private:

};




#endif // !DIGITAL_ASSET_H

