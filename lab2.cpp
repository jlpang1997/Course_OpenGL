#include"lab2.h"
void main_lab2(int argc, char**argv)
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE |GLUT_DEPTH);
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(500, 500);
		glutCreateWindow("lab2");

		glutReshapeFunc(myReshape);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glutDisplayFunc(lab2_display);

		glutMainLoop();
}
static GLfloat v[4][3] = { {0.0, 0.0, 1.0},
{0.0, 0.942809, -0.33333},
{-0.816497, -0.471405, -0.333333},
{0.816497, -0.471405, -0.333333} };
static GLfloat colors[4][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0} ,
{0.0, 0.0, 1.0}, {0.0, 0.0, 0.0} };
void lab2_display(void)
{
	glClearColor(1, 1, 1, 1);
	//报告上的三个测试函数
	//glTranslatef(0.8, 0, 0);
	//glRotatef(20, 0, 0, -1);
	//glScalef(2, 2, 1);

	//int cycle = 0;
	//for (int i = 0; cycle < 5; i = (i + 1) % 360)
	//{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);
		divide_tetra(v[0], v[1], v[2], v[3], 1);
		glEnd();
		glFlush();

		//glTranslatef((GLdouble)i / 180, 0, 0);
		my_translate(1,1,1);
		//glRotatef(10, 0, 0, -1);
		//my_rotate(30, 0, 0, -1);
		//glScalef(1.5, 1.5, 1.5);
		//my_scale(1.5, 1.5, 1.5);
		//glScalef(i / 150, i / 150, 1);
		glBegin(GL_TRIANGLES);
		divide_tetra(v[0], v[1], v[2], v[3], 1);
		glEnd();
		glFlush();


	//	for (int j = 0; j < 10000; j++)
	//		glFlush();
	//	if (i == 359)
	//		cycle++;
	//}

}

void my_translate(GLdouble x, GLdouble y, GLdouble z)
{
	glMatrixMode(GL_MODELVIEW);
	const GLfloat matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		x,y,z,1
	};//写进来的顺序跟我们的顺序不一样，刚好转置
	glMultMatrixf(matrix);
}

void my_rotate(GLdouble theta, GLdouble x, GLdouble y, GLdouble z)
{
	GLdouble mod = sqrt(x*x + y * y + z * z);
	GLdouble a = x / mod, b = y / mod, c = z / mod;
	theta = -theta;
	GLdouble d1 = sqrtf(b*b + c * c);
	const GLdouble Rx[16] = {
		1,0,0,0,
		0,c/d1,-b/d1,0,
		0,b/d1,c/d1,0,
		0,0,0,1
	};

	const GLdouble Rx_T[16] = {
		1,0,0,0,
		0,c / d1,b / d1,0,
		0,-b / d1,c / d1,0,
		0,0,0,1
	};
	

	const GLdouble Ry[16] = {//这个d有问题哈
		d1,0,-a,0,
		0,1,0,0,
		a,0,d1,0,
		0,0,0,1
	};

	const GLdouble Ry_T[16] = {
		d1,0,a,0,
		0,1,0,0,
		-a,0,d1,0,
		0,0,0,1
	};

	const GLdouble R_theta[16] = {
		cos(theta),+sin(theta),0,0,
		-sin(theta),cos(theta),0,0,
		0,0,1,0,
		0,0,0,1
	};
	glMultMatrixd(Rx_T);
	glMultMatrixd(Ry_T);
	glMultMatrixd(R_theta);
	glMultMatrixd(Ry);
	glMultMatrixd(Rx);
}

void my_scale(GLdouble x, GLdouble y, GLdouble z)
{
	glMatrixMode(GL_MODELVIEW);
	const GLfloat matrix[16] = {
		x,0,0,0,
		0,y,0,0,
		0,0,z,0,
		0,0,0,1
	};//写进来的顺序跟我们的顺序不一样，刚好转置
	glMultMatrixf(matrix);
}