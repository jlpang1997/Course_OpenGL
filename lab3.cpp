#include"lab3.h"
#include<stdio.h>

char texture_file_name[11][100];//最多十个
Material material[11];//最多十个，0号舍弃

float vertex[10001][3];//最多一万个，舍弃0号

float texture_point[10001][2];//最多一万个，舍弃0号

float normal[10001][3];//最多一万个，舍弃0号

float scale[3];

Model submodel[10];//最多十个子模型
void Get_Model()
{
	FILE *fp;
	fp = fopen("luweiqi.txt", "r");
	if (!fp)
	{
		printf("file open failed.");
		exit(0);
	}

	int texture_num;
	fscanf(fp,"%d", &texture_num);
	
	for (int i = 1; i <=texture_num; i++)//因为文件的编号都是1开始的，为了统一，方便，所以舍弃0号地址
	{
		fscanf(fp, "%s", texture_file_name[i]);
	}

	int material_num;
	fscanf(fp, "%d", &material_num);
	
	for (int i = 1; i <= material_num; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fscanf(fp, "%f", &material[i].ambient[j]);
		}
		for (int j = 0; j < 4; j++)
		{
			fscanf(fp, "%f", &material[i].diffuse[j]);
		}
		for (int j = 0; j < 4; j++)
		{
			fscanf(fp, "%f", &material[i].specular[j]);
		}
		for (int j = 0; j < 4; j++)
		{
			fscanf(fp, "%f", &material[i].emission[j]);
		}
		fscanf(fp, "%f",&material[i].shininess);
		fscanf(fp, "%d", &material[i].texture_file_index);
	}

	int vertex_num;
	fscanf(fp, "%d", &vertex_num);

	for (int i = 1; i <= vertex_num; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fscanf(fp, "%f", &vertex[i][j]);
		}
	}

	int texture_point_num;
	fscanf(fp, "%d", &texture_point_num);

	for (int i = 1; i <= texture_point_num; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			fscanf(fp, "%f", &texture_point[i][j]);
		}
	}

	int normal_num;
	fscanf(fp, "%d", &normal_num);

	for (int i = 1; i <= normal_num; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fscanf(fp, "%f", &normal[i][j]);
		}
	}

	int submodel_num;
	fscanf(fp, "%d", &submodel_num);


	for (int i = 0; i < 3; i++)
	{
		fscanf(fp, "%d", &scale[i]);
	}

	for (int i = 1; i <= submodel_num; i++)
	{
		int triangle_num;
		fscanf(fp, "%d",&triangle_num);
		submodel[i].triangle_num = triangle_num;
		fscanf(fp, "%d", &submodel[i].material_index);
		for (int j = 1; j <= triangle_num; j++)
		{
			for (int k = 0; k < 9; k++)//注意，这里三角形的九个分量从0算起，不一致有可能会导致错误
			{
				fscanf(fp, "%d", &submodel[i].triangle[k]);
			}
		}
	}
}