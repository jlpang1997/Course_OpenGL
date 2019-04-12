// Texture.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdlib.h>//妈的，这个头文件必须在glut.h前面
#include"gl/glut.h"
#include<stdio.h>
#include<iostream>

#define FileName "../bd378f0.bmp"
using namespace std;

static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 400, 0, 400, 0, 100);
	//绘制像素
	//glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
	glBegin(GL_POINTS);
	for(int i=0;i<imageheight;i++)
	{
		for (int j = 0; j < imagewidth*3;j+=3)
		{
			glColor3ub(pixeldata[i*imagewidth*3+j ], pixeldata[i*imagewidth*3 + j + 1], pixeldata[i*imagewidth*3 + j+2]);
			glVertex2d(j / 3,256-i);
		}
	}
	glEnd();



	//---------------------------------
	glFlush();
	glutSwapBuffers();
}
void LoadTexture_file(const char *filepath)
{
	//打开文件
	FILE* pfile = fopen(filepath, "rb");
	if (pfile == 0)
		exit(0);

	//读取图像大小
	fseek(pfile, 0x0012, SEEK_SET);//先跳18个字节？
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);
	imageheight = -imageheight;

	//计算像素数据长度
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;

	//读取像素数据
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);

	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);
	for(int i=0;i<imageheight;i++)
		for(int j=0;j<imagewidth*3;j+=3)
		{
			swap(pixeldata[i*imagewidth * 3 + j], pixeldata[i*imagewidth * 3 + j + 2]);
			//把bmp文件的rgb顺序由bgr改回rgb
		}


	//关闭文件
	fclose(pfile);
}
int main(int argc, char* argv[])
{
	
	LoadTexture_file("../bd378f0.bmp");
	//初始化glut运行
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow(FileName);
	glutDisplayFunc(&display);
	glutMainLoop();
	//-------------------------------------
	free(pixeldata);
	return 0;
	exit(0);
}