#include"gl/glut.h"
#include<math.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//可以隐藏控制台
//入门第一课

//输出三种图元，点、线、多边形
void point_display()
{
	glPointSize(10);//指定大小，单位像素
	glBegin(GL_POINTS);
	{
		GLfloat v[2] = { 0,0.5 };
		glVertex2f(0.0f, 0.0f);//表示屏幕中心，作为原点
		glVertex2fv(v);//指针，其实就是个数组，一维向量

		//glVertex2s(10,10);//为什么这个不行？
		//GLshort v[2] = { 10,20 };
		//glVertex2sv(v);
							   //glVertex2f(0.0f, 0.5f);//1.0表示屏幕边上
		//glVertex2f(0.5f, 0.25f);
	}
	glEnd();
	glFlush();
}
void line_display()
{
	//GL_LINES 两个点配对，所以必须有偶数个点
	//GL_LINE_STRIP 首尾相连但不闭合
	//GL_LINE_LOOP 首尾相连而且闭合
	glLineWidth(3);//设定宽度

	glEnable(GL_LINE_STIPPLE);//开启虚线模式

	glLineStipple(3, 0b1001001001001000);//设置虚线属性
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(-0.8, -0.5);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.8, 0);
		glVertex2f(-0.5, 0);
		glVertex2f(-0.8, 0.5);
		glVertex2f(-0.3, 0.5);
	}
	glEnd();
	glFlush();
}
void polygon_display()//opengl只能画凸多边形
{
	glPointSize(10);
	glFrontFace(GL_CCW);//逆时针为正面
	glFrontFace(GL_CW);//顺时针
	//glBegin(GL_POLYGON);
	//glBegin(GL_TRIANGLES);
	//glBegin(GL_TRIANGLE_STRIP);
	glPolygonMode(GL_FRONT, GL_POINT);//GL_POINT是用来设置模式的，而GL_POINTS是用来画点的
	glPolygonMode(GL_BACK, GL_FILL);//这说明当我们画二维的时候，看到的是背面
	glBegin(GL_QUADS);//四边形
	{
		glVertex2f(0, -0.1);
		glVertex2f(-0.5, 0);
		glVertex2f(0, 0.5);
		glVertex2f(0.5, 0);
		glVertex2f(0, -0.5);

	}
	glEnd();
	glFlush();
}

//输出颜色
void line_color_display()//RGBA模式，至于颜色索引模式就是把颜色值储存在一张表里面，用的时候直接去颜色指针就行
{
	glClearColor(1, 1, 1,1);//设置屏幕颜色白色
	glClear(GL_COLOR_BUFFER_BIT);//使用设置的颜色作为屏幕颜色，两者配合着使用

	glColor3f(0, 0, 1);//
	glLineWidth(5);
	glPolygonMode(GL_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.5, 0.5);
		glVertex2f(0, 0.5);
		glVertex2f(0, 0);
		glVertex2f(-0.5, 0);
	}
	glEnd();

	glLineWidth(5);
	glShadeModel(GL_FLAT);//取后一点颜色
	glShadeModel(GL_SMOOTH);//渐变
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex2f(0.5, 0);
		glColor3f(0, 1, 0);
		glVertex2f(1.0, 0);
	}
	glEnd();
	glFlush();


	glFlush();


}


void tiaoseban_display(void)//画出一个调色板，牛逼
{
	const int n = 10;
	const GLfloat R = 0.5;
	const GLfloat PI = 3.1415926536f;
	glBegin(GL_POLYGON);
	{
		glColor3f(1, 1, 1);
		glVertex2f(0, 0);
		for (int i = 1; i < 8; i++)
		{
			glColor3f(i & 0x004, i & 0x002, i & 0x001);//这个看不太懂？？
			glVertex2f(R*cos(i*PI / 3), R*sin(i*PI / 3));//画出八个顶点
		}
	}
	glEnd();

	glFlush();
}

//坐标变化
//1,实际变换顺序和指定的顺序是相反的

//一些已实现的模型
void model_display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 10; i++)
	{
		glPushMatrix();
		glTranslatef(0, 0.8 - 0.4*i, 0);
		glColor3f(i / 10, 1, 0);
		switch (i)
		{
			case 0:
			{
				glutWireSphere(0.2, 100, 100);//网状球，半径的设置为浮点数，所以小于1
				break;
			}
			case 1:
			{
				glutWireCone(0.2,0.2,10,10);//网状球，半径的设置为浮点数，所以小于1
				break;
			}
			case 2:
			{
				glutWireCube(0.2);//网状球，半径的设置为浮点数，所以小于1
				break;
			}
			case 3:
			{
				glutWireTeapot(0.2);//网状球，半径的设置为浮点数，所以小于1
				break;
			}
			case 4:
			{
				glutWireTorus(0.05,0.1,10,10);//网状球，半径的设置为浮点数，所以小于1
				break;
			}
		}
		glPopMatrix();
		glFlush();
	}

}

//世界坐标系和观察坐标系
void look_model_display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//世界坐标系
	//在OpenGL中，世界坐标系是以屏幕中心为原点(0, 0, 0)，且是始终不变的。
	//你面对屏幕，你的右边是x正轴，上面是y正轴，屏幕指向你的为z正轴。长度单位这样来定：窗口范围按此单位恰好是(-1, -1)到(1, 1)，即屏幕左下角坐标为
		//（ - 1， - 1），右上角坐标为（1, 1）。这是采用了归一化的结果
	glColor3f(1, 0, 0);
	{
		glMatrixMode(GL_MODELVIEW);//gl_lookat作用于模型视图，也就是说用他之前必须设置一下这里
		//glLoadIdentity();//栈顶为单位阵
		//gluLookAt(0, 0, 1,
		//		  0,0,0,
		//	0,1,0);//把它看成人，前三个分量是眼睛的位置，
					//中间三个分量是看的方向
					//最后三个分量是头的朝向
		glTranslatef(0.4, 0.2,0);
		glRotatef(30, 0, 0, 1);
		glScalef(0.5, 1.5, 0.5);


		glutWireTeapot(0.3);
		glFlush();

	}
}

//投影变换
void touying_display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_PROJECTION);//正视投影
	//glOrtho(-1, 1, -1, 1, 0, 20);//设置矩形视景体
	//glFrustum(-1, 1, -1, 1, 1, 20);//设置棱台视景体
	gluPerspective(60, 1, 1, 20);//同上

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0,0,0);
	glColor3f(1, 0, 0);
	glutWireTeapot(5);
	glFlush();
	


}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("helle world");

	//glutDisplayFunc(point_display);
	//glutDisplayFunc(line_display);
	//glutDisplayFunc(polygon_display);
	//glutDisplayFunc(line_color_display);
	//glutDisplayFunc(myDisplay);

	//glutDisplayFunc(model_display);
	//glutDisplayFunc(look_model_display);
	glutDisplayFunc(touying_display);

	glutMainLoop();
	return 0;
}