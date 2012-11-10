#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <irrlicht/irrlicht.h>

using namespace irr;

class EventReceiver : public IEventReceiver
{
public:

    EventReceiver(IrrlichtDevice* indevice):device(indevice) {}

    bool OnEvent(const SEvent& event)
    {

        if (event.EventType == EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
        {
            switch (event.KeyInput.Key)
            {
                //On escape, close
            case irr::KEY_ESCAPE:
                device->drop();
                break;
            default:
                break;
            }
        }

        return false;
    }

private:
    IrrlichtDevice* device;
};

#endif // EVENTRECEIVER_H
