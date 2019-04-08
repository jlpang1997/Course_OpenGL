#pragma once
#include"gl/glut.h"


void point_display();
void line_display();
void polygon_display();

void line_color_display();
void tiaoseban_display(void);
void model_display();
void look_model_display();
void touying_display();

//reshapeµÄÑ§Ï°
void myreshape(int w, int h);

void reshape_display();
void mymouse(int btn, int state, int x, int y);
void myDisplay(void);
int main_learning001(int argc, char**);
void draw(int x, int y);

void mymenu(int value);
void processTopMenu();
void processSizeMenu();