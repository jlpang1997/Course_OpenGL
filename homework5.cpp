#include"homework5.h"
#include<math.h>
GLdouble CAR0(GLdouble u,GLdouble t)
{
	GLdouble s = (1 - t) / 2;
	return -s * u*u*u + 2 * s*u*u - s * u;
}
GLdouble CAR1(GLdouble u,GLdouble t)
{
	GLdouble s = (1 - t) / 2;
	return (2 - s)*u*u*u + (s - 3)*u*u + 1;
}

GLdouble CAR2(GLdouble u,GLdouble t)
{
	GLdouble s = (1 - t) / 2;
	return (s - 2)*u*u*u + (3 - 2 * s)*u*u + s * u;
}
GLdouble CAR3(GLdouble u,GLdouble t)
{
	GLdouble s = (1 - t) / 2;
	return s * u*u*u - s * u*u;
}

GLdouble P0[2] = { -0.8,0 },//初始四个点
P1[2] = { -0.3,-0.8 },
P2[2] = { 0.3,0.3 },
P3[2] = { 0.8,0 };



void Cardinal_line_displag()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P0);
	glEnd();
	glFlush;
	
	glColor3f(1.0, 0, 0);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (GLdouble u = 0; u <= 1; u += 0.001)
	{
		glPointSize(1);

		{
			glVertex2d(P0[0] * CAR0(u) + P1[0] * CAR1(u) + P2[0] * CAR2(u) + P3[0] * CAR3(u), P0[1] * CAR0(u) + P1[1] * CAR1(u) + P2[1] * CAR2(u) + P3[1] * CAR3(u));
		}
		
		
	}
	glEnd();
	glFlush();
}
void mouse_homework5_Cardinal(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		P1[1] += 0.1;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		P1[1] -= 0.1;
	}
	Cardinal_line_displag();
}

void display_nop()
{

}
long int fact(int n)
{
	long int result = 1;
	while (n > 0)
	{
		result *= n;
		n--;
	}
	return result;
}

GLdouble Bernstein(GLdouble t, int i, int n )
{
	return pow(t, i)*pow(1 - t, n - i)*fact(n) / (fact(i)*fact(n - i));
}

GLdouble Vertex[4][3] = {
	{ -0.8,0,-0.9 },
	{ -0.3,-0.8 ,0.8},
	{ 0.3,0.3,0.3 },
	{ 0.8,0 ,0.8}
};
GLdouble init_viewx = 0, init_viewy = 0, init_viewz = 5;
GLdouble viewx = init_viewx, viewy = init_viewy, viewz = init_viewz;//作为三维观察点

//正交投影用的参数变量
GLdouble init_left = -1, init_right = 1, init_bottom = -1, init_top = 1,  init_near = 2, init_far = 10;//远近通用两种投影
GLdouble left=init_left, right=init_right, bottom=init_bottom, top=init_top, near=init_near, far=init_far;

//透视投影用的变量
GLdouble init_theta = 75;
GLdouble init_aspect = 1;
GLdouble theta = init_theta;
GLdouble aspect = init_aspect;

void key_homework5_Bezier(unsigned char key,int x,int y)
//void key_homework5_Bezier(int key, int x, int y)
{
	switch (key)
	{
	case'o'://选择正交投影
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(init_left, init_right, init_bottom, init_top, init_near, init_far);//正交投影
		break;
	}
	case'p'://选择透视投影
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(init_theta, init_aspect,  init_near, init_far);//正交投影
		break;
	}
	case'a':
	{
		viewx -= CHANGE_SIZE;
		break;
	}
	case'd':
	{
		viewx += CHANGE_SIZE;
		break;
	}
	case'w':
	{
		viewy += CHANGE_SIZE;
		break;
	}
	case's':
	{
		viewy -= CHANGE_SIZE;
		break;
	}
	case'z':
	{
		viewz -= CHANGE_SIZE;//靠近
		break;
	case'x':
	{
		viewz += CHANGE_SIZE;//远离
		break;
	case'r'://重置
	{
		viewx = init_viewx;
		viewy = init_viewy;
		viewz = init_viewz;
		left = init_left;
		right = init_right;
		bottom = init_bottom;
		top = init_top;
		near = init_near;
		far = init_far;

		theta = init_theta;
		aspect = init_aspect;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
		break;

	}
	case'g'://选择正交投影
	{
		if(glutGetModifiers()==GLUT_ACTIVE_CTRL)
			left += CHANGE_SIZE;
		else
			left -= CHANGE_SIZE;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
		break;
	}
	case'j'://选择正交投影
	{
		right+= CHANGE_SIZE;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
		break;
	}
	case'y'://选择正交投影
	{
		top += CHANGE_SIZE;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
		break;
	}
	case'h'://选择正交投影
	{
		bottom -= CHANGE_SIZE;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
		break;
	}
	case'b'://选择正交投影
	{
		near -= CHANGE_SIZE;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
		break;
	}
	case'n'://选择正交投影
	{
		far += CHANGE_SIZE;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
		break;
	}

	case'c'://增大角度
	{
		theta +=5;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(theta, aspect, near, far);
		break;
	}
	case'v'://减小角度
	{
		theta -= 5;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(theta, aspect, near, far);
		break;
	}
	case'k'://增大宽高比
	{
		aspect += 0.1;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(theta, aspect, near, far);
		break;
	}
	case'l'://减小宽高比
	{
		aspect -= 0.1;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(theta, aspect, near, far);
		break;
	}



	}
	}
	default:
		break;
	}
	Bezier_line_display();
}
void mouse_homework5_Bezier(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Vertex[0][1] += 0.1;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		Vertex[0][1] -= 0.1;
	}
	Bezier_line_display();
}

void Bezier_line_display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewx, viewy, viewz, 0, 0, 0, 0, 1, 0);

	glColor3f(0, 0, 0);
	glPointSize(5);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3dv(Vertex[0]);
	glVertex3dv(Vertex[2]);
	glVertex3dv(Vertex[3]);
	glVertex3dv(Vertex[1]);
	glEnd();
	glFlush();
	GLdouble B[3];
	glColor3f(1, 0, 0);
	glPointSize(1);
	glBegin(GL_POINTS);
	{
		for (GLdouble t = 0; t <= 1; t+=0.001)
		{
			B[0] = 0, B[1] = 0, B[2] = 0;
			for (int i = 0; i <=N; i++)
			{
				GLdouble tmp = Bernstein(t, i);
				for (int k = 0; k < 3; k++)
				{
					B[k] += tmp * Vertex[i][k];
				}
			}
			
			glVertex3dv(B);

		}

	}
	glEnd();
	glFlush();

}
void Init_homework5()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewx, viewy, viewz, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 0, 10);//正交投影

}

void main_homework5(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("homework5");

	Init_homework5();
	//glutMouseFunc(mouse_homework5_Cardinal);
	//glutDisplayFunc(display_nop);
	glutDisplayFunc(Bezier_line_display);
	glutKeyboardFunc(key_homework5_Bezier);
	glutMouseFunc(mouse_homework5_Bezier);

	glutMainLoop();


}