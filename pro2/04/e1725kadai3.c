#include <stdio.h>
#include <GL/glut.h>

//GLdouble s = 0.5;
//  GLdouble s = 0.9;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(1.0, 0.0, 0.0);

    glBegin(GL_TRIANGLES);

    glVertex2d(-0.9, 0.9);
    glVertex2d(-0.9,-0.9);
    glVertex2d( 0  , 0.9);


    glVertex2d(  0,-0.9);
    glVertex2d(0.9, 0.9);
    glVertex2d(0.9,-0.9);

    glEnd();
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Primitive Drawing");

    glutInitDisplayMode(GLUT_RGBA);
//    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearColor(0.0, 0.0, 1.0, 1.0);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

//cc program.c -lglut -lGLU -lGL -lm
//c -I/usr/X11R6/include program.c -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi//         -lXext -lX11 -lm -lpthread

