#include<iostream>
#include "gl/glut.h"
#include"homework4.h"
#include<time.h>
using namespace std;
bool display_func_flag = true;
GLint winWidth = 600, winHeight = 600; // Initial display-window size.
GLfloat view_x = 120.0, view_y = 50.0, view_z = 100.0; // Viewing-coordinate origin.
GLfloat z_select = view_z;
GLfloat x_select = view_x;
GLfloat y_select = view_y;

GLfloat xref = 50.0, yref = 50.0, zref = 0.0; // Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // View-up vector.
/* Set coordinate limits for the clipping window: */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;
/* Set positions for near and far clipping planes: */
GLfloat dnear = 20.0, dfar = 1250.0;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}
#define face_nop 100
static int front_design = GL_FILL;
static int back_design = GL_FILL;
#define front_select 1
#define back_select 0
static int face_select = front_select;
void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
}
void displayFcn(void)
{
	if (display_func_flag)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		/* Set parameters for a square fill area. */

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(x_select, y_select, z_select, xref, yref, zref, Vx, Vy, Vz);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE); // Wire-frame back face.
		glColor3f(0.0, 1.0, 0.0); // Set fill color to green.
		glBegin(GL_QUADS);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(100.0, 0.0, 0.0);
		glVertex3f(100.0, 100.0, 0.0);
		glVertex3f(0.0, 100.0, 0.0);
		glEnd();
		glFlush();
	}


}
//一个摩恩四面体
int polygon_face_num=4;
int polygon_vertex_num[10] = { 3,3,3,3 };
GLfloat polygon_vertex[10][10][3] = { { {0,0,0},{100,0,50},{100,100,0} },
										{ {100,0,50},{100,0,-50},{100,100,0} },
										{ {0,0,0},{100,0,50},{100,0,-50} },
										{ {0,0,0},{100,100,0},{100,0,-50} }
};

void process_top_menu(int value)
{
	if (value == 9)
	{
		exit(0);
	}
	else if (value == 10)//看正面
	{
		x_select = view_x;
		y_select = view_y;
		z_select = view_z;
	}
	else if(value==11)//看背面
	{
		x_select = view_x;
		y_select = view_y;
		z_select = -view_z;//就是把视点z坐标取反了
	}
	if(display_func_flag)
		displayFcn();
	else
	{
		polygon_cube_display();
	}
}
void process_submenu_front(int value)
{
	//if (value == 1)
	//{
	//	front_design = GL_FILL;
	//}
	//else if (value == 2)
	//{
	//	front_design = GL_LINE;
	//}
	//else if (value == 3)
	//{
	//	front_design = GL_POINT;
	//}
	//else if (value == 4)
	//{
	//	front_design = face_nop;
	//}
	displayFcn();
}
void process_submenu_back(int value)
{
	//if (value == 5)
	//{
	//	back_design = GL_FILL;
	//}
	//else if (value == 6)
	//{
	//	back_design = GL_LINE;
	//}
	//else if (value == 7)
	//{
	//	back_design = GL_POINT;
	//}
	//else if (value == 8)
	//{
	//	back_design = face_nop;
	//}
	displayFcn();
}
void process_perspective_para_input(int value)
{
	if (value == 1)
	{
		cout << "自定义观察点坐标x，y，z：";
		cin >> view_x >> view_y >> view_z;
	}
	else if (value == 2)
	{
		cout << "自定义焦点坐标x，y，z：";
		cin >> xref >> yref >> zref;
	}
	else if (value == 3)
	{
		cout << "自定义头顶指向x，y，z：";
		cin >> Vx >> Vy >> Vz;
	}
	else if (value == 4)
	{
		cout << "自定义透视近窗口左右坐标xwMin,xwMax：";
		cin >> xwMin >> xwMax;
	}
	else if (value == 5)
	{
		cout << "自定义透视近窗口上下坐标ywMax,ywMin：";
		cin >> ywMax >> ywMin;
	}
	else if (value == 6)
	{
		cout << "自定义透视近远窗口坐标dnear,dfar：";
		cin >> dnear >> dfar;
	}
	displayFcn();
}

void process_polygon(int value)
{
	
	 if (value == 1)
	 {
		 cout << "输入多面体面数：";
		 cin >> polygon_face_num;
		int tmp_vertex_num;
		for (int i = 0; i < polygon_face_num; i++)
		{
			cout << "	输入第" << i + 1 << "个面的顶点数：";
			cin >> tmp_vertex_num;
			polygon_vertex_num[i] = tmp_vertex_num;
			for (int j = 0; j < tmp_vertex_num; j++)
			{
				cout << "		输入这个面的第" << j + 1 << "个顶点：";
				for (int k = 0; k < 3; k++)
				{
					cin >> polygon_vertex[i][j][k];
				}
			}

		}
		polygon_cube_display();
	}
	 else if (value == 2)//预定义好的四面体
	 {
		 polygon_cube_display();
	 }
}

int tou;
void polygon_display(GLfloat v[10][3], int vex_num)//显示一个面
{
	display_func_flag = false;
	//为了方便观察里面的面，设置透明度
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	//glShadeModel(GL_FLAT);
	glBegin(GL_POLYGON);
	{
		for (int i = 0; i < vex_num; i++)
		{
			glColor4ub(rand() % 256, rand() % 256, rand() % 256,tou);//为了好看就用了随机色
			glVertex3fv(v[i]);
		}
	}
	glEnd();
	glFlush();

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}
void polygon_cube_display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glFlush();

	//glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x_select, y_select, z_select, xref, yref, zref, Vx, Vy, Vz);
	srand((unsigned)time(NULL));
	for (int i = 0; i < polygon_face_num; i++)
	{
		if (i < 2)
			tou = 255;//前面两个面需要透明
		else
		{
			tou = 35;//背面两个面不用透
		}
		polygon_display(polygon_vertex[i], polygon_vertex_num[i]);
	}
}
void main_homework4(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA |GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Perspective View of A Square");
	init();
	
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFcn);

	//int submenu_front = glutCreateMenu(process_submenu_front);
	//glutAddMenuEntry("fill", 1);
	//glutAddMenuEntry("line", 2);
	//glutAddMenuEntry("point", 3);
	//glutAddMenuEntry("nop", 4);

	//int submenu_back = glutCreateMenu(process_submenu_back);
	//glutAddMenuEntry("fill", 5);
	//glutAddMenuEntry("line", 6);
	//glutAddMenuEntry("point", 7);
	//glutAddMenuEntry("nop", 8);



	int submenu_lookat = glutCreateMenu(process_perspective_para_input);
	glutAddMenuEntry("自定义观察点坐标x，y，z",1);
	glutAddMenuEntry("自定义焦点坐标x，y，z",2);
	glutAddMenuEntry("自定义头顶指向x，y，z", 3);

	glutAddMenuEntry("自定义透视近窗口左右坐标xwMin,xwMax", 4);
	glutAddMenuEntry("自定义透视近窗口上下坐标ywMax,ywMin", 5);
	glutAddMenuEntry("自定义透视近远窗口坐标dnear,dfar", 6);

	int submenu_polygon = glutCreateMenu(process_polygon);
	glutAddMenuEntry("自定义",1);
	glutAddMenuEntry("四面体001",2);




	

	int top_menu;
	top_menu = glutCreateMenu(process_top_menu);
	glutAddMenuEntry("See front face", 10);
	glutAddMenuEntry("See back face", 11);
	glutAddSubMenu("自定义透视观察参数", submenu_lookat);
	//glutAddMenuEntry("生成多面体", 12);
	glutAddSubMenu("生成多面体", submenu_polygon);

	glutAddMenuEntry("exit", 9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}

