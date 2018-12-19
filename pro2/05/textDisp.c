
//
// Edit textDisp()
//
#include <GL/glut.h>
#include <stdio.h>
#include <string.h> // strlen()


void Display(void);
void Reshape(int,int);
void Timer(int);
void PrintText(int, int, char *);

char message[]="Welcome to Glut World!";
int counter=0;
//
//
//
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 250);
	glutCreateWindow("Testing PrintText()") ;
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutTimerFunc(1000,Timer,0);
	glutInitDisplayMode(GLUT_RGBA);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutMainLoop();

	return(0);
}


//
// Update Window Display
//
void Display(void)
{
	static	char num[5];

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(255, 200, 200);
	PrintText(50, 120, message);

	sprintf(num,"%d",counter);
//	glColor3ub(255, 200, 200);
	PrintText(300, 120, num);

	glFlush();
}


//
// Update Coordinate if Window Size Update occured
//
void Reshape(int w, int h)
{
	glViewport (0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0 , w, 0, h);
	glScaled (1, -1, 1);
	glTranslated (0, -h, 0);
	glutReshapeWindow (500 , 250); // Fixing Window Size
}


//
// Display Strings
//
void PrintText(int x, int y, char *s)
{
	int i , l;


	glRasterPos2i(x , y);

	l = strlen(s);


	for (i = 0 ; i < l ; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}
}

//
// Timer Interrupt
//
void Timer(int value)
{
	counter++;
	glutPostRedisplay();
	glutTimerFunc(1000, Timer, value);
}
