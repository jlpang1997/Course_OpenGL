#pragma once
#include"gl/glut.h"
void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc);

void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);

void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m);

void display();

void myReshape(int w, int h);

int main_homework3(int argc, char**argv);