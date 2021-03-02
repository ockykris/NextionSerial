#include "NextionSerial.h"
#include "NextionUI.h"

#include <cstdio>
#include <iterator>
#include <string>

NextionSerial::NextionSerial(PinName aTxPin, PinName aRxPin, int aBaud) :
  iNextionSerial(aTxPin, aRxPin, aBaud)
{
  iNextionSerial.set_blocking(true);
  serialThread.start([this]() { SerialLoop(); });
}

void NextionSerial::AddNextionUI(NextionUI* aNextionUI)
{
    iNextionUiElements.emplace_back(aNextionUI);
}

void NextionSerial::SerialLoop() {
  while (true) {
    char receivedBytes[16]{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    iNextionSerial.read(&receivedBytes, sizeof(receivedBytes));

    // 0x65 is UI Input Event
    if (receivedBytes[0] == 0x65) {
      auto nextionUI = std::find_if(iNextionUiElements.begin(), iNextionUiElements.end(), [&receivedBytes](NextionUI* aNextionUI)
      {
          return (aNextionUI->GetPage() == static_cast<int>(receivedBytes[1]) &&
                 (aNextionUI->GetId() == static_cast<int>(receivedBytes[2])));
      });

      if (nextionUI != iNextionUiElements.end())
      {
          if (static_cast<int>(receivedBytes[3] == 1))
          {
              (*nextionUI)->PressReleaseTriggered(TEventType::EPress);
          }
          else if (static_cast<int>(receivedBytes[3] == 0))
          {
              (*nextionUI)->PressReleaseTriggered(TEventType::ERelease);
          }
      }
    }
  }
}

bool NextionSerial::GetCurrentDualStateButton(const std::string& aObjectName)
{
    std::string command = "get ";
    command.append(aObjectName);
    command.append(".val");
    command.append(3, 0xff);
    iNextionSerial.write(command.c_str(), command.size());

    char receivedBytes[16]{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    iNextionSerial.read(&receivedBytes, sizeof(receivedBytes));

      if (receivedBytes[0] == 0x71 && receivedBytes[1] == 0x00 &&
          receivedBytes[2] == 0x00 && receivedBytes[3] == 0x00 &&
          receivedBytes[4] == 0x00 && receivedBytes[5] == 0xFF &&
          receivedBytes[6] == 0xFF && receivedBytes[7] == 0xFF) {
        return false;
      } else if (receivedBytes[0] == 0x71 && receivedBytes[1] == 0x01 &&
                 receivedBytes[2] == 0x00 && receivedBytes[3] == 0x00 &&
                 receivedBytes[4] == 0x00 && receivedBytes[5] == 0xFF &&
                 receivedBytes[6] == 0xFF && receivedBytes[7] == 0xFF) {
        return true;
      } else {
        printf("Error!! Current state of DualStateButton is invalid @ %s : %d \n", __PRETTY_FUNCTION__, __LINE__ );
        return false;
      }
}