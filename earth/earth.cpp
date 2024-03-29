#include "widget.h"
/*
todo:
1. 
*/

void Earth::initializeGL()
{
    DesktopGadget::initializeGL();
    GLfloat fogColor[4] = {0.5f,0.5f,0.5f,1.0f};   // Fog Color
    glFogi(GL_FOG_MODE, GL_LINEAR);                // Fog Mode: GL_EXP, GL_EXP2, GL_LINEAR
    glFogfv(GL_FOG_COLOR, fogColor);               // Set Fog Color
    glFogf(GL_FOG_DENSITY, 0.5f);                 // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);             // Fog Hint Value
    glFogf(GL_FOG_START, 1.0f);                    // Fog Start Depth
    glFogf(GL_FOG_END, 5.0f);                      // Fog End Depth
    //    glEnable(GL_FOG);                              // Enables GL_FOG

    GLfloat ambientLight[]={1,1,1,1};
    GLfloat diffuseLight[]={.5,.5,.5,1};
    glLightfv(GL_LIGHT0,GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuseLight);
    //GLfloat lightPos[]={2,2,2,0};
    //glLightfv(GL_LIGHT0,GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);

    cities<<"Lodon"<<"Paris"<<"Helsinki"<<"Moscow"<<"Kabul"<<"New Deli";
    cities<<"Dhakar"<<"Bankok"<<"Beijing"<<"Tokyo"<<"Sydney"<<"Solomon Island";
    cities<<"Aukland"<<"Midway Island"<<"Hawaii"<<"Alaska"<<"Seattle"<<"Denver";
    cities<<"Mexico City"<<"New York"<<"Caracas"<<"Brasilia"<<"Mid Atlantic"<<"Cape Verd"<<"Lodon";

    setAutoFillBackground(false);

    text=QPixmap("board.png");
    timer=new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(refresh()));
    timer->start(1000);
    count=59;
    refresh();
}

void Earth::createObjects()
{

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    GLUquadricObj *quadratic;               // Storage For Our Quadratic Objects ( NEW )
    quadratic=gluNewQuadric();          // Create A Pointer To The Quadric Object ( NEW )
    gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals ( NEW )
    gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords ( NEW )
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable ( GL_TEXTURE_2D );
    glBindTexture ( GL_TEXTURE_2D, earthTexture);
    glRotatef(-90,1,0,0);
    gluSphere(quadratic, 0.9, 36, 72);
    glRotatef(90,1,0,0);
    drawText();
}

void Earth::refresh()
{
    if(++count!=60)
    {
        paintGL();
        return;
    }
    count=0;
    QPixmap& pic=createSurface();
    earthTexture=bindTexture(pic, GL_TEXTURE_2D);
    delete &pic;
    glBindTexture(GL_TEXTURE_2D, earthTexture);
    paintGL();
}

void Earth::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    QApplication::processEvents();
    if (event->buttons() & Qt::LeftButton) {
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        move(pos().x()+dx, pos().y()+dy);
        //not perfect yet.
    }
    lastPos = event->pos();
}

void Earth::drawText()
{
    int timezone=yRot/(16*15);
    QString city=cities[24-timezone];
    if(timezone>12)
        timezone-=24;

    QPixmap board(text);
    QPainter painter(&board);
    QDateTime datetime=QDateTime::currentDateTimeUtc();
    datetime=datetime.addSecs(-timezone*3600);
    QString info=QString("%1\n%2\nUTC-%3").arg(city).arg(datetime.time().toString()).arg(timezone);
    painter.setPen(Qt::blue);
    painter.drawText(4,4, 88, 40, Qt::AlignJustify|Qt::AlignHCenter, info);
    painter.end();
    textTexture=bindTexture(board, GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textTexture);
    glPushMatrix();
    //not rotating y with the globe
    glRotated(-yRot / 16.0, 0.0, 1.0, 0.0);
    glTranslatef(-1,1,0);
    glScalef(0.5,0.5,0.5);
    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,1.0f);			// Set The Color To white
    glTexCoord2d(1,1);
    glVertex3f( 0.8f, 0.4f, 0);		// Top Right Of The Quad (Front)
    glTexCoord2d(0,1);
    glVertex3f(-0.8f, 0.4f, 0);		// Top Left Of The Quad (Front)
    glTexCoord2d(0,0);
    glVertex3f(-0.8f,-0.4f, 0);		// Bottom Left Of The Quad (Front)
    glTexCoord2d(1,0);
    glVertex3f( 0.8f,-0.4f, 0);		// Bottom Right Of The Quad (Front)
    glColor3f(1,1,1);
    glEnd();
    glPopMatrix();
}

QPixmap& Earth::createSurface()
{
    QDateTime time=QDateTime::currentDateTimeUtc();
    int utcMinutes=time.time().hour()*60+time.time().minute();
    //calculate the rect based on the utcMinutes
    //utc=[0-1440]
    int x=2048-(2048/60/24*utcMinutes)+1650;//split line
    if(x>2048)
        x-=2048;
    int x1=x+1024;
    if(x1>2048)
        x1-=2048;
    QRect rect1,rect2;
    if(x<x1)
    {
        rect1.setRect(0,0,x,1024);
        rect2.setRect(x1,0,2048-x1,1024);
    }
    if(x>x1)
    {
        rect1.setRect(x1,0,x-x1,1024);
        rect2.setRect(0,0,0,0);
    }
    QPixmap* day=new QPixmap("earth.png");
    QPixmap night("night.png");
    QPainter painter(day);
    painter.drawPixmap(rect1, night, rect1);
    painter.drawPixmap(rect2, night, rect1);
    return *day;
}
