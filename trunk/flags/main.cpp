#include <iostream> 
#include <cmath> 
#include <GL/glut.h> 
#include <GL/gl.h> 
#include "flag.h" 
ClothMesh g_Cloth;
void SetupRC(void);
void ReShapeFunc(GLsizei, GLsizei); 
void DisplayFunc(void);
void KeyboardFunc(unsigned char, int, int); 
void TimerFunc(int); 
void DrawMesh(void); 
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
void SetupRC(void) 
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
void DisplayFunc(void) 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	DrawMesh(); 
	glutSwapBuffers(); 
} 
GLvoid KeyboardFunc(unsigned char key, int x, int y) 
{ 
	if(key == 'd') 
		g_Cloth.DealMesh(); 
	glutPostRedisplay(); 
} 
GLvoid TimerFunc(int value) 
{ 
	g_Cloth.DealMesh(); 
	glutPostRedisplay(); 
	glutTimerFunc(0, TimerFunc, 1); 
} 
void DrawMesh(void) 
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
}
