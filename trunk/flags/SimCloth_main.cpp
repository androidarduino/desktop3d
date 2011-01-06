<html><head><title>SimCloth.zip SimCloth_main.cpp</title>
<LINK href="/inc/read_style.css" type=text/css rel=stylesheet></head>
<body>
<p><a href=http://www.pudn.com>www.pudn.com</a> &gt; <a href="http://www.pudn.com/downloads78/sourcecode/graph/detail298391.html">SimCloth.zip</a> &gt SimCloth_main.cpp, change:2006-11-28,size:4530b</p><!-- saved from http://www.pudn.com -->
<script src="/inc/gg_read1.js"></script><BR>
<pre name="code" class="cpp">
/* ========================================================================= * 
 *	Name:		Cloth_main.cpp                                               * 
 *	Function:	The main program.                                            * 
 *	Date:		2006-11-22                                                   * 
 *	Editor:		jixing_alex                                                  * 
 * ========================================================================= */ 
 
// Include 
#include <iostream> 
#include <conio.h> 
#include <cmath> 
#include <GL/glut.h> 
 
// Include my file 
#include "ClothMesh.h" 
 
// Declaration of globe variable 
ClothMesh g_Cloth; 
 
// Declaration of function 
GLvoid SetupRC(GLvoid); 
GLvoid ReShapeFunc(GLsizei, GLsizei); 
GLvoid DisplayFunc(GLvoid); 
GLvoid KeyboardFunc(unsigned char, int, int); 
GLvoid TimerFunc(int); 
GLvoid DrawMesh(GLvoid); 
 
// main 
int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(800, 600); 
	glutInitWindowPosition(100, 150); 
	glutCreateWindow("cloth"); 
	glutReshapeFunc(ReShapeFunc); 
	glutDisplayFunc(DisplayFunc); 
	glutKeyboardFunc(KeyboardFunc); 
	glutTimerFunc(0, TimerFunc, 1); 
	SetupRC(); 
	glutMainLoop(); 
	return 0; 
} 
 
// Get ready before render. It include set light, material, backgroud, ... 
GLvoid SetupRC(GLvoid) 
{ 
    GLfloat	lightPos[] = { 100.f, 0.0f, 100.0f, 1.0f }; 
	GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f }; 
    GLfloat ambientLight[] = { 0.05f, 0.05f, 0.05f, 1.0f }; 
    GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f }; 
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
 
    glEnable(GL_DEPTH_TEST); 
    glFrontFace(GL_CCW); 
    glEnable(GL_NONE); 
 
    glEnable(GL_LIGHTING); 
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos); 
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir); 
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight); 
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight); 
    glLightfv(GL_LIGHT0,GL_SPECULAR, specular); 
    glEnable(GL_LIGHT0); 
 
    glEnable(GL_COLOR_MATERIAL); 
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
	glShadeModel(GL_SMOOTH); 
 
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f ); 
} 
 
// Regulate viewport's size when the window was modified. 
GLvoid ReShapeFunc(GLsizei w, GLsizei h) 
{ 
	if(w >= h) 
		glViewport((w - h) / 2, 0, h, h); 
	else 
		glViewport(0, (h - w) / 2, w, w); 
 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(60.0, 1, -200.0, 200.0); 
	gluLookAt(0.0, 0.0, 800, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
} 
 
// This include the thing that will be rendered. 
GLvoid DisplayFunc(GLvoid) 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	DrawMesh(); 
	glutSwapBuffers(); 
} 
 
// Key's management 
GLvoid KeyboardFunc(unsigned char key, int x, int y) 
{ 
	if(key == ' ') 
		g_Cloth.DealMesh(); 
 
	glutPostRedisplay(); 
} 
 
// Time's management in animation 
GLvoid TimerFunc(int value) 
{ 
	g_Cloth.DealMesh(); 
	glutPostRedisplay(); 
	glutTimerFunc(0, TimerFunc, 1); 
} 
 
// Draw cloth's mesh 
GLvoid DrawMesh(GLvoid) 
{ 
	for(int i = 0; i < SIZEV - 1; i++) 
	{ 
		for(int j = 0; j < SIZEU - 1; j++) 
		{ 
			glColor3f(1.0f, 1.0f, 1.0f); 
			glBegin(GL_QUADS); 
				glNormal3f(g_Cloth.m_vNormal[i][j].m_fX, 
					       g_Cloth.m_vNormal[i][j].m_fY, 
						   g_Cloth.m_vNormal[i][j].m_fZ); 
				glVertex3f(g_Cloth.m_vPosition[i][j].m_fX, 
					       g_Cloth.m_vPosition[i][j].m_fY, 
						   g_Cloth.m_vPosition[i][j].m_fZ); 
				glNormal3f(g_Cloth.m_vNormal[i + 1][j].m_fX, 
					       g_Cloth.m_vNormal[i + 1][j].m_fY, 
						   g_Cloth.m_vNormal[i + 1][j].m_fZ); 
				glVertex3f(g_Cloth.m_vPosition[i + 1][j].m_fX, 
					       g_Cloth.m_vPosition[i + 1][j].m_fY, 
						   g_Cloth.m_vPosition[i + 1][j].m_fZ); 
				glNormal3f(g_Cloth.m_vNormal[i + 1][j + 1].m_fX, 
					       g_Cloth.m_vNormal[i + 1][j + 1].m_fY, 
						   g_Cloth.m_vNormal[i + 1][j + 1].m_fZ); 
				glVertex3f(g_Cloth.m_vPosition[i + 1][j + 1].m_fX, 
					       g_Cloth.m_vPosition[i + 1][j + 1].m_fY, 
						   g_Cloth.m_vPosition[i + 1][j + 1].m_fZ); 
				glNormal3f(g_Cloth.m_vNormal[i][j + 1].m_fX, 
					       g_Cloth.m_vNormal[i][j + 1].m_fY, 
						   g_Cloth.m_vNormal[i][j + 1].m_fZ); 
				glVertex3f(g_Cloth.m_vPosition[i][j + 1].m_fX, 
					       g_Cloth.m_vPosition[i][j + 1].m_fY, 
						   g_Cloth.m_vPosition[i][j + 1].m_fZ); 
			glEnd(); 
		} 
	} 
}</pre>
<script src="/inc/gg_read2.js"></script><BR>
<script src="http://s117.cnzz.com/stat.php?id=1236358&web_id=1236358&show=pic" language="JavaScript" charset="gb2312"></script>
</body></html>
