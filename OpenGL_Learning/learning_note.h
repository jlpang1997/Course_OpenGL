/*
	学习笔记
	1，reshape用好可以保持图形显示比例不变

	2，鼠标的滚轮还是有问题

	3，了解了gl_matrixmode的用法

	4，glutInitDisplayMode(GLUT_DOUBLE)开启双缓冲显示模式，	glFlush();
	glutSwapBuffers();然后在display中flush后，调用 glutSwapBuffers(); 效果是
	我们看到所有GDI元素同时出现在屏幕上，从而解决了频繁刷新导致的画面闪烁问题。
	先记得效果，总之是用在复杂的绘图操作中就是了。

	5,glViewport(300, 0, 300, 300);用来设置从弹出的Windows窗口中选择显示的区域，跟
	什么视点投影没有半毛钱关系就是一个分屏而已

	6,gluPerspective(75, (GLfloat)newWidth / newHeight, 0.1, 100);要记得装换类型



*/