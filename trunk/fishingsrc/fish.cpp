#include "fish.h"
#include <QDebug>
Fish::Fish(QString pic, float w, float h):Thing(pic,w,h)
{
    rotate(90,0,0);
    swimpadel.owner=swimturn.owner=swimslide.owner=predateturn.owner=predatepadel.owner=predatejumpback.owner=scaredpadel.owner=this;
    swimpadel.activate();
    acceleration=0.002;
    rudder=0.1;
    speed=0;
    dir=3.14/6;
    timer.setInterval(200);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeOut()));
}

void Fish::timeOut()
{
    this->currentState->run();
}

void Fish::draw()
{
    Thing::draw();
}

void Fish::goAhead()
{
    dir+=rudder;
    posZ-=speed*sin(dir);
    posX-=speed*cos(dir);
}

void SwimPadel::activate()
{
    owner->currentState=this;
}

void SwimPadel::run()
{
    //这个状态中，鱼进行打水的动作
    if(owner->angel>0)
        owner->angel=-10;
    else
        owner->angel=10;
    owner->speed+=owner->acceleration;
    //在这里随机转向，并随机消耗一些力气，以达到累的效果
    owner->goAhead();
    //如果发现鱼饵，则转入捕转向动作
    if(owner->baitAround())
        owner->predateturn.activate();
    //如果发现前方无法前进，则转向游转向动作
    if(owner->blocked())
        owner->swimturn.activate();
    //如果感到劳累，则转入游滑行动作
    if(owner->tired())
        owner->swimslide.activate();
}

void SwimTurn::activate()
{
    owner->currentState=this;
}

void SwimTurn::run()
{
    if(!owner->blocked())
        owner->swimpadel.activate();
    //如果仍有挡路的东西，则继续转向
}

void SwimSlide::activate()
{
    owner->currentState=this;
}

void SwimSlide::run()
{
    if(owner->blocked())
        owner->swimturn.activate();
    if(!owner->tired())
        owner->swimpadel.activate();
    if(owner->baitAround())
        owner->predateturn.activate();
    //滑动时不需要动作，只是慢慢根据水的阻力减速，并恢复体力
}

void PredateTurn::activate()
{
    owner->currentState=this;
}

void PredateTurn::run()
{
    if(owner->facingBait())
        owner->predatepadel.activate();
    //否则继续转向诱饵
}

void PredatePadel::activate()
{
    owner->currentState=this;
}

void PredatePadel::run()
{
    if(!owner->baitAround())
        owner->swimpadel.activate();
    if(!owner->facingBait())
        owner->predateturn.activate();
    if(owner->baitDistance()<=0)
        if(++owner->triedTimes>3)//什么时候要清零？
            owner->hooked();
        else
            owner->predatejumpback.activate();
    //不断地重复打水前进，直到达到诱饵为止
}

void PredateJumpBack::activate()
{
    owner->currentState=this;
}

void PredateJumpBack::run()
{
    if(!owner->baitAround())
        owner->swimpadel.activate();
    if(!owner->facingBait())
        owner->predateturn.activate();
    if(owner->baitDistance()>JUMPBACK_DISTANCE)
        owner->predatepadel.activate();
    if(owner->blocked())
        owner->predatepadel.activate();
    if(owner->speed>0)
        owner->predatepadel.activate();
    //不断后退，直到够远，碰到障碍物或者速度为0
}

bool Fish::baitAround()
{
    return false;
}

bool Fish::blocked()
{
    return false;
}

bool Fish::tired()
{
    return false;
}

bool Fish::facingBait()
{
    return false;
}
