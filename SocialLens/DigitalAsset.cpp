#include "DigitalAsset.h"
#include "StringUtil.h"
#include <iostream>

DigitalAsset::DigitalAsset(int id, const char* fileName, double basePrice)
    : assetId(id), fileName(cloneString(fileName)), basePrice(basePrice)
{
}

DigitalAsset::DigitalAsset(const DigitalAsset& other)
    : assetId(other.assetId),
      fileName(cloneString(other.fileName)),
      basePrice(other.basePrice)
{
}

DigitalAsset::~DigitalAsset()
{
    delete[] fileName;
}

DigitalAsset& DigitalAsset::operator=(const DigitalAsset& other)
{
    if (this != &other) {
        delete[] fileName;
        assetId = other.assetId;
        fileName = cloneString(other.fileName);
        basePrice = other.basePrice;
    }
    return *this;
}

int DigitalAsset::getAssetId() const
{
    return assetId;
}

const char* DigitalAsset::getFileName() const
{
    return fileName;
}

double DigitalAsset::getBasePrice() const
{
    return basePrice;
}

void DigitalAsset::setFileName(const char* newFileName)
{
    delete[] fileName;
    fileName = cloneString(newFileName);
}

void DigitalAsset::setBasePrice(double price)
{
    basePrice = price;
}

void DigitalAsset::print() const
{
    std::cout << "Asset #" << assetId << " [" << fileName << "] base $" << basePrice;
}
