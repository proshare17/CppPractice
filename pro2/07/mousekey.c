#include <GL/glut.h>
#include <stdio.h>


void Display(void);
void Reshape(int, int);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int); // Added
void PassiveMotion(int, int);
void Motion(int, int);
void Entry(int);


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(320, 240);
	glutCreateWindow("Mouse Sample");
	glutDisplayFunc(Display);
        glutKeyboardFunc(Keyboard); // Added
	glutReshapeFunc(Reshape);
	glutInitDisplayMode(GLUT_RGBA);
	glClearColor(0.0, 0.0, 1.0, 1.0);


	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(PassiveMotion);
	glutMotionFunc(Motion);
	glutEntryFunc(Entry);

	glutMainLoop();

	return(0);
}
//
//
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
//
//
//
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glScaled(1, -1, 1);
	glTranslated(0, -h, 0);
}
//
//
void Mouse(int b, int s, int x, int y)
{
	if (b == GLUT_LEFT_BUTTON)
	{
		if (s == GLUT_UP ) printf("Left-Button Up");
		if (s == GLUT_DOWN) printf("Left-Button Down");
	}

	if (b == GLUT_MIDDLE_BUTTON)
	{
		if (s == GLUT_UP ) printf("Middle-Button Up");
		if (s == GLUT_DOWN) printf("Middle-Button Down");
	}

	if (b == GLUT_RIGHT_BUTTON)
	{
		if (s == GLUT_UP ) printf("Center-Button Up");
		if (s == GLUT_DOWN) printf(" Center-Button Down");
	}

	printf(" at (%d, %d) \n", x, y);
}


//
//
//
void PassiveMotion(int x, int y)
{
	printf("PassiveMotion : (x, y) = (%d, %d)\n", x, y);
}
//
//
void Motion(int x, int y)
{
	printf("Motion : (x, y) = (%d, %d)\n", x, y);
}

//
//
void Entry(int s)
{
	if (s == GLUT_ENTERED) printf("Entered\n");
	if (s == GLUT_LEFT ) printf("Exited\n");
}

//
// Processing Key Input
//
void Keyboard(unsigned char key, int x, int y)
{
	if ((key == 'q') || (key == 27))
	{
		printf("Finished\n");
		exit(0);
	}
}

