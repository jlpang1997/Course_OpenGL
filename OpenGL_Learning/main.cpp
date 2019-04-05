#include"gl/glut.h"
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//�������ؿ���̨
//���ŵ�һ��

//���
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
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("helle world");

	//glutDisplayFunc(point_display);
	//glutDisplayFunc(line_display);
	glutDisplayFunc(polygon_display);

	glutMainLoop();
	return 0;
}