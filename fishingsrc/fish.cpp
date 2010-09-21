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
    BAIT_DISTANCE_THRESHOLD=0.1;
    FACING_BAIT_THRESHOLD=0.3;
    BAIT_TURN_ANGEL=0.1;
    JUMPBACK_DISTANCE=0.1;
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
    {
        owner->triedTimes=0;
        owner->predateturn.activate();
    }
    //�������ǰ���޷�ǰ������ת����ת����
    if(owner->blocked())
        owner->swimturn.activate();
    //����е����ۣ���ת���λ��ж���
    if(owner->tired())//todo
        owner->swimslide.activate();
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
        owner->swimpadel.activate();
    //������е�·�Ķ����������ת��
}

void SwimSlide::activate()
{
    qDebug()<<"swimslide activated";
    owner->currentState=this;
    owner->noRudder=1;
}

void SwimSlide::run()
{
    if(owner->blocked())
        owner->swimturn.activate();
    if((!owner->tired())&&(owner->chance(0.1)||owner->speed==0))//where 0.1 is the possibility to change status to padel
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
    owner->noRudder=0;
}

void PredateTurn::run()
{
    float fb=owner->facingBait();
    if(fb<0)
        fb=-fb;
    if(fb<owner->FACING_BAIT_THRESHOLD)
    {
        qDebug()<<"YEAH now predate.";
        owner->predatepadel.activate();
        return;
    }
    //�������ת���ն�
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
    //���ϵ��ظ���ˮǰ����ֱ���ﵽ�ն�Ϊֹ
    owner->goAhead();
    //check current status
    if(!owner->baitAround())
        owner->swimpadel.activate();
    if(!owner->facingBait())
        owner->predateturn.activate();
    //qDebug()<<"distance: "<<owner->baitDistance()<<owner->speed;
    if(owner->baitDistance()<=owner->speed)//ʣ�µľ��벻��һ����
    {
        //qDebug()<<"now here"<<owner->triedTimes;
        if(++owner->triedTimes>3)//ʲôʱ��Ҫ���㣿
            owner->hooked();
        else
            owner->predatejumpback.activate();
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
    //���Ϻ��ˣ�ֱ����Զ�������ϰ�������ٶ�Ϊ0
    owner->goBack();
        //qDebug()<<owner->baitDistance()<<owner->JUMPBACK_DISTANCE;

    if(!owner->baitAround())
        owner->swimpadel.activate();
    if(!owner->facingBait())
        owner->predateturn.activate();
    if(owner->baitDistance()>owner->JUMPBACK_DISTANCE)
    {
        owner->predatepadel.activate();
    }
    if(owner->blocked())
        owner->predatepadel.activate();
    //if(owner->speed>0)
    //    owner->predatepadel.activate();
}

bool Fish::baitAround()
{
    //���������λ�ú��Լ����ĵľ��룬С�����߾����ʱ���򷵻�true
    return baitDistance()<BAIT_DISTANCE_THRESHOLD;
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

float Fish::facingBait()
{
    //�����Լ�������������֮��ļнǣ�С��ĳһ��ֵʱ����true
    float baitDir=atan((baitZ-posZ)/(baitX-posX));
    qDebug()<<"dirs: "<<baitDir<<dir<<baitZ<<posZ<<baitX<<posX;
    //verify that the baitdir and dir are in the same unit
    return baitDir-dir;
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
