#include"lab3.h"
#include<stdio.h>

char texture_file_name[11][100];//最多十个
Material material[11];//最多十个，0号舍弃

float vertex[10001][3];//最多一万个，舍弃0号

float texture_point[10001][2];//最多一万个，舍弃0号

float normal[10001][3];//最多一万个，舍弃0号

float scale[3];

int submodel_num;

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

	
	fscanf(fp, "%d", &submodel_num);


	for (int i = 0; i < 3; i++)
	{
		fscanf(fp, "%f", &scale[i]);
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
				fscanf(fp, "%d", &submodel[i].triangle[j][k]);
			}
		}
	}
}
static GLdouble init_viewx = 0,
init_viewy = 0,
init_viewz = 2;
static GLdouble viewx = init_viewx,
viewy = init_viewy,
viewz = init_viewz;
int submodel_index = 1;
void submodel_display()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 2, 0, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(scale[0], scale[1], scale[2]);//纹理搞了半天，先不实现纹理，先把材质搞好了
	gluLookAt(viewx, viewy, viewz, 0, 0, 0, 0, 1, 0);


	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	GLfloat diffuse0[] = { 1,1,1,1 };
	GLfloat ambient0[] = { 0,1,0,1 };
	GLfloat specular0[] = { 0,1.0,1, 1};
	GLfloat light0_pos[] = { 0,8.0,8.0,8.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);


	GLfloat light1_pos[] = { -0.8,0.8,0.8,0 };
	GLfloat ambient1[] = { 1,0,0,1 };
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION,light1_pos );
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);

	
	{
		for (int i = 1; i <= submodel[submodel_index].triangle_num;i++)
		{
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < 9; j += 3)//这里从0开始
			{

				glVertex3fv(vertex[submodel[submodel_index].triangle[i][j]]);//先画点
				
				glNormal3fv(normal[submodel[submodel_index].triangle[i][j+2]]);
				
				glMaterialfv(GL_FRONT|GL_BACK, GL_AMBIENT, material[submodel[submodel_index].material_index].ambient);

				glMaterialfv(GL_FRONT | GL_BACK, GL_DIFFUSE, material[submodel[submodel_index].material_index].diffuse);

				glMaterialfv(GL_FRONT | GL_BACK, GL_SPECULAR, material[submodel[submodel_index].material_index].specular);

				glMaterialfv(GL_FRONT | GL_BACK, GL_EMISSION, material[submodel[submodel_index].material_index].emission);

				glMateriali(GL_FRONT | GL_BACK, GL_SHININESS, material[submodel[submodel_index].material_index].shininess);


			}
			glEnd();
			
			

		}
	}
	glFlush(); //画点看看效果

	



	
}
GLdouble change_size = 0.2;
void mouse_lab3(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		viewy += change_size;
	}
	 if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		viewy -= change_size;
	}
	submodel_display();
}

void key_lab3(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': viewx -= change_size; break;
	case 'd': viewx += change_size; break;
	case 's': viewy -= change_size; break;
	case 'w': viewy += change_size; break;
	case 'z': viewz -= change_size; break;
	case 'x': viewz += change_size; break;
	case 'e':
	{
		submodel_index++;
		if (submodel_index == submodel_num+1)
			submodel_index = 1;
		viewx = init_viewx;
		viewy = init_viewy;
		viewz = init_viewz;

	}
	default:
		break;
	}
	submodel_display();
}
void Init_lab5()
{
	glClearColor(1, 1, 1, 1);

}

void main_lab3(int  argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("lab3");


	glEnable(GL_DEPTH_TEST);
	glutMouseFunc(mouse_lab3);
	glutKeyboardFunc(key_lab3);
	Get_Model();
	Init_lab5();
	glutDisplayFunc(submodel_display);
	glutMainLoop();
}
