#include"Initial.h"
#include"gl/glut.h"
void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("lab1");

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

}