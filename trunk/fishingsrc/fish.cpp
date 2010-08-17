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
    //���״̬�У�����д�ˮ�Ķ���
    if(owner->angel>0)
        owner->angel=-10;
    else
        owner->angel=10;
    owner->speed+=owner->acceleration;
    //���������ת�򣬲��������һЩ�������Դﵽ�۵�Ч��
    owner->goAhead();
    //��������������ת�벶ת����
    if(owner->baitAround())
        owner->predateturn.activate();
    //�������ǰ���޷�ǰ������ת����ת����
    if(owner->blocked())
        owner->swimturn.activate();
    //����е����ۣ���ת���λ��ж���
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
    //������е�·�Ķ����������ת��
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
    //����ʱ����Ҫ������ֻ����������ˮ���������٣����ָ�����
}

void PredateTurn::activate()
{
    owner->currentState=this;
}

void PredateTurn::run()
{
    if(owner->facingBait())
        owner->predatepadel.activate();
    //�������ת���ն�
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
        if(++owner->triedTimes>3)//ʲôʱ��Ҫ���㣿
            owner->hooked();
        else
            owner->predatejumpback.activate();
    //���ϵ��ظ���ˮǰ����ֱ���ﵽ�ն�Ϊֹ
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
    //���Ϻ��ˣ�ֱ����Զ�������ϰ�������ٶ�Ϊ0
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
