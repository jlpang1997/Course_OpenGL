#pragma once
#include"gl/glut.h"
#define T 0.5
#define N 3//��Ӧ�ĸ����Ƶ�Ľ���Ϊ3
#define CHANGE_SIZE 0.1
GLdouble CAR0(GLdouble u,GLdouble t=T);
GLdouble CAR1(GLdouble u,GLdouble t=T);
GLdouble CAR2(GLdouble u,GLdouble t=T);
GLdouble CAR3(GLdouble u,GLdouble t=T);

void Init_homework5();
void mouse_homework5_Cardinal(int button, int state, int x, int y);
void mouse_homework5_Bezier(int button, int state, int x, int y);
void Cardinal_line_displag();
void main_homework5(int argc, char**argv);
void display_nop();

long int fact(int n);
GLdouble Bernstein(GLdouble t, int i, int n = N);
void Bezier_line_display();