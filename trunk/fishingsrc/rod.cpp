#include "rod.h"

Rod::Rod()
{
}

Bait::Bait(QString bt):Thing(":/smallfry.png", 0.05, 0.05)
{
    this->posY=0.21;
    baitType=bt;
    rotate(90,0,0);
}
