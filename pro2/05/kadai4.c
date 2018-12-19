
//
// Edit textDisp()
//
#include <GL/glut.h>
#include <stdio.h>
#include <string.h> // strlen()
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void Display(void);
void Reshape(int,int);
void Timer(int);
void PrintText(int, int, char *);

	time_t tt;		//present time
	struct tm *ts;	//pointe to tm structure
	int h, m, s;	//Time . Minute . Second
	int yy, mm, dd;	//Year . Month . Day
	int ww;		//Day of Week
	char yb[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	char opt_hour;	//12 hour system or 24 hour system
	char opt_month;	// if represents date english
	int i;		// for Loop counter
	char tstr [40];	// String for Time display
	char dstr [40];	// String for Date display

//char message[]="Welcome to Glut World!";
//int counter=0;
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
	//PrintText(50, 120, message);
	// Day
	sprintf(dstr, "%04d/%02d/%02d (%s)", yy, mm, dd, yb[ww]);
	//Time
	sprintf(tstr, "%02d:%02d:%02d", h, m, s);

	PrintText(50,120,dstr);
	PrintText(300,120,tstr);
//	sprintf(num,"%d",counter);
//	glColor3ub(255, 200, 200);
//	PrintText(300, 120, num);

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
	//counter++;
		time(&tt);		// present Time
		ts = localtime(&tt);	// time_t --> struct tm

		h = ts->tm_hour;	// Time
		m = ts->tm_min;		// Minute
		s = ts->tm_sec;		// Second

		yy = ts->tm_year+1900;	// Year
		mm = ts->tm_mon+1;	// Month
		dd = ts->tm_mday;	// Day
		ww = ts->tm_wday;	// Day of Week

		strcpy(dstr, "");
		strcpy(tstr, "");


	glutPostRedisplay();
	glutTimerFunc(1000, Timer, value);
}
