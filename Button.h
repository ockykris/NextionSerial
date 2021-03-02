#pragma once

#include "NextionUI.h"

#include <cstdint>
#include <functional>
#include <string>

class NextionSerial;

class Button : public NextionUI
{
public:
    explicit Button(uint32_t aPage, uint32_t aId, const std::string& aObjectName, NextionSerial& aNextionSerial);

    void SetPushCallback(std::function<void()> aPushCallback);
    void SetReleaseCallback(std::function<void()> aReleaseCallback);
    
    void PressReleaseTriggered(TEventType aEventType) override;

private:
    std::function<void()> iPushCallback {nullptr};
    std::function<void()> iReleaseCallback {nullptr};
};

