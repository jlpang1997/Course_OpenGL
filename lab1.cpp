#include"lab1.h"
#include"GL/glut.h"
using namespace std;
void set_pixel(int x, int y)
{
	//glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2i(x, y);
	glEnd();
	for (int i = 0; i <100000; i++)
	{
		glFlush();
	}
	
}

int xc = 60;
int yc = 60;
int r = 50;

void Cycle_display()
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	gluLookAt(60, 60, 10,60,60,0, 0, 1, 0);

	glMatrixMode(GL_PROJECTION);
	glOrtho(-60, 60, -60, 60,0,100);
	//gluOrtho2D有毒，还是不用了吧

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	int x = 0;
	int y = r;
	double p = 5 / 4 - r;
	while (x < y)
	{
		set_pixel(x + xc, y + yc);
		set_pixel(y + xc, x + yc);
		set_pixel(-x + xc, -y + yc);
		set_pixel(-y + xc, -x + yc);

		set_pixel(-x + xc, y + yc);
		set_pixel(y + xc, -x + yc);
		set_pixel(x + xc, -y + yc);
		set_pixel(-y + xc, x + yc);
		if (p < 0)
		{
			x = x + 1;
			p += 2 * x + 1;
		}
		else 
		{
			x++;
			y--;
			p += 2 * x + 1 - 2 * y;
		}

	}
	glFlush();

}