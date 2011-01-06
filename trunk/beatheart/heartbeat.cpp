#include "widget.h"
/*

*/

void HeartBeat::createObjects()
{
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
  glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Front)
  glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Front)
  glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Front)
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
  glEnd();					// Done Drawing The Cube
}
