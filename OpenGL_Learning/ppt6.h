#pragma once
#include"gl/glut.h"
class wcPt2D {
public:
	GLfloat x;
	GLfloat y;
};
void init(void);
void triangle(wcPt2D *verts);
void displayFcn(void);
void main_ppt6(int argc, char ** argv);