#include <GL/glut.h>
#include <GL/glpng.h>
#include <GL/gl.h>
// #include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>


void Display(void);
void Reshape(int, int);
void Timer(int);
void PutSprite(int, int, int, pngInfo *);



GLuint img1, img2;
pngInfo info1, info2;


int main(int argc, char **argv)
{
//
srandom(12345);
glutInit(&argc, argv);
glutInitWindowSize(180, 180);
glutCreateWindow("Read PNG File");
glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
glClearColor(0.0, 0.0, 1.0, 1.0);


glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

// PWG
img1 = pngBind("sample1.png", PNG_NOMIPMAP, PNG_ALPHA,
	&info1, GL_CLAMP, GL_NEAREST, GL_NEAREST);
img2 = pngBind("sample2.png", PNG_NOMIPMAP, PNG_ALPHA,
	&info2, GL_CLAMP, GL_NEAREST, GL_NEAREST);

printf ("img1: id=%d, W=%d, H=%d, D=%d, A=%d\n", img1,
info1.Width, info1.Height, info1.Depth, info1.Alpha);
printf (" img2: id=%d, W=%d, H=%d, D=%d, A=%d\n", img2,
info2.Width, info2.Height, info2.Depth, info2.Alpha);

//
glutDisplayFunc(Display);
glutReshapeFunc (Reshape);
glutTimerFunc(1000, Timer, 0);

//
glutMainLoop();

return(0);
}
//
void Timer(int t)
{
glutPostRedisplay();
glutTimerFunc(1000, Timer, 0);
}
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
void Display(void)
{
int x, y;
int w, h;


glClear(GL_COLOR_BUFFER_BIT);

w = glutGet(GLUT_WINDOW_WIDTH);
h = glutGet(GLUT_WINDOW_HEIGHT);

x = random() % w;
y = random() % h;
PutSprite(img1, x, y, &info1);

x = random() % w;
y = random() % h;
PutSprite(img2, x, y, &info2);

glFlush();
}

void PutSprite(int num, int x, int y, pngInfo *info)
{
int w, h; //

w = info->Width;
h = info->Height;

glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, num);
glColor4ub(255, 255, 255, 255);

glBegin(GL_QUADS);

glTexCoord2i(0, 0);
glVertex2i(x, y);

glTexCoord2i(0, 1);
glVertex2i(x, y + h);

glTexCoord2i(1, 1);
glVertex2i(x + w, y + h);

glTexCoord2i(1,0);

glVertex2i(x + w, y);

glEnd();

glDisable(GL_TEXTURE_2D);
glPopMatrix();
}

