#include <GL/glut.h>

#include"Initial.h"//初始化用

#include"homework1.h"//作业用

#include"lab1.h"//实验用
using namespace std;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	init();


	//glutDisplayFunc(function_display);//画二次函数
	//glutDisplayFunc(line_display);//画直线
	glutDisplayFunc(Cycle_display);//画圆

	glutMainLoop();
	return 0;
}