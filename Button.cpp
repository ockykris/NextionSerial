#include "Button.h"
#include "NextionSerial.h"

Button::Button(uint32_t aPage, uint32_t aId, const std::string& aObjectName, NextionSerial& aNextionSerial) : 
  NextionUI(aPage, aId, aObjectName, aNextionSerial)
{
}

void Button::SetReleaseCallback(std::function<void()> aCallback)
{
    iReleaseCallback = std::move(aCallback);
}

void Button::SetPushCallback(std::function<void ()> aPushCallback)
{
    iPushCallback = std::move(aPushCallback);
}

void Button::PressReleaseTriggered(TEventType aEventType)
{
    switch (aEventType) {
        case TEventType::EPress:
        {
            if (iPushCallback != nullptr) { iPushCallback(); }
            break;
        }    
        case TEventType::ERelease:
        {
            if (iReleaseCallback != nullptr) { iReleaseCallback(); }
            break;
        }
        default:
            break;
    }
}