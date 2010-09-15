#include "scene.h"

Scene::Scene(QWidget *parent)
    : QGLWidget(parent)
{
    setMouseTracking(true);
    rotX=rotZ=0;
    timer.setInterval(20);
    connect(&timer, SIGNAL(timeout()),this,SLOT(update()));
    timer.start();
}

Scene::~Scene()
{

}

 void Scene::initializeGL()
 {
     qglClearColor(Qt::white);
     glShadeModel(GL_FLAT);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     glEnable(GL_TEXTURE_2D);
     glEnable(GL_BLEND);
     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     foreach(Thing* t, objects)
         t->init();
 }

void Scene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -20.0);
    glRotatef(rotX+15,1,0,0);
    glRotatef(rotZ,0,0,1);

    foreach(Thing* t, objects)
    {
        glPushMatrix();
        glScalef(8,8,8);
        glRotatef(180,0,-0.3,1);
        t->draw();
        glPopMatrix();
    }

}

 void Scene::resizeGL(int width, int height)
 {
     int side = qMin(width, height);
     //glViewport((width - side) / 2, (height - side) / 2, side, side);
     glViewport(0,0,width,height);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     //glOrtho(-1, 1, 1, -1, 4.0, 15.0);
//     qDebug()<<width<<height<<width/height;
     gluPerspective(60,((float)width)/height,1,1000);
     glMatrixMode(GL_MODELVIEW);
 }

 void Scene::add(Thing* thing)
 {
     objects<<thing;
     thing->container=this;
 }

void Scene::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    //QApplication::processEvents();
    if (event->buttons() & Qt::LeftButton)
    {
        rotX += dy;
        rotZ += dx;
    }
    lastPos = event->pos();
    update();
}


