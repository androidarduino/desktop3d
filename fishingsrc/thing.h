#ifndef THING_H
#define THING_H
#include <QPixmap>
#include <QGLWidget>
#include <QDebug>
#include <math.h>

class Scene;
class Thing: public QGLWidget
{
public:
    Thing(QString pic, float w, float h);
    virtual void draw();
    virtual void init();
    void putTo(float x, float y, float z);
    void rotate(float x, float y, float z);
    float posX, posY, posZ, rotX, rotY, rotZ;
    Scene* container;
protected:
    QPixmap* picture;
    GLuint texture;
    float picWidth, picHeight;
    double curX, curY, dir;
    virtual float swingAngel(){return 0.0;}
};

#endif // THING_H
