#include "Scooter.h"

class XiaomiScooter : public Scooter
{
protected:
    void idleThrottle();
    Scooter::MsgType getMsgType(uint8_t buff[]);
    int readCurrentSpeed(uint8_t buff[]);
    int readCurrentBraking(uint8_t buff[]);
};
