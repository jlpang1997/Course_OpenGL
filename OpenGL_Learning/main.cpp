#include"gl/glut.h"
#include<math.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//�������ؿ���̨
//���ŵ�һ��

//�������ͼԪ���㡢�ߡ������
void point_display()
{
	glPointSize(10);//ָ����С����λ����
	glBegin(GL_POINTS);
	{
		GLfloat v[2] = { 0,0.5 };
		glVertex2f(0.0f, 0.0f);//��ʾ��Ļ���ģ���Ϊԭ��
		glVertex2fv(v);//ָ�룬��ʵ���Ǹ����飬һά����

		//glVertex2s(10,10);//Ϊʲô������У�
		//GLshort v[2] = { 10,20 };
		//glVertex2sv(v);
							   //glVertex2f(0.0f, 0.5f);//1.0��ʾ��Ļ����
		//glVertex2f(0.5f, 0.25f);
	}
	glEnd();
	glFlush();
}
void line_display()
{
	//GL_LINES ��������ԣ����Ա�����ż������
	//GL_LINE_STRIP ��β���������պ�
	//GL_LINE_LOOP ��β�������ұպ�
	glLineWidth(3);//�趨���

	glEnable(GL_LINE_STIPPLE);//��������ģʽ

	glLineStipple(3, 0b1001001001001000);//������������
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(-0.8, -0.5);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.8, 0);
		glVertex2f(-0.5, 0);
		glVertex2f(-0.8, 0.5);
		glVertex2f(-0.3, 0.5);
	}
	glEnd();
	glFlush();
}
void polygon_display()//openglֻ�ܻ�͹�����
{
	glPointSize(10);
	glFrontFace(GL_CCW);//��ʱ��Ϊ����
	glFrontFace(GL_CW);//˳ʱ��
	//glBegin(GL_POLYGON);
	//glBegin(GL_TRIANGLES);
	//glBegin(GL_TRIANGLE_STRIP);
	glPolygonMode(GL_FRONT, GL_POINT);//GL_POINT����������ģʽ�ģ���GL_POINTS�����������
	glPolygonMode(GL_BACK, GL_FILL);//��˵�������ǻ���ά��ʱ�򣬿������Ǳ���
	glBegin(GL_QUADS);//�ı���
	{
		glVertex2f(0, -0.1);
		glVertex2f(-0.5, 0);
		glVertex2f(0, 0.5);
		glVertex2f(0.5, 0);
		glVertex2f(0, -0.5);

	}
	glEnd();
	glFlush();
}

//�����ɫ
void line_color_display()//RGBAģʽ��������ɫ����ģʽ���ǰ���ɫֵ������һ�ű����棬�õ�ʱ��ֱ��ȥ��ɫָ�����
{
	glClearColor(1, 1, 1,1);//������Ļ��ɫ��ɫ
	glClear(GL_COLOR_BUFFER_BIT);//ʹ�����õ���ɫ��Ϊ��Ļ��ɫ�����������ʹ��

	glColor3f(0, 0, 1);//
	glLineWidth(5);
	glPolygonMode(GL_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.5, 0.5);
		glVertex2f(0, 0.5);
		glVertex2f(0, 0);
		glVertex2f(-0.5, 0);
	}
	glEnd();

	glLineWidth(5);
	glShadeModel(GL_FLAT);//ȡ��һ����ɫ
	glShadeModel(GL_SMOOTH);//����
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex2f(0.5, 0);
		glColor3f(0, 1, 0);
		glVertex2f(1.0, 0);
	}
	glEnd();
	glFlush();


	glFlush();


}

const int n = 10;
const GLfloat R = 0.5;
const GLfloat PI = 3.1415926536f;
void myDisplay(void)//����һ����ɫ�壬ţ��
{
	glBegin(GL_POLYGON);
	{
		glColor3f(1, 1, 1);
		glVertex2f(0, 0);
		for (int i = 1; i < 8; i++)
		{
			glColor3f(i & 0x004, i & 0x002, i & 0x001);//�������̫������
			glVertex2f(R*cos(i*PI / 3), R*sin(i*PI / 3));//�����˸�����
		}
	}
	glEnd();

	glFlush();
}

//


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("helle world");

	//glutDisplayFunc(point_display);
	//glutDisplayFunc(line_display);
	//glutDisplayFunc(polygon_display);
	//glutDisplayFunc(line_color_display);
	glutDisplayFunc(myDisplay);

	glutMainLoop();
	return 0;
}