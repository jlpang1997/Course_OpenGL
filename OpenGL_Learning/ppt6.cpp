#include"ppt6.h"
#include <GL/glut.h>

void init(void)
{
	/* Set color of display window to white. */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	/* Set parameters for world-coordinate clipping window. */
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
	/* Set mode for constructing geometric transformation matrix. */
	glMatrixMode(GL_MODELVIEW); 
}
void triangle(wcPt2D *verts)
{
	GLint k;
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 3; k++)
		glVertex2f(verts[k].x, verts[k].y);
	glEnd();
}
void displayFcn(void)//重点是glviewport的使用 其实就是分屏
//glViewport(GLint x,GLint y,GLsizei width,GLsizei height)为其函数原型。
//X，Y————以像素为单位，指定了视口的左下角（在第一象限内，以（0，0）为原点的）位置。
//width，height————表示这个视口矩形的宽度和高度，根据窗口的实时变化重绘窗口。
{
	/* Define initial position for triangle. */
	wcPt2D verts[3] = { {-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0} };
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	glColor3f(0.0, 0.0, 1.0); // Set fill color to blue.
	glViewport(0, 0, 300, 300); // Set left viewport.

	triangle(verts); // Display triangle.
		/* Rotate triangle and display in right half of display window. */
	glColor3f(1.0, 0.0, 0.0); // Set fill color to red. 
	glViewport(300, 0, 300, 300); // Set right viewport. 
	glRotatef(90.0, 0.0, 0.0, 1.0); // Rotate about z axis. 
	triangle(verts); // Display red rotated triangle.
	glFlush();
}
void main_ppt6(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 300);
	glutCreateWindow("Split-Screen Example");
	init();
	glutDisplayFunc(displayFcn);
	glutMainLoop();
}
