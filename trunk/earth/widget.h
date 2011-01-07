#ifndef WIDGET_H
#define WIDGET_H
#include <QtGui>
#include <QGLWidget>
#include <GL/glut.h>
#include <QPainter>
#include <QDateTime>
#include <QTimer>

class DesktopGadget : public QGLWidget
{
    Q_OBJECT

    public:
        DesktopGadget(QWidget *parent = 0);
        ~DesktopGadget();
        QSize minimumSizeHint() const;
        QSize sizeHint() const;

    public slots:
        void setXRotation(int angle);
        void setYRotation(int angle);
        void setZRotation(int angle);

    signals:
        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);

    protected:
        virtual void initializeGL();
        virtual void paintGL();
        virtual void resizeGL(int width, int height);
        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseMoveEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent( QMouseEvent * event );
        virtual void createObjects();
        bool d_transparent;//control whether remove window border
        int xRot;
        int yRot;
        int zRot;
        QPoint lastPos;
    private:
        QBitmap mask;
        GLuint listSquare;
        void normalizeAngle(int * angle);
        void drawBox(float x, float y, float z, float width, float height, float depth);
};

class Earth : public DesktopGadget
{
    Q_OBJECT
    public:
        Earth(QWidget *parent =0):DesktopGadget(parent){d_transparent=1;}
        ~Earth(){}
    protected:
        void createObjects();
        void initializeGL();
        void drawText();
        void mouseMoveEvent(QMouseEvent* event);
        QPixmap& createSurface();
    private:
        GLuint earthTexture, textTexture;
        QStringList cities;
        QPixmap text;
        QTimer* timer;
        int count;
    private slots:
        void refresh();
};

#endif // WIDGET_H
