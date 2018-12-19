//
// Plotting Error Graph
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>

#define NUM 300

void Reshape(int, int);
void Display(void);
void PrintText(int, int, char *);


GLdouble s = 0.9;

double err[NUM];

struct data {
	double x;
	double y;} appl[NUM], embe[NUM];
struct cord {
	int x;
	int y;};

struct data cal, app;

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity();
	gluOrtho2D(0 , w, 0, h);
	glScaled(1, -1, 1);
	glTranslated(0, -h, 0);
	glutReshapeWindow(700 , 500); // Window Size Fixing
}

void Display(void) {

	// Definition of Coordinate of Axes
	struct cord axis[4] = {	{50, 50},
				{50, 450},
				{50, 250}, 
				{700, 250}};
	 struct cord mini[4] = {{250, 250},
				{450, 250}, 
				{650, 250}, 
				{690, 250}}; 
	int i; 
	int x, y;

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(255,255,255);
	glBegin(GL_LINES);
	glLineWidth(2.0);
	glVertex2d(axis[0].x,axis[0].y);
	glVertex2d(axis[1].x,axis[1].y);

	glVertex2d(axis[2].x,axis[2].y);
	glVertex2d(axis[3].x,axis[3].y);

	for(i=0; i<4; i++){
		glVertex2d(mini[0].x,mini[0].y);
		glVertex2d(mini[0].x,mini[0].y-10);
		glVertex2d(mini[1].x,mini[1].y);
		glVertex2d(mini[1].x,mini[1].y-10);
		glVertex2d(mini[2].x,mini[2].y);
		glVertex2d(mini[2].x,mini[2].y-10);
		glVertex2d(mini[3].x,mini[3].y);
		glVertex2d(mini[3].x,mini[3].y-5);
	}

	for(i=0; i<9; i++){
		glVertex2d(axis[0].x,axis[0].y+i*50);
		glVertex2d(axis[0].x+10,axis[0].y+i*50);
	}

	glEnd();

//
//	Draw line
//	
    	glBegin(GL_LINE_STRIP);
	
	for(i=0; i<NUM; i++){
		x = (int)(embe[i].x*200+50);
		y = (int)(250-err[i]*1.0e6*100);
		glVertex2d(x, y);
	}

	glEnd();

//
//	Display Scales
//
	glColor3ub(250, 0, 0);
	PrintText(mini[0].x-200,mini[0].y+30, "0.0");
	PrintText(mini[0].x-10,mini[0].y+30, "1.0");
	PrintText(mini[1].x-10,mini[1].y+30, "2.0");
	PrintText(mini[2].x-10,mini[2].y+30, "3.0");

	PrintText(10,50, " 2");
	PrintText(10,150, " 1");
	PrintText(10,250, " 0");
	PrintText(10,350, "-1");
	PrintText(10,450, "-2");

	glFlush();
}

void PrintText(int x, int y, char *s)
{
         int i , l;
 
         glRasterPos2i(x , y);

         l = strlen(s);
 
 
         for (i = 0 ; i < l ; i++)
         {
                 glutBitmapCharacter(GLUT_BITMAP_9_BY_15 , s[i]);
         }
}

int main(int argc, char **argv){

	int i;
	double max,	min;
	double dx=0.01;
	double coef;
	double	c1=0.868591718,
		c3=0.289335524,
		c5=0.177522071,
		c7=0.094376476,
		c9=0.191337714;
 
	printf("    x    Calculated Apploximated Erroe \n");

	for(i=0; i<NUM; i++){
		embe[i].x=0.3+dx*i;
		embe[i].y=log10(embe[i].x);

		coef=(embe[i].x-1)/(embe[i].x+1);
		appl[i].x=0.3+dx*i;
		appl[i].y=c1*coef+c3*pow(coef,3)
				+c5*pow(coef,5)
				+c7*pow(coef,7)
				+c9*pow(coef,9);

		err[i] = embe[i].y - appl[i].y;
	}
//
// Seek Max and Min data
//
	max = err[0];
	min = err[0];
	for(i=1; i<NUM; i++){
		if(max < err[i]) max = err[i];
		if(min > err[i]) min = err[i];
	}

	printf("max= %13.6e    min = %13.6e \n",max, min);
		
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 500);
	glutCreateWindow("Error Graph");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

