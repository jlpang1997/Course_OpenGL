#include"lab1.h"
#include"GL/glut.h"
using namespace std;
void set_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2i(x, y);
	glEnd();

}

int xc = 60;
int yc = 60;
int r = 50;

void Cycle_display()
{
	int x = 0;
	int y = r;
	double p = 5 / 4 - r;
	glClear(GL_COLOR_BUFFER_BIT);
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