#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


void display(void) {
    int i;
    int tmp = 10000000;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(1.0, 0.0, 0.0);

    glBegin(GL_POINTS);

    double error, approximation, true_value;
    double C1=0.868591718, C3=0.289335524, C5=0.177522071, C7=0.094376476, C9=0.191337714;

    for (i = 0;i <= tmp; i++){

	  double X = 1/sqrt(10) + i*(sqrt(10)-1/sqrt(10))/tmp;
	  double x = 1.8*(X-1/sqrt(10))/(sqrt(10)-1/sqrt(10))-0.8;

	  approximation = C1*(X-1)/(X+1) + C3*pow((X-1)/(X+1),3.0) + C5*pow((X-1)/(X+1),5.0) + C7*pow((X-1)/(X+1),7.0) + C9*pow((X-1)/(X+1),9.0);

      true_value = log10(X);

	  error = approximation - true_value;

      glVertex2d(x,error*5000000);
    }


    glEnd();
    glFlush();
}

int main(int argc, char **argv){


    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1200, 600);
    glutCreateWindow("e1725kadai8");

    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
