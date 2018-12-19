//
// Analog Clock
//
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


void Display(void);
void Reshape(int,int);
void Timer(int);

time_t tt;		//present time
struct tm *ts;	//pointe to tm structure
int h, m, s; 	// Hour-Minute-Second


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize (300, 300);
	glutCreateWindow("clock2");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutTimerFunc (500, Timer, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutMainLoop();

	return(0);
}


//
// Update Window Display
//
void Display(void)
{
//	time_t tt;	// Current Time
//	struct tm *ts;	// Pointer to tm structure

	int ls, lm, lh; // Length of Needle
	int xs, ys;	// Second Hand Coordinate
	int xm, ym;	// Minute Hand Coordinate
	int xh , yh;	// Second Hand Coordinate

	int xc, yc;	// Center Coordinate
	int xd, yd;	// Scale of Panel
	int xd0, yd0;	// Scale0 of Panel
	int ld;		// Radius of Panel
	int ld0;	// Radius of Panel Indicate
	double theta;	// Angle
	int i ;		// Loop Counter
	char wt[20];

	ls = 129;
	lm = 120;
	lh = 90;
	ld = ls + 10;
	ld0 = ls-10;

	xc = 150;
	yc = 150;

// Getting Current Time
//	time(&tt);
//	ts = localtime(&tt);
//	 It's 10:40:20 ,now.
//	h = 11;
//	m = 40;
//	s = 20;

 // Window Title
	sprintf(wt, "%02d:%02d:%02d" , h, m, s);
	glutSetWindowTitle(wt);

	// Bachground Paint
	glClear(GL_COLOR_BUFFER_BIT);

	// Watch face
	for (i = 0 ; i < 60 ; i++)
	{
		theta = 2.0 * M_PI * (double)(i * 6) / 360.0;
		xd0 = xc + (int)(ld0 * sin(theta));
		xd = xc + (int)(ld * sin(theta));
		yd0 = yc - (int)(ld0 * cos(theta));
		yd = yc - (int)(ld * cos(theta));
//
		glColor3ub (0 , 0, 0);
		glPointSize (5.0);

		if(i % 5){
			glBegin(GL_POINTS);
			glVertex2i(xd, yd);
			glEnd();
		}
		else{
			glBegin(GL_LINES);
			glVertex2i(xd, yd);
			glVertex2i(xd0, yd0);
			glEnd();
		}
	}

	// Needle
	// Second
	theta = 2.0 * M_PI * (double) s / 60.0;
	xs = xc + (int)(ls * sin(theta));
	ys = yc - (int)(ls * cos(theta));

	// minute
	theta = 2.0 * M_PI * (double)(60 * m + s) / 3600.0;
	xm = xc + (int)(lm * sin(theta));
	ym = yc - (int)(lm * cos(theta));

	// Hour
	theta = 2.0 * M_PI * (double)(3600 * h + 60 * m + s) / 43200.0;
	xh = xc + (int)(lh * sin(theta));
	yh = yc - (int)(lh * cos(theta));

	glColor3ub (0, 0, 0);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex2i(xc , yc);
	glVertex2i(xs , ys);
	glVertex2i(xc , yc);
	glVertex2i(xm, ym);
	glVertex2i(xc , yc);
	glVertex2i(xh , yh);
	glEnd();

	// Finish
	glFlush();
	glutSwapBuffers();
}


	// Reset Coordinate if occurs Window Resizing
//
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity();
	gluOrtho2D(0 , w, 0, h);
	glScaled(1, -1, 1);
	glTranslated(0, -h, 0);
	glutReshapeWindow(300 , 300); // Window Size Fixing
}

// Timer Interrupt
void Timer(int value)
{
	time(&tt);		// present Time
	ts = localtime(&tt);	// time_t --> struct tm

	h = ts->tm_hour;	// Time
	m = ts->tm_min;		// Minute
	s = ts->tm_sec;		// Second

	glutPostRedisplay();
	glutTimerFunc(500, Timer, value);
}
