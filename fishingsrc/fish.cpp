#include "fish.h"
#include <QDebug>
Fish::Fish(QString pic, float w, float h):Thing(pic,w,h)
{
    rotate(90,0,0);
    swimpadel.owner=swimturn.owner=swimslide.owner=predateturn.owner=predatepadel.owner=predatejumpback.owner=scaredpadel.owner=this;
    swimpadel.activate();
    acceleration=0.002;
    resistance=0.001;
    strength=10;
    rudder=5;
    noRudder=1;
    speed=0;
    MAX_SPEED=0.05;
    BAIT_DISTANCE_THRESHOLD=0.15;
    FACING_BAIT_THRESHOLD=0.1;
    BAIT_TURN_ANGEL=0.1;
    JUMPBACK_DISTANCE=0.08;
    dir=3.14/6;
    timer.setInterval(200);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeOut()));
}

void Fish::setBait(Thing& b)
{
    baitX=b.posX;
    baitZ=b.posZ;
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
    dir+=rudder*speed*noRudder;
    posZ-=speed*sin(dir);
    posX-=speed*cos(dir);
}

void Fish::goBack()
{
    dir+=rudder*speed*noRudder;
    posZ+=speed*sin(dir);
    posX+=speed*cos(dir);
}

void SwimPadel::activate()
{
    qDebug()<<"swim padel activated.";
    owner->currentState=this;
    owner->noRudder=1;
}

void SwimPadel::run()
{
    //qDebug()<<"swimpadel running"<<owner->baitAround();
    //这个状态中，鱼进行打水的动作
    if(owner->angel>0)
        owner->angel=-10;
    else
        owner->angel=10;
    owner->speed+=owner->acceleration*(1-owner->speed/owner->MAX_SPEED);
    //在这里随机转向，并随机消耗一些力气，以达到累的效果
    owner->strength--;//add random flavour later
    owner->goAhead();
    //如果发现鱼饵，则转入捕转向动作
    if(owner->baitAround())
    {
        owner->triedTimes=0;
        qDebug()<<"bait found, change to predate turn";
        owner->predateturn.activate();
    }
    //如果发现前方无法前进，则转向游转向动作
    if(owner->blocked())
    {
        qDebug()<<"way blocked, change to swim turn";
        owner->swimturn.activate();
    }
    //如果感到劳累，则转入游滑行动作
    if(owner->tired())//todo
    {
        qDebug()<<"tired, change to swim slide";
        owner->swimslide.activate();
    }
}

void SwimTurn::activate()
{
    qDebug()<<"swimturn activated";
    owner->currentState=this;
    owner->noRudder=1;
    //randomly choose a turn direction, and modify rudder accordingly
}

void SwimTurn::run()
{
    if(!owner->blocked())
    {
        qDebug()<<"block disappeared, change to swim padel";
        owner->swimpadel.activate();
    }
    //如果仍有挡路的东西，则继续转向
}

void SwimSlide::activate()
{
//    qDebug()<<"swimslide activated";
    owner->currentState=this;
    owner->noRudder=1;
}

void SwimSlide::run()
{
    if(owner->blocked())
    {
        qDebug()<<"way blocked, change to swim turn";
        owner->swimturn.activate();
    }
    if((!owner->tired())&&(owner->chance(0.1)||owner->speed==0))//where 0.1 is the possibility to change status to padel
    {
        owner->swimpadel.activate();
        qDebug()<<"tired, or randomly change to swim padel";
    }
    if(owner->baitAround())
    {
        qDebug()<<"found bait, change to predate turn";
        owner->predateturn.activate();
    }
    owner->speed-=owner->resistance;
    if(owner->speed<0)
        owner->speed=0;
    owner->strength++;//add random flavour later
    if(owner->strength>10)//ceil of strength
        owner->strength=10;
    owner->goAhead();
    //滑动时不需要动作，只是慢慢根据水的阻力减速，并恢复体力
}

void PredateTurn::activate()
{
    qDebug()<<"predate turn activated.";
    owner->currentState=this;
    owner->noRudder=0;
}

void PredateTurn::run()
{
    float fb=owner->facingBait();
    if(fb<0)
        fb=-fb;
    if(fb<owner->FACING_BAIT_THRESHOLD)
    {
        qDebug()<<"facing bait now, start to predate padel.";
        owner->predatepadel.activate();
        return;
    }
    //否则继续转向诱饵
    if(owner->facingBait()>0)
        owner->turn(owner->BAIT_TURN_ANGEL);
    else
        owner->turn(-owner->BAIT_TURN_ANGEL);
}

void Fish::turn(float a)
{
    dir+=a;
}

void PredatePadel::activate()
{
    qDebug()<<"predate padel activated.";
    owner->currentState=this;
    owner->noRudder=0;
}

void PredatePadel::run()
{
    //不断地重复打水前进，直到达到诱饵为止
    owner->goAhead();
    //check current status
    if(!owner->baitAround())
    {
        qDebug()<<"bait lost, change back to swim padel";
        owner->swimpadel.activate();
    }
    if(!owner->facingBait())
    {
        qDebug()<<"bait around but not facing, change to predate turn";
        owner->predateturn.activate();
    }
    //qDebug()<<"distance: "<<owner->baitDistance()<<owner->speed;
    if(owner->baitDistance()<=owner->speed)//剩下的距离不够一步的
    {
        //qDebug()<<"now here"<<owner->triedTimes;
        if(++owner->triedTimes>=3)//什么时候要清零？
        {
            qDebug()<<"tried enough, now eat it";
            owner->hooked();
        }
        else
        {
            owner->predatejumpback.activate();
            qDebug()<<"try one more time";
        }
    }
}

void PredateJumpBack::activate()
{
    qDebug()<<"predate jump back activated.";
    owner->currentState=this;
    owner->noRudder=0;
}

void PredateJumpBack::run()
{
    //不断后退，直到够远，碰到障碍物或者速度为0
    owner->goBack();
        //qDebug()<<owner->baitDistance()<<owner->JUMPBACK_DISTANCE;

    if(!owner->baitAround())
    {
        owner->swimpadel.activate();
        qDebug()<<"bait lost, go back to swim padel";
    }
    if(!owner->facingBait())
    {
        qDebug()<<"not facing bait, change to predate turn";
        owner->predateturn.activate();
    }
    if(owner->baitDistance()>owner->JUMPBACK_DISTANCE)
    {
        qDebug()<<"bait distance long enough, now predate ahead.";
        owner->predatepadel.activate();
    }
    if(owner->blocked())
    {
        qDebug()<<"way blocked, can't jump back, change to predate ahead";
        owner->predatepadel.activate();
    }
    //if(owner->speed>0)
    //    owner->predatepadel.activate();
}

bool Fish::baitAround()
{
    //计算鱼饵的位置和自己中心的距离，小于视线距离的时候则返回true
    return baitDistance()<BAIT_DISTANCE_THRESHOLD;
}

bool Fish::blocked()
{
    //查看前方是否可以走，如果不可走则返回true
    return false;
}

bool Fish::tired()
{
    return strength<1;
}

float Fish::facingBait()
{
    //计算自己朝向和鱼饵方向之间的夹角，小于某一阈值时返回true
    double baitDir=atan((baitZ-posZ)/(baitX-posX));
//    qDebug()<<"dirs: "<<baitDir<<dir<<baitZ<<posZ<<baitX<<posX;
    //verify that the baitdir and dir are in the same unit
    //baitDir+=3.1416/2;
    float d=dir;
    while(d>3.14)
        d-=6.28;
    qDebug()<<"==========="<<baitDir<<dir<<d;
    return baitDir-d;
}

float Fish::baitDistance()
{
    float d=baitZ-posZ;
    float distance2=d*d;
    d=baitX-posX;
    distance2+=d*d;
    //qDebug()<<sqrt(distance2);
    return sqrt(distance2);
}

void Fish::hooked()
{

}

bool Fish::chance(float percent)
{
    srand((unsigned)time(0));
    int rnd=rand()%1000;
    //qDebug()<<rnd<<percent*1000<<(rnd<percent*1000);
    return rnd<percent*1000;
}
