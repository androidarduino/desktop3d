#ifndef SCENE_H
#define SCENE_H

#include "thing.h"
#include <QMouseEvent>
#include <QTimer>

class Scene : public QGLWidget
{
    Q_OBJECT

public:
    Scene(QWidget *parent = 0);
    ~Scene();
    void add(Thing* thing);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QList<Thing*> objects;
    //the following are fixed things
    Thing* tree1, *tree2, *tree3;
    Thing* grass1, *grass2;
    Thing* ground, *sky, *surface;
    QPoint lastPos;
    float rotX, rotZ;
    QTimer timer;
};

#endif // SCENE_H
