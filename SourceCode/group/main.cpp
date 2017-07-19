#include "render.h"

//主程序入口
int main(int argc, char* argv[]) {
	//GLeeInit();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900, 600);
	glutCreateWindow("cg");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyAction);	
	init();
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}