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
    glFogf(GL_FOG_DENSITY, 0.35f);                 // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);             // Fog Hint Value
    glFogf(GL_FOG_START, 1.0f);                    // Fog Start Depth
    glFogf(GL_FOG_END, 5.0f);                      // Fog End Depth
    //glEnable(GL_FOG);                              // Enables GL_FOG

    //glEnable(GL_LIGHTING);
    GLfloat ambientLight[]={1,1,1,1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    QGLShader * shaderF=new QGLShader(QGLShader::Fragment);
    QGLShader * shaderV=new QGLShader(QGLShader::Vertex);
//    shaderV->compileSourceFile("test.vsh");
    shaderF->compileSourceFile("test.fsh");
    QGLShaderProgram * program=new QGLShaderProgram;
//    program->addShader(shaderV);
    program->addShader(shaderF);
    qDebug()<<"compile shader: "<<program->link();
    program->bind();

    //glEnable (GL_BLEND);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void HeartBeat::createObjects()
{
    glEnable(GL_TEXTURE_2D);
    wood=bindTexture(QPixmap("pics/waterlili.png"), GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wood);

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

}

