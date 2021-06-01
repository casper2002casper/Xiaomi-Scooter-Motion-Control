#include "Scooter.h"

void Scooter::update(uint8_t buff[])
{
    switch (getMsgType(buff))
    {
    case THROTTLE:
        currentSpeedKmu = readCurrentSpeed(buff);
        break;

    case BRAKE:
        currentBrakingPercentage = readCurrentBraking(buff);
        break;
    }
}

void Scooter::control()
{
    if(currentBrakingPercentage > 50){//Handle Brakes
        currentState = MAX_BRAKING;
    }
    else if(currentBrakingPercentage > 5){
        decreaseThrottle(currentBrakingPercentage);
    }

    switch (currentState)//Handle Kicks
    {
    case DETECTING:
        int kickingPercentage = analyseKickPercentage();
        if(currentSpeedKmu > 5 && kickingPercentage>20){//Conditions for boost
            setThrottle(kickingPercentage);
            boostEndTime = millis() + boostTime;
            currentState = BOOSTING;
        }
        else{
            idleThrottle();
        }
        break;

    case BOOSTING:
        if(millis()> boostEndTime || currentSpeedKmu > 25){
            idleThrottle();
            currentState = DETECTING;
        }
        break;

    case MAX_BRAKING:
        setThrottle(0);//ERS enabled
        if(currentBrakingPercentage < 30){
            currentState = DETECTING;
        }
        break;
    }
}

void Scooter::setThrottle(int percentage)
{
    percentage = max(0, min(100, percentage)); //Cap value
    currentThrottle = percentage;
    analogWrite(THROTTLE_PIN, percentage * 233);
}

void Scooter::decreaseThrottle(int percentage){
    setThrottle(currentThrottle - percentage);
}

int Scooter::analyseKickPercentage()//TODO
{
    if (currentSpeedKmu > averageSpeed)
    {
        return 80;
    }
    return 0;
}

bool Scooter::checkChecksum(uint8_t buff[])
{
    uint16_t sum = 0;
    int i = 0;
    while (buff[i + 2] != 0) //Last 2 bytes are crc so check past that
    {
        sum += buff[i++];
    }

    uint16_t checksum = (uint16_t)buff[i] | ((uint16_t)buff[i + 1] << 8);
    return checksum != (sum ^ 0xFFFF);
}
