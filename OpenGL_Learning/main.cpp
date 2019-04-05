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

const int n = 10;
const GLfloat R = 0.5;
const GLfloat PI = 3.1415926536f;
void myDisplay(void)//画出一个调色板，牛逼
{
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

//


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
	glutDisplayFunc(myDisplay);

	glutMainLoop();
	return 0;
}