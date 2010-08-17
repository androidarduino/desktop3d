#include "thing.h"
#include "scene.h"

Thing::Thing(QString pic, float w, float h)
{
    //load the picture and make texture with it
    picture=new QPixmap(pic);
    picWidth=w;
    picHeight=h;
    rotX=rotY=rotZ=posX=posY=posZ=curX=curY=dir=0;
}

void Thing::init()
{
    texture = bindTexture(*picture, GL_TEXTURE_2D);
}

void Thing::draw()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(posX,posY,posZ);
    glRotatef(rotX,1,0,0);
    glRotatef(rotY,0,1,0);
    glRotatef(rotZ,0,0,1);
    glTranslatef(curX,curY,0);//very difficult, how to remember the new position?
    glRotatef(dir*180/3.1416+swingAngel(),0,0,1);
    glBegin(GL_QUADS);
    //glColor4f(1,1,1,0.5);
    glTexCoord2d(0,0);
    glVertex3f(-picWidth/2,picHeight/2,0);
    glTexCoord2d(0,1);
    glVertex3f(-picWidth/2,-picHeight/2,0);
    glTexCoord2d(1,1);
    glVertex3f(picWidth/2,-picHeight/2,0);
    glTexCoord2d(1,0);
    glVertex3f(picWidth/2,picHeight/2,0);
    glEnd();
}

void Thing::putTo(float x, float y, float z)
{
    posX=-x;
    posY=-y;
    posZ=-z;
}

void Thing::rotate(float x, float y, float z)
{
    rotX=x;
    rotY=y;
    rotZ=z;
}
