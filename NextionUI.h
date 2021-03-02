#pragma once

#include <cstdint>
#include <string>

class NextionSerial;

enum class TEventType 
{
    EPress,
    ERelease
};

class NextionUI
{
public:
  explicit NextionUI(uint32_t aPage, uint32_t aId, const std::string& aObjectName, NextionSerial& aSerialHandler);
  virtual ~NextionUI() = default;

  uint32_t GetPage() const;
  uint32_t GetId() const;

  virtual void PressReleaseTriggered(TEventType aEventType);

protected:
  uint32_t iPage;
  uint32_t iId;
  std::string iObjectName;
  NextionSerial& iNextionSerial;
};