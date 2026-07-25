#ifndef __VIDEOCLIP_H
#define __VIDEOCLIP_H

#include <ostream>
#include "DigitalAsset.h"

class VideoClip : public DigitalAsset
{
public:
    enum VideoType
    {
        STORY,
        FEED
    };

private:
    int durationInSeconds;
    VideoType videoType;

public:
    VideoClip();
    VideoClip(int assetId, const char* fileName, double baseprice, int duration, VideoType vidtype);
    VideoClip(const VideoClip& other);
    ~VideoClip();
    VideoClip& operator=(const VideoClip& other);

    void setVidType(VideoType);
    void setDuration(int seconds);

    VideoType getVidType() const;
    int getDuration() const;

    double calculatePrice() const override;
    DigitalAsset* clone() const override;
    void print() const override;
};


#endif
