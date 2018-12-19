//
// OpenGL Primitive Display
//
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define WIDTH 320
#define HEIGHT 260


void Display(void);
void Reshape(int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int, int, int);


int mode = 4;
// 0: GL_POINTS
// 1: GL_LINES
// 2: GL_LINE_STRIP
// 3: GL_LINE_LOOP
// 4: GL_TRIANGLEE
// 5: GL_TRIANGLE_STRIP
// 6: GL_TRIANGLE_FAN
// 7: GL_QUADS
// 8: GL_QUAD_STRIP
// 9: GL_POLYGON

int main(int argc, char **argv)
{
	glutInit(&argc , argv);
	glutInitWindowSize(WIDTH , HEIGHT);
	glutCreateWindow("Test of OpenGL Primitives");
	glutInitDisplayMode(GLUT_RGBA);
	glClearColor(0.3, 0.3, 0.8, 1.0);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);

	glutMainLoop();

	return(0);
}


//
// Redefinition of Coordinate if occurs Resize Window
//
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glScaled (1, -1, 1);
	glTranslated(0, -h, 0);
	glutReshapeWindow(WIDTH, HEIGHT);
}


//
// Refresh Window Display
//
void Display(void)
{

	int a[] = { GL_POINTS , GL_LINES ,
		GL_LINE_STRIP , GL_LINE_LOOP ,
		GL_TRIANGLES , GL_TRIANGLE_STRIP ,
		GL_TRIANGLE_FAN , GL_QUADS ,
		GL_QUAD_STRIP, GL_POLYGON} ;
	char s[][20]= { "GL_POINTS", "GL_LINES",
		"GL_LINE_STRIP", "GL_LINE_LOOP",
		"GL_TRIANGLES" , "GL_TRIANGLE_STRIP" ,
		"GL_TRIANGLE_FAN" , "GL_QUADS" ,
		"GL_QUAD_STRIP", "GL_POLYGON"};
	int i ;
	int x [8] , y[8];


	if (mode <= 3) // GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP
	{
		x[0] = 50;
		y[0] = 50;
		x[1] = 150;
		y[1] = 50;
		x[2] = 50;
		y[2] = 150;
		x[3] = 150;
		y[3] = 150;
		x[4] = -1;
		y[4] = -1;
		x[5] = -1;
		y[5] = -1;
		x[6] = -1;
		y[6] = -1;
		x[7] = -1;
		y[7] = -1;
	}

	if (mode == 4) // GL_TRIANGLES
	{
		x[0] = 50;
		y[0] = 50;
		x[1] = 150;
		y[1] = 50;
		x[2] = 50;
		y[2] = 150;
		x[3] = 150;
		y[3] = 150;
		x[4] = 250;
		y[4] = 50;
		x[5] = 250;
		y[5] = 150;
		x[6] = -1;
		y[6] = -1;
		x[7] = -1;
		y[7] = -1;
	}

	if (mode == 5) // GL_TRIANGLE_STRIP
	{
		x[0] = 50;
		y[0] = 50;
		x[1] = 150;
		y[1] = 50;
		x[2] = 150;
		y[2] = 50;
		x[3] = 150;
		y[3] = 150;
		x[4] = 250;
		y[4] = 50;
		x[5] = -1;
		y[5] = -1;
		x[6] = -1;
		y[6] = -1;
		x[7] = -1;
		y[7] = -1;
	}

	if (mode == 6) // GL_TRIANGLE_FAN
	{
		x[0] = 155;
		y[0] = 50;
		x[1] = 50;
		y[1] = 120;
		x[2] = 120;
		y[2] = 150;
		x[3] = 190;
		y[3] = 150;
		x[4] = 260;
		y[4] = 120;
		x[5] = -1;
		y[5] = -1;
		x[6] = -1;
		y[6] = -1;
		x[7] = -1;
		y[7] = -1;
	}

	if (mode == 7) // GL_QUADS
	{
		x[0] = 50;
		y[0] = 50;
		x[1] = 50;
		y[1] = 150;
		x[2] = 120;
		y[2] = 150;
		x[3] = 120;
		y[3] = 50;
		x[4] = 190;
		y[4] = 50;
		x[5] = 190;
		y[5] = 150;
		x[6] = 260;
		y[6] = 150;
		x[7] = 260;
		y[7] = 50;
	}

	if (mode == 8) // GL_QUAD_STRIP
	{
		x[0] = 50;
		y[0] = 50;
		x[1] = 50;
		y[1] = 150;
		x[2] = 120;
		y[2] = 70;
		x[3] = 120;
		y[3] = 130;
		x[4] = 190;
		y[4] = 70;
		x[5] = 190;
		y[5] = 130;
		x[6] = 260;
		y[6] = 50;
		x[7] = 260;
		y[7] = 150;
	}
	if (mode == 9) // GL_POLYGON
	{
		x[0] = 50;
		y[0] = 100;
		x[1] = 120;
		y[1] = 50;
		x[2] = 190;
		y[2] = 50;
		x[3] = 260;
		y[3] = 100;
		x[4] = 190;
		y[4] = 150;
		x[5] = 120;
		y[5] = 150;
		x[6] = -1;
		y[6] = -1;
		x[7] = -1;
		y[7] = -1;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(255, 255, 255);
	glPointSize (3.0);
	glLineWidth(3.0);

	glBegin (a [mode ]) ;

	for (i = 0 ; i < 8; i++)
	{
		if (x [i] > 0)
		{
			glVertex2i(x[i], y[i]);
		}
	}

	glEnd ();

	for (i = 0 ; i < 8; i++)
	{
		if ((x [i] > 0) && (y[i] < 100))
		{
			glRasterPos2i(x [i] - 5, y[i] - 15);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12 , '1' + i);
		}
		if ((x [i] > 0) && (y[i] >= 100))
		{
			glRasterPos2i(x [i] - 5, y[i] + 15);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12 , '1' + i);
		}
	}

	glRasterPos2i(30, 200);
	for (i = 0 ; i < strlen(s[mode]) ; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , s[mode][i]);
	}

	glFlush () ;
}

//
// React to Key-In
//
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 0x1b) exit(0);
}


//
// React to Special Key-In
//
void SpecialKey(int k, int x, int y)
{
	if (k == GLUT_KEY_LEFT)
	{
		mode--;
		if (mode < 0) mode = 9;
	}

	if (k == GLUT_KEY_RIGHT)
	{
		mode++;
		if (mode > 9) mode = 0;
	}

	glutPostRedisplay();
}
