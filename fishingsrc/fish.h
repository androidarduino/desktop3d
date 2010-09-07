#ifndef FISH_H
#define FISH_H
#include "thing.h"
#include <time.h>
#include <QTimer>
//by liu
class Fish;

class State
{
    public:
        Fish* owner;
        State(){}
        virtual void run(){}
        virtual void activate(){}
};

class SwimPadel:public State
{
    public:
        SwimPadel(){}
        void run();
        void activate();
};
class SwimTurn:public State
{
    public:
        SwimTurn(){}
        void run();
        void activate();
};
class SwimSlide:public State
{
    public:
        SwimSlide(){}
        void run();
        void activate();
};
class PredateTurn:public State
{
    public:
        PredateTurn(){}
        void run();
        void activate();
};
class PredatePadel:public State
{
    public:
        PredatePadel(){}
        void run();
        void activate();
};
class PredateJumpBack:public State
{
    public:
        PredateJumpBack(){}
        void run();
        void activate();
};
class ScaredPadel:public State
{
    public:
        ScaredPadel(){}
        void run(){}
        void activate(){}
};

class Fish: public Thing
{
    Q_OBJECT
public:
    Fish(QString pic, float w, float h);
    virtual void draw();
public:
    //states
    State* currentState;
    SwimPadel swimpadel;
    SwimTurn swimturn;
    SwimSlide swimslide;
    PredateTurn predateturn;
    PredatePadel predatepadel;
    PredateJumpBack predatejumpback;
    ScaredPadel scaredpadel;
    Thing* bait;
public:
    //helper functions
    bool tired();
    bool baitAround();
    bool blocked();
    void hooked();
    float facingBait();
    float baitDistance();
    float swingAngel(){return angel;}
    void goAhead();
    bool chance(float percent);
    //status variables
    float speed, acceleration, resistance;
    float rudder, angel;
    int triedTimes;
    float strength;
    float MAX_SPEED, BAIT_DISTANCE_THRESHOLD, FACING_BAIT_THRESHOLD, BAIT_TURN_ANGEL, JUMPBACK_DISTANCE;
private:
    QTimer timer;
private slots:
    void timeOut();
};

#endif // FISH_H
