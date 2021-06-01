class Scooter
{
protected:
    //Settings
    const int THROTTLE_PIN = 3;
    const int boostTime = 5000;

    //Scooter State
    enum State
    {
        DETECTING,
        BOOSTING,
        MAX_BRAKING
    };
    State currentState = State::DETECTING;
    int currentSpeedKmu = 0;
    int currentBrakingPercentage = 0;
    int currentThrottle = 0;

    int averageSpeed = 0;
    unsigned long boostEndTime = 0;
    //Handle throttle
    void setThrottle(int percentage);
    virtual void idleThrottle();
    //Analyse kicks
    int analyseKickPercentage();
    //Parse Serial
    bool checkChecksum(uint8_t buff[]);
    enum MsgType
    {
        THROTTLE,
        BRAKE,
        UNKNOWN
    };
    virtual MsgType getMsgType(uint8_t buff[]);
    virtual int readCurrentSpeed(uint8_t buff[]);
    virtual int readCurrentBraking(uint8_t buff[]);

public:
    void update(uint8_t buff[]);
    void control();
};
