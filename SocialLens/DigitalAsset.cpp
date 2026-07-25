#include "DigitalAsset.h"
#include <iostream>

DigitalAsset::DigitalAsset(int id, const char* fileName, double basePrice)
    : assetId(id),
      fileName(fileName == nullptr ? "" : fileName),
      basePrice(basePrice)
{
}

DigitalAsset::DigitalAsset(const DigitalAsset& other)
    : assetId(other.assetId), fileName(other.fileName), basePrice(other.basePrice)
{
}

DigitalAsset::~DigitalAsset()
{
}

DigitalAsset& DigitalAsset::operator=(const DigitalAsset& other)
{
    if (this != &other) {
        assetId = other.assetId;
        fileName = other.fileName;
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
    return fileName.c_str();
}

double DigitalAsset::getBasePrice() const
{
    return basePrice;
}

void DigitalAsset::setFileName(const char* newFileName)
{
    fileName = (newFileName == nullptr ? "" : newFileName);
}

void DigitalAsset::setBasePrice(double price)
{
    basePrice = price;
}

void DigitalAsset::print() const
{
    std::cout << "Asset #" << assetId << " [" << fileName << "] base $" << basePrice;
}
