#pragma once

#include "Button.h"

#include <cstdint>
#include <string>

class NextionSerial;

class DualStateButton : public Button
{
public:
    explicit DualStateButton(uint32_t aPage, uint32_t aId, const std::string& aObjectName, NextionSerial& aNextionSerial);
    bool GetState() const;
};

