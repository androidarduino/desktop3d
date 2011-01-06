#include "widget.h"
void DesktopGadget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}
DesktopGadget::DesktopGadget(QWidget *parent):QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    d_transparent=1;
    //createObjects();
}
DesktopGadget::~DesktopGadget()
{
    makeCurrent();
}
QSize DesktopGadget::minimumSizeHint() const
{
    return QSize(50, 50);
}
QSize DesktopGadget::sizeHint() const
{
    return QSize(600, 600);
}
void DesktopGadget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}
void DesktopGadget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}
void DesktopGadget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}
void DesktopGadget::initializeGL()
{
    qglClearColor(QColor::fromRgb(128,128,128));
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
void DesktopGadget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //gluLookAt(8,5,3,0,0,-5,0,0,1);

    glTranslated(0.0, 0.0, -5.0);
    //glRotatef(-30,0,1,0);
    //glScalef(1,2,1);y zoom 2
    //glRotatef(15,0,0,1);//z rotate 15 degree
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    /*glTranslated(-0.5,0,0);
    createObjects();
    glTranslated(0.32,0,0);
    glRotatef(30,0,0,1);
    createObjects();
    glTranslated(0.32,0,0);
    glRotatef(30,0,0,1);*/
    createObjects();
}

void DesktopGadget::createObjects()
{
    //glNewList (listSquare, GL_COMPILE);
    //glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3d(0.3,0.1, -0.05);
    glVertex3d(0.3,0, -0.05);
    glVertex3d(0,0, -0.05);
    glVertex3d(0,0.1, -0.05);
    glEnd();
    //glTranslatef (1.5, 0.0, 0.0);
    //glEndList ();
}

void DesktopGadget::mouseReleaseEvent ( QMouseEvent * )
{
    if(d_transparent==0)
        return;
    QImage img=grabFrameBuffer();
    mask=QBitmap::fromImage(img.createMaskFromColor(img.pixel(QPoint(10,10)),Qt::MaskInColor));
    setMask(mask);
}
void DesktopGadget::resizeGL(int width, int height)
{

    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,0.1,10);
    glMatrixMode(GL_MODELVIEW);
}
void DesktopGadget::mousePressEvent(QMouseEvent *event)
{
    clearMask();
    lastPos = event->pos();
}
void DesktopGadget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    QApplication::processEvents();
    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        move(pos().x()+dx, pos().y()+dy);
        //not perfect yet.
    }
    lastPos = event->pos();
}

