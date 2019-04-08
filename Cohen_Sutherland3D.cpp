
#include <gl/glut.h>

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
#define BACK 16
#define FRONT 32
using namespace std;
int x1 = -180, y11 = 180, z1 = 0,
	x2 = 200,  y2 = 150,  z2=0,
	//(x1,y11,z1)、(x2,y2,z2)为直线段的两个端点，

	XL = -100, XR = 100,//XL为左边界，XR为右边界

	YB = -100, YT = 100,//YB为下边界，YT为上边界

	ZF = 100,  ZB=-100; //,ZF为前边界，ZB为后边界
 

int x1_init = x1, y11_init = y11,
	x2_init = x2, y2_init = y2,
	z1_init = z1, z2_init = z2;
int encode(int x, int y,int z)
{
	int c = 0;
	if (x < XL) c |= LEFT;
	if (x > XR) c |= RIGHT;
	if (y < YB) c |= BOTTOM;
	if (y > YT) c |= TOP;
	if (z < ZB) c |= BACK;
	if (z > ZF) c |= FRONT;
	return c;
}

void CS_LineClip()  //Cohen-Sutherland裁剪算法
{
	int x, y,z;
	int code1, code2, code;
	code1 = encode(x1, y11,z1);
	code2 = encode(x2, y2,z2);

	while (code1 != 0 || code2 != 0)
	{
		if (code1 & code2)
			return;
		if (code1 != 0)
			code = code1;
		else
			code = code2;

		if (LEFT & code)
		{
			x = XL;
			y = y11 + (y2 - y11)*(XL - x1) / (x2 - x1);
			z = z1 + (z2-z1)*(XL - x1) / (x2-x1);
		}
		else if (RIGHT & code)
		{
			x = XR;
			y = y11 + (y2 - y11)*(XR - x1) / (x2 - x1);
			z = z1 + (z2 - z1)*(XR - x1) / (x2 - x1);
		}
		else if (BOTTOM & code)
		{
			y = YB;
			x = x1 + (x2 - x1)*(YB - y11) / (y2 - y11);
			z=z1+ (z2 - z1)*(YB - y11) / (y2 - y11);
		}
		else if (TOP & code)
		{
			y = YT;
			x = x1 + (x2 - x1)*(YT - y11) / (y2 - y11);
			z = z1 + (z2 - z1)*(YT - y11) / (y2 - y11);
		}
		else if (BACK & code)
		{
			z = ZB;
			x = x1 + (x2 - x1)*(ZB - z1) / (z2 - z1);
			y = y11 + (y2 - y11)*(ZB - z1) / (z2 - z1);
		}
		else if (FRONT & code)
		{
			z = ZF;
			x = x1 + (x2 - x1)*(ZF - z1) / (z2 - z1);
			y = y11 + (y2 - y11)*(ZF - z1) / (z2 - z1);
		}


		if (code == code1)
		{
			x1 = x; y11 = y; z1 = z; code1 = encode(x1, y11,z1);
		}
		else
		{
			x2 = x; y2 = y; z2 = z; code2 = encode(x2, y2,z2);
		}
	}

}


void myinit()  //初始化函数
{
	glClearColor(1.0, 1.0, 1.0, 0.0);  //设置背景颜色
	glMatrixMode(GL_PROJECTION);       // 设置投影参数
	glOrtho(-200, 200, -200, 200,0,1000); // 设置场景的大小
	CS_LineClip();  //执行一次裁剪算法
}
void cube_display()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glColor4f(0, 1, 0, 0.5);
	glBegin(GL_POLYGON);
	{
		glVertex3i(XL, YB, ZF);
		glVertex3i(XL, YB, ZB);
		glVertex3i(XL, YT, ZB);
		glVertex3i(XL, YT, ZF);
	}
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);
	{
		glVertex3i(XR, YB, ZF);
		glVertex3i(XR, YB, ZB);
		glVertex3i(XR, YT, ZB);
		glVertex3i(XR, YT, ZF);
	}
	glEnd();
	glFlush();


	glBegin(GL_POLYGON);
	{
		glVertex3i(XL, YB, ZF);
		glVertex3i(XL, YB, ZB);
		glVertex3i(XR, YB, ZB);
		glVertex3i(XR, YB, ZF);
	}
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	{
		glVertex3i(XL, YT, ZF);
		glVertex3i(XL, YT, ZB);
		glVertex3i(XR, YT, ZB);
		glVertex3i(XR, YT, ZF);
	}
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);
	{
		glVertex3i(XL, YT, ZB);
		glVertex3i(XL, YB, ZB);
		glVertex3i(XR, YB, ZB);
		glVertex3i(XR, YT, ZB);
	}
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);
	{
		glVertex3i(XL, YT, ZF);
		glVertex3i(XL, YB, ZF);
		glVertex3i(XR, YB, ZF);
		glVertex3i(XR, YT, ZF);
	}
	glEnd();
	glFlush();
}
int view_x = 50;
int view_y = 0;
void mydisplay()  //显示函数
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(view_x, view_y, 200, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT);
	//绘制方形边界
	//glColor3f(1.0, 0.0, 0.0);
	//glPointSize(2);
	////glBegin(GL_LINE_LOOP);
	////glVertex2i(XL, YT);//画出裁剪窗口
	////glVertex2i(XL, YB);
	////glVertex2i(XR, YB);
	////glVertex2i(XR, YT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	//glEnd();
	//glFlush();
	//绘制未裁剪前的线段

	//绘制立方体边界
	cube_display();


    /////////////////////////////////
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3i(x1_init, y11_init,z1_init);
	glVertex3i(x2_init, y2_init,z2_init);
	glEnd();
	glFlush();
	//绘制裁剪后的线段
	if (encode(x1, y11, z1) == 0 && encode(x2, y2, z2))
	{
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3i(x1, y11, z1);
		glVertex3i(x2, y2, z2);
		glEnd();
		glFlush();
	}


	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}
void mymouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		view_y += 10;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		view_y -= 10;
	}
	mydisplay();
}
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(400, 400);
//	glutCreateWindow("Cohen-Sutherland裁剪算法");
//	glutMouseFunc(mymouse);
//	myinit();
//	glutDisplayFunc(&mydisplay);
//	glutMainLoop();
//	return 0;
//}