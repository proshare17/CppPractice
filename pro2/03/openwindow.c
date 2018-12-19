#include <GL/glut.h>


void Display(void);


int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitWindowSize(320,240);
	glutCreateWindow("サンプルその１");
	glutDisplayFunc(Display);
	
	glutMainLoop();

	return 0;
}



void Display(void){

}
