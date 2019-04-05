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


void tiaoseban_display(void)//����һ����ɫ�壬ţ��
{
	const int n = 10;
	const GLfloat R = 0.5;
	const GLfloat PI = 3.1415926536f;
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

//����仯
//1,ʵ�ʱ任˳���ָ����˳�����෴��

//һЩ��ʵ�ֵ�ģ��
void model_display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 10; i++)
	{
		glPushMatrix();
		glTranslatef(0, 0.8 - 0.4*i, 0);
		glColor3f(i / 10, 1, 0);
		switch (i)
		{
			case 0:
			{
				glutWireSphere(0.2, 100, 100);//��״�򣬰뾶������Ϊ������������С��1
				break;
			}
			case 1:
			{
				glutWireCone(0.2,0.2,10,10);//��״�򣬰뾶������Ϊ������������С��1
				break;
			}
			case 2:
			{
				glutWireCube(0.2);//��״�򣬰뾶������Ϊ������������С��1
				break;
			}
			case 3:
			{
				glutWireTeapot(0.2);//��״�򣬰뾶������Ϊ������������С��1
				break;
			}
			case 4:
			{
				glutWireTorus(0.05,0.1,10,10);//��״�򣬰뾶������Ϊ������������С��1
				break;
			}
		}
		glPopMatrix();
		glFlush();
	}

}

//��������ϵ�͹۲�����ϵ
void look_model_display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//��������ϵ
	//��OpenGL�У���������ϵ������Ļ����Ϊԭ��(0, 0, 0)������ʼ�ղ���ġ�
	//�������Ļ������ұ���x���ᣬ������y���ᣬ��Ļָ�����Ϊz���ᡣ���ȵ�λ�������������ڷ�Χ���˵�λǡ����(-1, -1)��(1, 1)������Ļ���½�����Ϊ
		//�� - 1�� - 1�������Ͻ�����Ϊ��1, 1�������ǲ����˹�һ���Ľ��
	glColor3f(1, 0, 0);
	{
		glMatrixMode(GL_MODELVIEW);//gl_lookat������ģ����ͼ��Ҳ����˵����֮ǰ��������һ������
		//glLoadIdentity();//ջ��Ϊ��λ��
		//gluLookAt(0, 0, 1,
		//		  0,0,0,
		//	0,1,0);//���������ˣ�ǰ�����������۾���λ�ã�
					//�м����������ǿ��ķ���
					//�������������ͷ�ĳ���
		glTranslatef(0.4, 0.2,0);
		glRotatef(30, 0, 0, 1);
		glScalef(0.5, 1.5, 0.5);


		glutWireTeapot(0.3);
		glFlush();

	}
}

//ͶӰ�任
void touying_display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_PROJECTION);//����ͶӰ
	//glOrtho(-1, 1, -1, 1, 0, 20);//���þ����Ӿ���
	//glFrustum(-1, 1, -1, 1, 1, 20);//������̨�Ӿ���
	gluPerspective(60, 1, 1, 20);//ͬ��

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0,0,0);
	glColor3f(1, 0, 0);
	glutWireTeapot(5);
	glFlush();
	


}

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
	//glutDisplayFunc(myDisplay);

	//glutDisplayFunc(model_display);
	//glutDisplayFunc(look_model_display);
	glutDisplayFunc(touying_display);

	glutMainLoop();
	return 0;
}