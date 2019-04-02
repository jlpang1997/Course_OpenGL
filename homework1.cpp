#include"gl/glut.h"
#include"homework1.h"
#include<math.h>
void setPixel(int x, int y, float p)
{
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2i(x, y);
	glEnd();
}
void function_display()//二次函数用中点画线算法实现  为了画出左右两边函数图像，坐标原点为（50,0）
{

	int x, y;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);

	x = 50;
	y = 100;
	int p = -3;
	while (x <= 60)
	{
		glVertex2i(x, y);
		glVertex2i(100 - x, y);
		y--;
		if (p >= 0)
		{
			p = p - 4;
		}
		else
		{
			x++;
			p = p + (x - 50) * 8 - 4;
		}
	}

	glEnd();
	glFlush();
}

void line_display()//中点画线算法实现
{
	//测试样例

	int x1 = 0, y1 = 0, x2 = 100, y2 = 40;//0<=k<=1
	//int x1 = 0, y1 = 0, x2 = 20, y2 = 100;//k>1
	//int x1 = 0, y1 = 100, x2 = 100, y2 = 60;//-1<=k<0
	//int x1 = 0, y1 = 100, x2 = 20, y2 = 0;//k<-1



	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int x, y;
	int tmpx = 2 * dx, tmpy = 2 * dy;



	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 0.0, 0.0);
	//glBegin(GL_POINTS);

	if (x1 > x2)
	{
		x = x2;
		y = y2;
		x2 = x1;
		y2 = y1;
	}
	else {
		x = x1;
		y = y1;
	}//x,y选最左边的像素点
	int p;
	double area = dx;
	if (y <= y2 && dx >= dy)//0<=k<=1
	{
		p = dx - tmpy;
		while (x <= x2)
		{
			setPixel(x, y, area / (2 * dx));
			//glVertex2i(x, y);
			x++;
			if (p >= 0)
			{
				p += -tmpy;
				area += tmpy;
			}
			else
			{
				y++;
				p += tmpx - tmpy;
				area += tmpy - tmpx;
			}
		}
	}
	else if (y <= y2 && dx < dy)//k>1
	{
		p = tmpx - dy;
		while (x <= x2)
		{
			//glVertex2i(x, y);
			setPixel(x, y, area / (2 * dy));
			y++;
			if (p >= 0)
			{
				x++;
				area += tmpy - tmpx;
				p += tmpx - tmpy;
			}
			else
			{
				area += -tmpx;
				p += tmpx;
			}
		}
	}
	else if (y >= y2 && dx >= dy)//0>=k>=-1
	{
		p = -dx + tmpy;
		while (x <= x2)
		{
			//glVertex2i(x, y);
			setPixel(x, y, area / (2 * dx));
			x++;
			if (p >= 0)
			{
				y--;
				area += -tmpy + tmpx;
				p += -tmpx + tmpy;
			}
			else
			{
				area += -tmpy;
				p += tmpy;
			}
		}
	}
	else//k<-1
	{
		p = -tmpx + dy;
		while (x <= x2)
		{
			//glVertex2i(x, y);
			setPixel(x, y, area / (2 * dy));
			y--;
			if (p >= 0)
			{
				p += -tmpx;
				area += tmpx;
			}
			else
			{
				//y++;
				p += -tmpx + tmpy;
				x++;
				area += -tmpy + tmpx;
			}
		}
	}
	//glEnd();
	glFlush();
}