#pragma once

#include "mbed.h"

#include <vector>

class NextionUI;

class NextionSerial 
{
public:
    explicit NextionSerial(PinName aTxPin, PinName aRxPin, int aBaud);

    bool GetCurrentDualStateButton(const std::string& aObjectName);
    void AddNextionUI(NextionUI* aNextionUI);

private:
    void SerialLoop();

private:
    BufferedSerial iNextionSerial;
    std::vector<NextionUI*> iNextionUiElements;
    Thread serialThread;
};