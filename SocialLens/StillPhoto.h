#ifndef STILL_PHOTO_H
#define STILL_PHOTO_H

#include "DigitalAsset.h"

class StillPhoto : public DigitalAsset {
public:
    enum Orientation { FEED, STORY };
    enum EditStyle { FILTER, NATURAL };

private:
    Orientation orientation;
    EditStyle editStyle;

public:
    StillPhoto(int id, const char* fileName, double basePrice,
        Orientation orient, EditStyle style);
    StillPhoto(const StillPhoto& other);
    ~StillPhoto();
    StillPhoto& operator=(const StillPhoto& other);

    Orientation getOrientation() const;
    EditStyle getEditStyle()   const;
    void setOrientation(Orientation orient);
    void setEditStyle(EditStyle style);

    double calculatePrice() const override;
    DigitalAsset* clone() const override;
    void print() const override;
};

#endif

