#include "StillPhoto.h"
#include <iostream>

#define PHOTO_STORY_MULTIPLIER  1.20
#define PHOTO_FILTER_MULTIPLIER 1.15

StillPhoto::StillPhoto(int id, const char* fileName, double basePrice,
    Orientation orient, EditStyle style)
    : DigitalAsset(id, fileName, basePrice), orientation(orient), editStyle(style)
{
}

StillPhoto::Orientation StillPhoto::getOrientation() const
{
    return orientation;
}

StillPhoto::EditStyle StillPhoto::getEditStyle() const
{
    return editStyle;
}

void StillPhoto::setOrientation(Orientation orient)
{
    orientation = orient;
}

void StillPhoto::setEditStyle(EditStyle style)
{
    editStyle = style;
}

double StillPhoto::calculatePrice() const
{
    double price = getBasePrice();
    if (orientation == STORY)
        price *= PHOTO_STORY_MULTIPLIER;
    if (editStyle == FILTER)
        price *= PHOTO_FILTER_MULTIPLIER;
    return price;
}

std::unique_ptr<DigitalAsset> StillPhoto::clone() const
{
    return std::make_unique<StillPhoto>(*this);
}

void StillPhoto::print() const
{
    DigitalAsset::print();
    std::cout << " | Photo "
              << (orientation == STORY ? "Story" : "Feed") << ", "
              << (editStyle == FILTER ? "Filter" : "Natural")
              << " -> $" << calculatePrice();
}
