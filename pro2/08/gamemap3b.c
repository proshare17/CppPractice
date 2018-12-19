//
//
//
#include <GL/glut.h>
#include <GL/glpng.h>
#include <stdio.h>


// Prototyping
void Display(void);
void Reshape(int, int);
void PutSprite(int, int, int, pngInfo *);
void Keyboard(unsigned char, int, int);
void SpecialKey(int, int, int);
void Timer(int);
int movecheck(int, int, int);


// Variables for PNG file
GLuint me[8], fd[4];
pngInfo meinf[8], fdinf[4];


// Parameter of Main Character
int px = 32, py = 32; // Coordinate of Image
int pt = 0; // Counter of animation
int dir = 2; // Up=0 Right=1, Down=2, Left=3


// Map data
char map[10][11]={
	"AAAAAAAAAA" ,
	"ABBBBBCBBA" ,
	"ABCBAABBBA" ,
	"ABBCBBDBBA" ,
	"ABBBAAAAAA" ,
	"ABABBBBCBA" ,
	"AAABBAABBA" ,
	"ABBBCAAABA" ,
	"ABDBBBCBBA" ,
	"AAAAAAAAAA" ,
};


int main(int argc, char **argv)
{
	int i;
	char f[30];


// Preparation
	glutInit(&argc, argv);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Moving character");
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
	glClearColor(0.0, 0.80, 0.0, 1.0);

// Setting alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);

// Read PNG file
	for (i = 0 ; i <= 7 ; i++)
	{
		sprintf(f, "arrow%1d.png" , i);
		me[i] = pngBind(f, PNG_NOMIPMAP, PNG_ALPHA, &meinf[i],
			GL_CLAMP, GL_NEAREST, GL_NEAREST);
	}

	for (i = 0 ; i <= 3 ; i++)
	{
		sprintf(f, "field%1d.png", i);
		fd [i] = pngBind(f, PNG_NOMIPMAP, PNG_ALPHA, &fdinf[i],
			GL_CLAMP, GL_NEAREST, GL_NEAREST);
	}

// Registration of Call back function
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutTimerFunc(350, Timer, 0);

//
	glutMainLoop();

	return(0);
}


//
// Rssetting coordinate if occured window size updated
//
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glScaled (1, -1, 1);
	glTranslated(0, -h, 0);
	glutReshapeWindow(320, 320);
}
//
// Update display
//
void Display(void)
{
	int i , j , k;


	glClear(GL_COLOR_BUFFER_BIT);

	for (i = 0 ; i < 10 ; i++)
	{
		for (j = 0 ; j < 10 ; j++)
		{
			k = map[i] [ j ];
			PutSprite(fd[k - 'A'], j * 32, i * 32, &fdinf[k - 'A']);
		}
	}

	PutSprite(me[dir * 2 + pt], px, py, &meinf[dir * 2 + pt]);

	glFlush();
	glutSwapBuffers();
}


//
// Timer interrupt for moving legs
//
void Timer(int a)
{
	pt = 1 - pt; // Moving legs
	glutPostRedisplay();
	glutTimerFunc(350, Timer, 0);
}


//
// Return val=1 if it can move direction from (x,y)
//
int movecheck(int x, int y, int d)
{
	int fg = 0; // Flag
	int cx1 , cy1; // Check-1  map[][]
	int cx2 , cy2 ; // Check-2  map[][]


	if ((d == 0) && (y > 0))
	{

		fg = 1;
		cx1 = x / 32;
		cy1 = (y - 1) / 32;
		cx2 = cx1;
		cy2 = cy1;
		if(x % 32 != 0) cx2++;
	}

	if ((d == 2) && (y < 288))
	{
		fg = 1;
		cx1 = x / 32;
		cx2 = cx1;
		cy1 = y / 32+1;
		cy2 = cy1;
		if(x % 32 != 0) cx2++;
	}
	if ((d == 3) && (x > 0))
	{
		fg = 1;
		cx1 = (x - 1) / 32;
		cy1 = y / 32;
		cx2 = cx1;
		cy2 = cy1;
		if (y % 32 != 0) cy2 ++;
	}
	if ((d == 1) && (x < 288))
	{
		fg = 1;
		cx1 = x / 32 + 1;
		cy1 = y / 32;
		cx2 = cx1;
		cy2 = cy1;
		if (y % 32 != 0) cy2++;
	}
	if (fg == 1)
	{
		if ((map[cy1][cx1] == 'A') || (map[cy2][cx2] == 'A')) fg = 0;
	}

	return(fg);
}


//
// Processing special key
//
void SpecialKey(int key, int x, int y)
{
	int dx = 0, dy = 0; // Increment of coordinate


	switch(key)
	{
		case GLUT_KEY_UP:
			dir = 0;
			if(movecheck(px, py, dir) == 1) dy = -1;
			break;
		case GLUT_KEY_DOWN:
			dir = 2;
			if(movecheck(px, py, dir) == 1) dy = 1;
			break;
		case GLUT_KEY_LEFT:
			dir = 3;
			if(movecheck(px, py, dir) == 1) dx = -1;
			break;
		case GLUT_KEY_RIGHT:
			dir = 1;
			if(movecheck(px, py, dir) == 1) dx = 1;
			break;
		default:
			dx = 0;
			dy = 0;
	}

	px += dx * 8;
	py += dy * 8;

	if ((px % 32 == 0) && (py % 32 == 0) && (map [py / 32] [px / 32] == 'D'))
	{
		map[py / 32] [px / 32] = 'C';
		printf("Got treasures\n");
	}
	glutPostRedisplay();
}


//
// Processing key input
//
void Keyboard(unsigned char key, int x, int y)
{
	FILE *fp;
//	char c;

	if(key == 0x1b)
	{
		printf("Finished by ESC key \n");
		exit(0);
	}

	if(key == 's')
	{
		fp = fopen("gamedata.txt", "w");
		if (fp == NULL)
		{
			printf("Cnanot open gamedata.txt\n");
		}
		else
		{
			fprintf(fp, "%d %d \n" , px , py) ; // Coordinate of main character
			fprintf(fp, "%d\n" , dir); // Direction of main character
			fprintf(fp, "%c\n", map[3][6]); // Upper right of treasure
			fprintf(fp, "%c\n", map [8] [2]); //Downer left of treasure
			fclose(fp);
			printf ("Saved\n");
		}
	}

	if (key == '1')
	{
		fp = fopen("gamedata.txt", "r");
		if (fp == NULL)
		{
			printf("Cannot open gamedata.txt\n");
		}
		else
		{
			fscanf(fp, "%d %d\n", &px , &py); //Coordinate of main character
			fscanf(fp, "%d\n", &dir); //Direction of main character
			fscanf(fp, "%c\n", &map[3] [6]); // Upper right of treasure
			fscanf(fp, "%c_n", &map [8] [2] ) ; // Upper right of treasure
			fclose(fp);
			printf("Recovered\n");
			glutPostRedisplay();
		}
	}
}

//
//  Display of coordinate of PNG image of num
//
void PutSprite(int num, int x, int y, pngInfo *info)
{
	int w , h ; // Width and hight of texture


	w = info->Width; // Getting width and hight of texture
	h = info->Height;

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, num);

	glBegin(GL_QUADS) ; // Rectangle of widdth and hight

	glTexCoord2i(0, 0);
	glVertex2i(x, y);

	glTexCoord2i(0, 1);
	glVertex2i(x, y + h);

	glTexCoord2i(1, 1);
	glVertex2i(x + w, y + h);

	glTexCoord2i(1, 0);
	glVertex2i(x + w, y);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

