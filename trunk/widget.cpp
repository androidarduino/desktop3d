#include "widget.h"
#include "ui_widget.h"

#include "widget.h"

GLWidget::GLWidget(QWidget *parent)
     : QGLWidget(parent)
 {
     object = 0;
     xRot = 0;
     yRot = 0;
     zRot = 0;

     trolltechGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
     trolltechPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
 }

GLWidget::~GLWidget()
 {
     makeCurrent();
     glDeleteLists(object, 1);
 }

 QSize GLWidget::minimumSizeHint() const
 {
     return QSize(50, 50);
 }

 QSize GLWidget::sizeHint() const
 {
     return QSize(400, 400);
 }

 void GLWidget::setXRotation(int angle)
 {
     normalizeAngle(&angle);
     if (angle != xRot) {
         xRot = angle;
         emit xRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::setYRotation(int angle)
 {
     normalizeAngle(&angle);
     if (angle != yRot) {
         yRot = angle;
         emit yRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::setZRotation(int angle)
 {
     normalizeAngle(&angle);
     if (angle != zRot) {
         zRot = angle;
         emit zRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::initializeGL()
 {
     qglClearColor(QColor::fromRgb(128,128,128));
     object = makeObject();
     glShadeModel(GL_FLAT);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     timer=new QTimer();
     timer->setInterval(1000);
     connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
     timer->start();
 }

 void GLWidget::paintGL()
 {
     //clearMask();
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     glTranslated(0.0, 0.0, -10.0);
     glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
     glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
     glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
     glCallList(object);
     makeArrows();
     qDebug()<<"paintGL";     
 }
void GLWidget::mouseReleaseEvent ( QMouseEvent * event )
{
     QImage img=grabFrameBuffer();
     mask=QBitmap::fromImage(img.createMaskFromColor(img.pixel(QPoint(10,10)),Qt::MaskInColor));
     //img.save("buffer.bmp");
     //mask.save("mask.bmp");
     //qDebug()<<"mask created";
     setMask(mask);
 }
void GLWidget::refresh()
{
    qDebug()<<"refreshed";
    update();
}

 void GLWidget::resizeGL(int width, int height)
 {

     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);
     glMatrixMode(GL_MODELVIEW);
     qDebug()<<"resizeGL";
 }

 void GLWidget::mousePressEvent(QMouseEvent *event)
 {
     clearMask();
     lastPos = event->pos();
 }

 void GLWidget::mouseMoveEvent(QMouseEvent *event)
 {
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

     if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot + 8 * dy);
         setYRotation(yRot + 8 * dx);
     } else if (event->buttons() & Qt::RightButton) {
         //setXRotation(xRot + 8 * dy);
         //setZRotation(zRot + 8 * dx);
         move(pos().x()+dx, pos().y()+dy);
         //not perfect yet.
     }
     lastPos = event->pos();
 }

 GLuint GLWidget::makeObject()
 {
     GLuint list = glGenLists(1);
     glNewList(list, GL_COMPILE);

     glBegin(GL_QUADS);

     const double Pi = 3.14159265358979323846;
     const int NumSectors = 60;

     for (int i = 0; i < NumSectors; ++i) {
         double angle1 = (i * 2 * Pi) / NumSectors;
         GLdouble x5 = 0.30 * sin(angle1);
         GLdouble y5 = 0.30 * cos(angle1);
         GLdouble x6 = 0.25 * sin(angle1);
         GLdouble y6 = 0.25 * cos(angle1);

         double angle2 = ((i + 1) * 2 * Pi) / NumSectors;
         GLdouble x7 = 0.25 * sin(angle2);
         GLdouble y7 = 0.25 * cos(angle2);
         GLdouble x8 = 0.30 * sin(angle2);
         GLdouble y8 = 0.30 * cos(angle2);


         quad(x5, y5, x6, y6, x7, y7, x8, y8,0);
/*         qglColor(QColor::fromRgb(255,255,255));

     glVertex3d(x8, y8, -0.049);
     glVertex3d(0, 0, -0.049);
     glVertex3d(x6, y6, -0.049);
     glVertex3d(x5, y5, -0.049);*/
         qglColor(trolltechGreen);
     glVertex3d(x5, y5, -0.05);
     glVertex3d(x6, y6, -0.05);
     glVertex3d(0, 0, -0.05);
     glVertex3d(x8, y8, -0.05);



         extrude(x6, y6, x7, y7);
         extrude(x8, y8, x5, y5);
     }

     glEnd();
     draw_circle(0.25,60);
     glEndList();
     return list;
 }
 void GLWidget::makeArrows()
 {
     glBegin(GL_QUADS);
     const double Pi = 3.14159265358979323846;
     const double secArmLen=0.18;
     const double minArmLen=0.15;
     const double hrArmLen=0.10;
     QTime time = QTime::currentTime();
     quad(-0.01,0.01,-0.01,-0.01,hrArmLen,-0.01,hrArmLen,0.01,Pi/6 * ((time.hour() + time.minute() / 60.0))-Pi/2);
     quad(-0.01,0.01,-0.01,-0.01,minArmLen,-0.01,minArmLen,0.01,Pi/30 * (time.minute() + time.second() / 60.0)-Pi/2);
     quad(-0.01,0.0025,-0.01,-0.0025,secArmLen,-0.0025,secArmLen,0.0025,Pi/30 * time.second()-Pi/2);
     glEnd();
 }

 void GLWidget::quad(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2,
                     GLdouble x3, GLdouble y3, GLdouble x4, GLdouble y4,
                     double angle)
 {
     if(angle!=0)
     {
         double r,a;
         r=sqrt(x1*x1+y1*y1);
         a=asin(y1/r)+angle;
         x1=r*cos(a);
         y1=r*sin(a);
         r=sqrt(x2*x2+y2*y2);
         a=asin(y2/r)+angle;
         x2=r*cos(a);
         y2=r*sin(a);
         r=sqrt(x3*x3+y3*y3);
         a=asin(y3/r)+angle;
         x3=r*cos(a);
         y3=r*sin(a);
         r=sqrt(x4*x4+y4*y4);
         a=asin(y4/r)+angle;
         x4=r*cos(a);
         y4=r*sin(a);
     }
     qglColor(trolltechGreen);

     glVertex3d(x1, y1, -0.05);
     glVertex3d(x2, y2, -0.05);
     glVertex3d(x3, y3, -0.05);
     glVertex3d(x4, y4, -0.05);
//back color here
     glVertex3d(x4, y4, +0.05);
     glVertex3d(x3, y3, +0.05);
     glVertex3d(x2, y2, +0.05);
     glVertex3d(x1, y1, +0.05);
 }

 void GLWidget::extrude(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
 {
     qglColor(trolltechGreen.dark(250 + int(100 * x1)));

     glVertex3d(x1, y1, +0.05);
     glVertex3d(x2, y2, +0.05);
     glVertex3d(x2, y2, -0.05);
     glVertex3d(x1, y1, -0.05);
 }

 void GLWidget::normalizeAngle(int *angle)
 {
     while (*angle < 0)
         *angle += 360 * 16;
     while (*angle > 360 * 16)
         *angle -= 360 * 16;
 }
 void GLWidget::draw_circle(const GLfloat radius,const GLuint num_vertex)
 {
     GLuint texture=bindTexture(QPixmap("test.jpg"), GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, texture);
     GLfloat vertex[4];
     GLfloat texcoord[2];
     const GLfloat delta_angle = 2.0*M_PI/num_vertex;
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D,texture);
     glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
     glBegin(GL_TRIANGLE_FAN);
    //draw the vertex at the center of the circle
     texcoord[0] = 0.5;
     texcoord[1] = 0.5;
     glTexCoord2fv(texcoord);
     vertex[0] = vertex[1] = vertex[2] = 0.0;
     vertex[3] = 1.0;
     glVertex4fv(vertex);
     //draw the vertex on the contour of the circle
     for(int i = 0; i < num_vertex ; i++)
     {
        texcoord[1] = (cos(delta_angle*i) + 1.0)*0.5;
        texcoord[0
                 ] = (sin(delta_angle*i) + 1.0)*0.5;
        glTexCoord2fv(texcoord);
        vertex[1] = cos(delta_angle*i) * radius;
        vertex[0] = sin(delta_angle*i) * radius;
        vertex[2] = 0.0;
        vertex[3] = 1.0;
        glVertex4fv(vertex);
     }
     texcoord[1] = (1.0 + 1.0)*0.5;
     texcoord[0] = (0.0 + 1.0)*0.5;
     glTexCoord2fv(texcoord);
     vertex[1] = 1.0 * radius;
     vertex[0] = 0.0 * radius;
     vertex[2] = 0.0;
     vertex[3] = 1.0;
     glVertex4fv(vertex);
     glEnd();
     glDisable(GL_TEXTURE_2D);
  }
