/*
	ѧϰ�ʼ�
	1��reshape�úÿ��Ա���ͼ����ʾ��������

	2�����Ĺ��ֻ���������

	3���˽���gl_matrixmode���÷�

	4��glutInitDisplayMode(GLUT_DOUBLE)����˫������ʾģʽ��	glFlush();
	glutSwapBuffers();Ȼ����display��flush�󣬵��� glutSwapBuffers(); Ч����
	���ǿ�������GDIԪ��ͬʱ��������Ļ�ϣ��Ӷ������Ƶ��ˢ�µ��µĻ�����˸���⡣
	�ȼǵ�Ч������֮�����ڸ��ӵĻ�ͼ�����о����ˡ�

	5,glViewport(300, 0, 300, 300);�������ôӵ�����Windows������ѡ����ʾ�����򣬸�
	ʲô�ӵ�ͶӰû�а�ëǮ��ϵ����һ����������

	6,gluPerspective(75, (GLfloat)newWidth / newHeight, 0.1, 100);Ҫ�ǵ�װ������



*/