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
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("helle world");

	glutDisplayFunc(point_display);

	glutMainLoop();
	return 0;
}