#include"gl/glut.h"
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//可以隐藏控制台
//入门第一课

//框架
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
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("helle world");

	//glutDisplayFunc(point_display);
	//glutDisplayFunc(line_display);
	glutDisplayFunc(polygon_display);

	glutMainLoop();
	return 0;
}