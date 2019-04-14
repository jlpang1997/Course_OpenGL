#include"lab3.h"
#include<stdio.h>
#include<malloc.h>
#include<math.h>
char texture_file_name[11][100];//最多十个
Material material[11];//最多十个，0号舍弃

float vertex[10001][3];//最多一万个，舍弃0号

float texture_point[10001][2];//最多一万个，舍弃0号

float normal[10001][3];//最多一万个，舍弃0号

float scale[3];

int submodel_num;

int texture_id[10];

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
static GLdouble viewr = 2;
static GLdouble init_viewx = 0,
init_viewy = 0,
init_viewz = 2;
static GLdouble viewx = init_viewx,
viewy = init_viewy,
viewz = init_viewz;
int submodel_index = 2;

static int nx[] = { 1,0,0 };
static int ny[] = { 0,1,0 };
static int nz[] = { 0,0,1 };
static int n[3] = { ny[0],ny[1],ny[2]};

static  GLdouble init_theta = 0;
static GLdouble theta=init_theta;

void submodel_display()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(scale[0], scale[1], scale[2]);//纹理搞了半天，先不实现纹理，先把材质搞好了
	gluLookAt(viewx, viewy, viewz, 0, 0, 0, 0,1, 0);


	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	GLfloat diffuse0[] = { 1,1,1,1 };
	GLfloat ambient0[] = { 1,1,1,1 };
	GLfloat specular0[] = { 1,1,1, 1};
	GLfloat light0_pos[] = { 0,0.8,0.8,1 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);


	GLfloat light1_pos[] = { 0,-0.8,0.8,1 };
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION,light1_pos );
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);

	GLfloat light2_pos[] = { -0.8,0.8,-2,1 };
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular0);

	GLfloat light3_pos[] = { 0,-0.8,-2,1 };
	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular0);

	


	//int id= load_texture(texture_file_name[material[submodel[submodel_index].material_index].texture_file_index]);
	//glBindTexture(GL_TEXTURE_2D, id);
	glBindTexture(GL_TEXTURE_2D, texture_id[submodel_index]);
	{

		glRotated(theta, n[0], n[1], n[2]);
		if (submodel_index == 2)
		{
			
			glRotated(50, -1, 0, 0);
			glTranslated(-0.5, -0.5, 0);
		}
		glTranslated(0, 0, 0.9);
		glRotated(90, -1, 0, 0);
		
		glBegin(GL_TRIANGLES);
		for (int i = 1; i <= submodel[submodel_index].triangle_num;i++)
		{
			
			for (int j = 0; j < 9; j += 3)//这里从0开始
			{

				glTexCoord2fv(texture_point[submodel[submodel_index].triangle[i][j + 1]]);//加上贴图
				glVertex3fv(vertex[submodel[submodel_index].triangle[i][j]]);//画点

				glNormal3fv(normal[submodel[submodel_index].triangle[i][j+2]]);//设置法向
				
				glMaterialfv(GL_FRONT|GL_BACK, GL_AMBIENT, material[submodel[submodel_index].material_index].ambient);

				glMaterialfv(GL_FRONT | GL_BACK, GL_DIFFUSE, material[submodel[submodel_index].material_index].diffuse);

				glMaterialfv(GL_FRONT | GL_BACK, GL_SPECULAR, material[submodel[submodel_index].material_index].specular);

				glMaterialfv(GL_FRONT | GL_BACK, GL_EMISSION, material[submodel[submodel_index].material_index].emission);

				glMateriali(GL_FRONT | GL_BACK, GL_SHININESS, material[submodel[submodel_index].material_index].shininess);


			}
			
			
			

		}
		glEnd();
		glutSwapBuffers();

	}
	//glFlush(); //画点看看效果

	


	
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
	case 'a': 
	{
		theta -= 15;
		break;
	}
	case 'd':
	{
		theta += 15;
		break;
	}
	case 's': 
	{
		viewx = init_viewx; 
		if (viewz > 0)
		{
			if (viewy > 0)
			{
				viewz += change_size;
			}
			else
			{
				viewz -= change_size;
			}
			viewy -= change_size;
		}
		else 
		{
			if (viewy > 0)
			{
				viewz -= change_size;
			}
			else
			{
				viewz += change_size;
			}
			viewy += change_size;
		}
		 break;
	}
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

		n[0] = ny[0];
		n[1] = ny[1];
		n[2] = ny[2];

		theta = init_theta;

	}
	default:
		break;
	}
	submodel_display();
}

GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	height = -height;//为什么会读出一个-256还是不清楚
	fseek(pFile, 54, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}
	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}


	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	free(pixels);
	return texture_ID;

}

//glBindTexture(GL_TEXTURE_2D, texture_ID);//绑定纹理

////一大堆参数设置，暂时不了解每个参数的意义
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
//	GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
//free(pixels);
//return texture_ID;
void Idle_lab3(void)
{
	theta += 0.3;
	if (theta >= 360)
		theta = 0;
	submodel_display();
}

void Init_lab3()
{
	glClearColor(1, 1, 1, 1);
	Get_Model();
	for (int i = 1; i <= submodel_num; i++)
	{
		texture_id[i] = load_texture(texture_file_name[material[submodel[i].material_index].texture_file_index]);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

}
void shape_lab3(int w, int h)
{
	glViewport(0, 0, w, h);//取全屏
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w > h)
	{
		glOrtho(-1*(GLdouble)w/ (GLdouble)h, 1* (GLdouble)w/ (GLdouble)h, -1, 1, 0, 100);
	}
	else
	{
		glOrtho(-1 , 1 , -1* (GLdouble)h/ (GLdouble)w, 1* (GLdouble)h/ (GLdouble)w, 0, 100);
	}
	//submodel_display();
	
}

void main_lab3(int  argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("lab3");
	Init_lab3();
	//glutMouseFunc(mouse_lab3);
	glutKeyboardFunc(key_lab3);
	glutReshapeFunc(shape_lab3);
	//glutIdleFunc(&Idle_lab3);
	glutDisplayFunc(submodel_display);
	glutMainLoop();
}