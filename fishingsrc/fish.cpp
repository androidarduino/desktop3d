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
    speed=0;
    MAX_SPEED=0.5;
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
    dir+=rudder*speed;
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
    owner->speed+=owner->acceleration*(1-owner->speed/owner->MAX_SPEED);
    //���������ת�򣬲��������һЩ�������Դﵽ�۵�Ч��
    owner->strength--;//add random flavour later
    owner->goAhead();
    //��������������ת�벶ת����
    if(owner->baitAround())
        owner->predateturn.activate();
    //�������ǰ���޷�ǰ������ת����ת����
    if(owner->blocked())
        owner->swimturn.activate();
    //����е����ۣ���ת���λ��ж���
    if(owner->tired())//todo
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
    if((!owner->tired())&&(owner->chance(0.1)||owner->speed==0))//where 3% is the possibility to change status to padel
        owner->swimpadel.activate();
    if(owner->baitAround())
        owner->predateturn.activate();
    owner->speed-=owner->resistance;
    if(owner->speed<0)
        owner->speed=0;
    owner->strength++;//add random flavour later
    if(owner->strength>10)//ceil of strength
        owner->strength=10;
    owner->goAhead();
    //����ʱ����Ҫ������ֻ����������ˮ���������٣����ָ�����
}

void PredateTurn::activate()
{
    qDebug()<<"predate turn activated.";
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
    qDebug()<<"predate padel activated.";
    owner->currentState=this;
}

void PredatePadel::run()
{
    if(!owner->baitAround())
        owner->swimpadel.activate();
    if(!owner->facingBait())
        owner->predateturn.activate();
    if(owner->baitDistance()<=speed)//ʣ�µľ��벻��һ����
    {
        if(++owner->triedTimes>3)//ʲôʱ��Ҫ���㣿
            owner->hooked();
        else
            owner->predatejumpback.activate();
    }
    //���ϵ��ظ���ˮǰ����ֱ���ﵽ�ն�Ϊֹ
}

void PredateJumpBack::activate()
{
    qDebug()<<"predate jump back activated.";
    owner->currentState=this;
}

void PredateJumpBack::run()
{
    float JUMPBACK_DISTANCE=0.1;
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
    //���������λ�ú��Լ����ĵľ��룬С�����߾����ʱ���򷵻�true
    return false;
}

bool Fish::blocked()
{
    //�鿴ǰ���Ƿ�����ߣ�����������򷵻�true
    return false;
}

bool Fish::tired()
{
    return strength<1;
}

bool Fish::facingBait()
{
    //�����Լ�������������֮��ļнǣ�С��ĳһ��ֵʱ����true
    return false;
}

float Fish::baitDistance()
{
    return 1.0;
}

void Fish::hooked()
{

}

bool Fish::chance(float percent)
{
    //srand((unsigned)time(0));
    int rnd=rand()%1000;
    qDebug()<<rnd<<percent*1000<<(rnd<percent*1000);
    return rnd<percent*1000;
}
