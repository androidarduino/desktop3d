#ifndef ROD_H
#define ROD_H
#include "thing.h"

class Bait: public Thing
{
public:
    Bait(QString bt="white bait");
    QString baitType;
private:

};

class Rod
{
public:
    Rod();
private:
    //line;
};

#endif // ROD_H
