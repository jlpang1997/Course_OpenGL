#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//可以隐藏控制台

#include <GL/glut.h>


#include"Initial.h"//初始化用

#include"homework1.h"//作业用
#include"homework3.h"
#include"homework4.h"
#include"homework5.h"


#include"lab1.h"//实验用
#include"lab2.h"
#include"lab3.h"

using namespace std;
int   main(int argc, char **argv)
{
	//main_homework3(argc, argv);
	//main_homework4(argc, argv);
	//main_lab1(argc, argv);
	//main_lab2(argc, argv);
	main_lab3(argc, argv);
	//main_homework5(argc, argv);
}






