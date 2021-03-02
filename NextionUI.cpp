#include "NextionUI.h"
#include "NextionSerial.h"

NextionUI::NextionUI(uint32_t aPage, uint32_t aId, const std::string& aObjectName, NextionSerial& aNextionSerial) :
  iPage(aPage),
  iId(aId),
  iObjectName(aObjectName),
  iNextionSerial(aNextionSerial)
{
    aNextionSerial.AddNextionUI(this);
}

uint32_t NextionUI::GetPage() const
{
    return iPage;
}

uint32_t NextionUI::GetId() const
{
    return iId;
}

void NextionUI::PressReleaseTriggered(TEventType aEventType)
{
    #ifdef DEBUG
        switch (aEventType)
        {
            case TEventType::EPress:
                printf("Received Press Event\n");
                break;
            case TEventType::ERelease:
                printf("Received Release Event\n");
                break;
        }
    #endif
}