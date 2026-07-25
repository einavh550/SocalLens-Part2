#include "VideoClip.h"
#include <iostream>

#define VIDEO_PRICE_PER_SECOND 2.0
#define VIDEO_STORY_MULTIPLIER 1.10

VideoClip::VideoClip()
    : DigitalAsset(0, "", 0.0), durationInSeconds(0), videoType(FEED)
{
}

VideoClip::VideoClip(int assetId, const char* fileName, double baseprice, int duration, VideoType vidtype)
    : DigitalAsset(assetId, fileName, baseprice), durationInSeconds(duration), videoType(vidtype)
{
}

VideoClip::VideoClip(const VideoClip& other)
    : DigitalAsset(other), durationInSeconds(other.durationInSeconds), videoType(other.videoType)
{
}

VideoClip::~VideoClip()
{
}

VideoClip& VideoClip::operator=(const VideoClip& other)
{
    if (this != &other) {
        DigitalAsset::operator=(other);
        durationInSeconds = other.durationInSeconds;
        videoType = other.videoType;
    }
    return *this;
}

void VideoClip::setVidType(VideoType type)
{
    videoType = type;
}

void VideoClip::setDuration(int seconds)
{
    durationInSeconds = seconds;
}

VideoClip::VideoType VideoClip::getVidType() const
{
    return videoType;
}

int VideoClip::getDuration() const
{
    return durationInSeconds;
}

double VideoClip::calculatePrice() const
{
    double price = getBasePrice() + durationInSeconds * VIDEO_PRICE_PER_SECOND;
    if (videoType == STORY)
        price *= VIDEO_STORY_MULTIPLIER;
    return price;
}

DigitalAsset* VideoClip::clone() const
{
    return new VideoClip(*this);
}

void VideoClip::print() const
{
    DigitalAsset::print();
    std::cout << " | Video "
              << (videoType == STORY ? "Story" : "Feed") << ", "
              << durationInSeconds << "s -> $" << calculatePrice();
}
