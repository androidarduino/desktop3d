#ifndef WIDGET_H
#define WIDGET_H
#include <QtGui>
#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT

    public:
        GLWidget(QWidget *parent = 0);
        ~GLWidget();

        QSize minimumSizeHint() const;
        QSize sizeHint() const;

        public slots:
            void setXRotation(int angle);
        void setYRotation(int angle);
        void setZRotation(int angle);
        void refresh();

signals:
        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent( QMouseEvent * event );

    private:
        GLuint makeObject();
        void makeArrows();
        void draw_circle(const GLfloat radius,const GLuint num_vertex);
        void quad(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2,
                GLdouble x3, GLdouble y3, GLdouble x4, GLdouble y4, double angle);
        void extrude(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
        void normalizeAngle(int *angle);
        QBitmap mask;
        GLuint object;
        int xRot;
        int yRot;
        int zRot;
        QPoint lastPos;
        QColor trolltechGreen;
        QColor trolltechPurple;
        QTimer *timer;
};

#endif // WIDGET_H
