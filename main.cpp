#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//可以隐藏控制台

#include <GL/glut.h>


#include"Initial.h"//初始化用

#include"homework1.h"//作业用
#include"homework3.h"

#include"lab1.h"//实验用
using namespace std;
int   main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D Gasket");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	//gl_depth_test和reshape两个都很重要
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutMainLoop();
}



//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(0, 0);
//	glutInitWindowSize(800, 800);
//	glutCreateWindow("lab1");
//
//	glutDisplayFunc(display);
//	glEnable(GL_DEPTH_TEST);//很关键
//
//	glutMainLoop();
//	return 0;
//
//	//glutInit(&argc, argv);
//	//init();
//
//
//	////glutDisplayFunc(function_display);//画二次函数
//	////glutDisplayFunc(line_display);//画直线
//	//glutDisplayFunc(Cycle_display);//画圆
//	////glutDisplayFunc(display);//三维Sierpinski镂垫
//
//	//glutMainLoop();
//	return 0;
//}

