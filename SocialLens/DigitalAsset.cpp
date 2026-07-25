#include "DigitalAsset.h"
#include <iostream>

DigitalAsset::DigitalAsset(int id, const char* fileName, double basePrice)
    : assetId(id),
      fileName(fileName == nullptr ? "" : fileName),
      basePrice(basePrice)
{
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
