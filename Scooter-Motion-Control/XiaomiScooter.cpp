#include "XiaomiScooter.h"

void XiaomiScooter::idleThrottle()
{
    setThrottle(35); //idle
}

Scooter::MsgType XiaomiScooter::getMsgType(uint8_t buff[])
{
    switch (buff[1])
    {
    case 0x20:
        switch (buff[2])
        {
        case 0x65:
            return BRAKE;
        }
    case 0x21:
        switch (buff[2])
        {
        case 0x64:
            return THROTTLE;
        }
    }
    return UNKNOWN;
}
int XiaomiScooter::readCurrentSpeed(uint8_t buff[])
{
    return buff[8];
}
int XiaomiScooter::readCurrentBraking(uint8_t buff[])
{
    return buff[6];
}
