#include "widget.h"
/*
todo:
1. add fog done
2. add glsl
3. add point sprites
4. add NURB surface
5. 
 */

void HeartBeat::initializeGL()
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

    shaderF=new QGLShader(QGLShader::Fragment);
    shaderV=new QGLShader(QGLShader::Vertex);
    shaderV->compileSourceFile("test.vsh");
    shaderF->compileSourceFile("test.fsh");
    QGLShaderProgram * program=new QGLShaderProgram;
    program->addShader(shaderV);
    program->addShader(shaderF);
    qDebug()<<"compile shader: "<<program->link();

    //program->bind();

    QMatrix4x4 mat;//mat,0.1,100
    float nearZ=0.1;
    float farZ=100;
    static const QMatrix4x4 reference(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -1.0f, 0.0f);

    mat = reference;
    mat(2, 2) = (nearZ+farZ)/(nearZ-farZ);
    mat(2, 3) = 2.0f*nearZ*farZ/(nearZ-farZ);

    program->setUniformValue("tex", GLint(0));
    program->setUniformValue("env", GLint(1));
    //program->setUniformValue("noise", GLint(2));
    //program->setUniformValue("marbleColors[0]", QColor(0,255,0,255));
    //program->setUniformValue("marbleColors[1]", QColor(255,0,0,255));
    program->setUniformValue("view", mat);
    //     program->setUniformValue("invView", invView);
    //   program->release();

    glEnable(GL_TEXTURE_2D);
    wood=bindTexture(QPixmap("earth.png"), GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wood);
    //    glShadeModel(GL_SMOOTH);
}

void HeartBeat::createObjects()
{

    //GLfloat gray[]={1,1,1,1};
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    /*
       glBegin(GL_QUADS);				// start drawing the cube.
    // top of cube
    glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);		// Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);		// Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);		// Bottom Right Of The Quad (Top)
    // bottom of cube
    glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Bottom)
    // front of cube
    glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
    glTexCoord2d(1,1);
    glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Front)
    glTexCoord2d(0,1);
    glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Front)
    glTexCoord2d(0,0);
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Front)
    glTexCoord2d(1,0);
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Front)
    // back of cube.
    glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);		// Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);		// Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);		// Bottom Right Of The Quad (Back)
    // left of cube
    glColor3f(0.0f,0.0f,1.0f);			// Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Left)
    // Right of cube
    glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);	        // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Right)
    glEnd();					// Done Drawing The Cub
     */
       GLUquadricObj *quadratic;               // Storage For Our Quadratic Objects ( NEW )
       quadratic=gluNewQuadric();          // Create A Pointer To The Quadric Object ( NEW )
       gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals ( NEW )
       gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords ( NEW )

       //gluSphere(quadratic,1.3f,32,32);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable ( GL_TEXTURE_2D );
    glBindTexture ( GL_TEXTURE_2D, wood);

    glRotatef(90,1,0,0);
   //draw textured sphere
    gluSphere(quadratic, 0.9, 36, 72);
    glRotatef(-90,1,0,0);
    //draw textured rectangle
/*    glPushMatrix();
    glTranslatef(0.0,0.0,1.0);
    glScalef(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex2f( -1.0,-1.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(1.0,-1.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(1.0,1.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(-1.0,1.0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(-1.0,-1.0);
    glEnd();
    glPopMatrix();
    */
    glDisable(GL_TEXTURE_2D);

}
