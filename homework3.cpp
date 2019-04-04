#include"homework3.h"

GLfloat v[4][3] = { {0.0, 0.0, 1.0},
{0.0, 0.942809, -0.33333},
{-0.816497, -0.471405, -0.333333},
{0.816497, -0.471405, -0.333333} };
GLfloat colors[4][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0} ,
{0.0, 0.0, 1.0}, {0.0, 0.0, 0.0} };

void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc)
{ //画三角形
	glBegin(GL_POINTS);
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
	glEnd();
}
void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{ //画四面体
	glColor3fv(colors[0]);
	triangle(a, b, c);
	glColor3fv(colors[1]);
	triangle(a, c, d);
	glColor3fv(colors[2]);
	triangle(a, d, b);
	glColor3fv(colors[3]);
	triangle(b, d, c);
}

void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{
	GLfloat mid[6][3];
	int j;
	if (m > 0)
	{ /* compute six midpoints */
		for (j = 0; j < 3; j++) mid[0][j] = (a[j] + b[j]) / 2;
		for (j = 0; j < 3; j++) mid[1][j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) mid[2][j] = (a[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) mid[3][j] = (b[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) mid[4][j] = (c[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) mid[5][j] = (b[j] + d[j]) / 2;
		/* create 4 tetrahedrons by subdivision */
		divide_tetra(a, mid[0], mid[1], mid[2], m - 1);
		divide_tetra(mid[0], b, mid[3], mid[5], m - 1);
		divide_tetra(mid[1], mid[3], c, mid[4], m - 1);
		divide_tetra(mid[2], mid[4], d, mid[5], m - 1);
	}
	else(tetra(a, b, c, d)); /* draw tetrahedron at end of recursion */
}
	int n = 1;//?
void display()
{

	glClear(GL_COLOR_BUFFER_BIT
		| GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_tetra(v[0], v[1], v[2], v[3],n);
	glEnd();
	glFlush();
}