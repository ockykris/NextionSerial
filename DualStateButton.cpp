#include "DualStateButton.h"
#include "NextionSerial.h"

DualStateButton::DualStateButton(uint32_t aPage, uint32_t aId, const std::string& aObjectName, NextionSerial& aNextionSerial) : 
  Button(aPage, aId, aObjectName, aNextionSerial)
{
}

bool DualStateButton::GetState() const
{
    return iNextionSerial.GetCurrentDualStateButton(iObjectName);
}
