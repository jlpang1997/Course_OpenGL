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
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("helle world");

	glutDisplayFunc(point_display);

	glutMainLoop();
	return 0;
}