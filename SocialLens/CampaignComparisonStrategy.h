#ifndef CAMPAIGN_COMPARISON_STRATEGY_H
#define CAMPAIGN_COMPARISON_STRATEGY_H

#include "Campaign.h"

class CampaignComparisonStrategy {
public:
    virtual ~CampaignComparisonStrategy() {}
    virtual const Campaign* pick(const Campaign* first, const Campaign* second) const = 0;
};

class HigherProfitComparisonStrategy : public CampaignComparisonStrategy {
public:
    const Campaign* pick(const Campaign* first, const Campaign* second) const
    {
        if (first == nullptr || second == nullptr)
            return nullptr;
        if (*first > *second)
            return first;
        if (*second > *first)
            return second;
        return nullptr;
    }
};

class LowerProfitComparisonStrategy : public CampaignComparisonStrategy {
public:
    const Campaign* pick(const Campaign* first, const Campaign* second) const
    {
        if (first == nullptr || second == nullptr)
            return nullptr;
        if (*first > *second)
            return second;
        if (*second > *first)
            return first;
        return nullptr;
    }
};

#endif
