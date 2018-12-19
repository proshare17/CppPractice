#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <GL/glut.h>
#include <GL/glpng.h>



//プロトタイプ宣言
void position(void);
void Display(void);
void Reshape(int,int);
void Timer(int);
void PutSprite(int, int, int, pngInfo *);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void PrintText(int, int, char *);
void Change(int,int);
void Check(void);

int Flag = 0;
int count = 0;
int click = 0;
int timekeep = 0;
int savex1,savey1,savex2,savey2;
int ElapsedTime,ms;
int font = 0;

//PNG読み込み用
GLuint c[13], s[13], h[13], d[13], z, b;
pngInfo cinfo[13], sinfo[13], hinfo[13], dinfo[13], zinfo, binfo;

//初期配置
int  Position[4][14];


int main (int argc, char **argv)
{
    int i;
    char f[20];

    position();
//設定
    glutInit(&argc,argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(880, 396);
    glutCreateWindow("Memory");

    glutDisplayFunc(Display);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutTimerFunc(1000,Timer,0);
//アルファチャネル
    glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
  	glTexEnvf(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);

//PNG読み込み
    for (i = 1 ; i <= 13 ; i++)
  	{
      sprintf(f, "c%1d.png" , i);
  		c[i-1] = pngBind(f, PNG_NOMIPMAP, PNG_ALPHA, &cinfo[i-1],
  			GL_CLAMP, GL_NEAREST, GL_NEAREST);
      sprintf(f, "s%1d.png" , i);
    	s[i-1] = pngBind(f, PNG_NOMIPMAP, PNG_ALPHA, &sinfo[i-1],
  			GL_CLAMP, GL_NEAREST, GL_NEAREST);
      sprintf(f, "h%1d.png" , i);
  		h[i-1] = pngBind(f, PNG_NOMIPMAP, PNG_ALPHA, &hinfo[i-1],
  			GL_CLAMP, GL_NEAREST, GL_NEAREST);
      sprintf(f, "d%1d.png" , i);
  		d[i-1] = pngBind(f, PNG_NOMIPMAP, PNG_ALPHA, &dinfo[i-1],
  			GL_CLAMP, GL_NEAREST, GL_NEAREST);
  	}
    z = pngBind("z.png", PNG_NOMIPMAP, PNG_ALPHA, &zinfo,
      GL_CLAMP, GL_NEAREST, GL_NEAREST);
    b = pngBind("b.png", PNG_NOMIPMAP, PNG_ALPHA, &binfo,
      GL_CLAMP, GL_NEAREST, GL_NEAREST);

    glutMainLoop();
    return 0;

}

//トランプの表面の配置決定
void position(void){
  int i, j, judge;
  int list[52];
  srandom((unsigned)time(NULL));

  for (i = 0; i < 52; i++) {
    while (1) {
      judge = 0;
      list[i] = random() % 52;
      for (j = 0; j < i; j++){
        if(list[i] == list[j])
          judge++;
      }
      if(judge == 0)
          break;
    }
  }
 for(i=0;i<4;i++){
   for(j=0;j<13;j++){
     Position[i][j] = list[13*i+j] + 52;//0~12:♠,13~25:♥,26~38:♣,39~51:♦,52~裏
   }
 }
}

void Display(void){
  int i,j,k;

  glClear(GL_COLOR_BUFFER_BIT);

  if(Flag == 2){
    char message1[11] = "GameClear";
    char message2[20] = "Please Press \"Esc\"";
    char num[15];
    int minute = ElapsedTime/60;
    int second = ElapsedTime%60;
    sprintf(num,"%dmin%dsec",minute,second);

    glColor3ub(255, 0, 0);
    font = 1;
  	PrintText(300, 100, message1);
    glColor3ub(255, 200, 200);
  	PrintText(400, 200, num);
    font = 0;
    PrintText(300, 350, message2);

  }else{
    for (i = 0; i<4; i++){
      for (j = 0; j < 13; j++) {
        k = Position[i][j];

        if(k < 13){       //
          PutSprite(s[k],j*68,i*100,&sinfo[k]);
        }else if(k <26) {
          PutSprite(h[k-13],j*68,i*100,&hinfo[k-13]);
        }else if(k <39){
          PutSprite(c[k-26],j*68,i*100,&cinfo[k-26]);
        }else if(k <52){
          PutSprite(d[k-39],j*68,i*100,&dinfo[k-39]);
        }else if(k > 120){
          PutSprite(b,j*68,i*100,&binfo);
        }else{
          PutSprite(z,j*68,i*100,&zinfo);
        }
      }
    }
  }


  glFlush();
  glutSwapBuffers();
  usleep(500000);
  timekeep = 0;
  Check();
}


void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glScaled (1, -1, 1);
	glTranslated(0, -h, 0);
	glutReshapeWindow(880, 396);
}

void Timer(int a)
{
  ms = glutGet(GLUT_ELAPSED_TIME);
  if(Flag != 2)
    ElapsedTime = ms/1000;
	glutPostRedisplay();
	glutTimerFunc(10, Timer, a);
}

void PutSprite(int num, int x, int y, pngInfo *info)
{
	int w , h ;
//画像の縦・横の長さを取得
	w = info->Width;
	h = info->Height*1.5;

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, num);
//画像の描画
	glBegin(GL_QUADS) ;

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
//クリック操作
void Mouse(int b, int s, int x, int y){
  if((Flag != 2)&&(timekeep == 0)){
    if (b == GLUT_LEFT_BUTTON){
      if (s == GLUT_DOWN){
        if((x%68<64)&&(y%100<96)){
          if((Position[y/100][x/68] >= 52) && (Position[y/100][x/68] < 120)){
            click++;
            timekeep++;
            Change(x,y);
          }
        }
      }
    }
  }
}

//Escで終了
void Keyboard(unsigned char key, int x, int y){
  if (key == 0x1b) {
    //exit(0);
    Flag = 2;
  }
}

//文字出力
void PrintText(int x, int y, char *s)
{
	int i , l;

	glRasterPos2i(x , y);

	l = strlen(s);


	for (i = 0 ; i < l ; i++)
	{
    if(font == 1)
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    else
		  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
}

//表裏入れ替え
void Change(int x, int y){
  int i = x / 68,j = y / 100;
  if(click == 1){
    Position[j][i] -= 52;
    savex1 = i;
    savey1 = j;
  }
  if(click == 2){
    Position[j][i] -= 52;
    savex2 = i;
    savey2 = j;
    click = 0;
    Flag = 1;
  }
}
//同じ数字か判定
void Check(){
  if(Flag == 1){
    Flag = 0;
    if(Position[savey1][savex1]%13==Position[savey2][savex2]%13){
      Position[savey1][savex1] = 200;
      Position[savey2][savex2] = 200;
      count++;
      if(count == 26)
        Flag = 2;
    }else{
      Position[savey1][savex1] += 52;
      Position[savey2][savex2] += 52;
    }
    glutPostRedisplay();
  }
}
