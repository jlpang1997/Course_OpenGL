#pragma once
#include"gl/glut.h"
struct Material
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	float shininess;
	int texture_file_index;
};

struct Model
{
	int triangle_num;
	int material_index;
	unsigned int triangle[10001][9];//ÿ��ģ�����10000��������
};
void Get_Model();
void submodel_display();
void Init_lab5();
void main_lab3(int  argc, char** argv);