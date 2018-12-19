#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define Len 1000

struct {
	char k[32];
	int d;
} a[Len];

//プロトタイプ宣言
int hash(char *);
int store(char *, int);
void menu(void);
void load(void);
void find(void);


void main(void) {
	char str[3];

	//Initial Screen
	printf("\e[2J");
	printf("\e[1m\e[33m");

	menu();

	while(1){
		scanf("%s",str);
		if (str[0] == '.'){
			switch (toupper(str[1])){
				case 'L': load();   break;
				case 'F': find();   break;
				case 'Q': exit(0);
				default:
					printf("\nコマンドが間違っています.\nL, F, Qを入力してください.");
                    printf("\e[12C");
                    printf("Enter Command >>");
			}
		}else

			printf("\nコマンドが間違っています.\nL, F, Qを入力してください.");
            printf("\e[12C");
            printf("Enter Command >>");
	}
}


/* ハッシュ計算 */
int hash(char *name) {
	int i = 0, len;

	len = strlen(name);

	//Making Hash Key;
	if (len < 8)
		printf("\t\t");
	if (len >= 8)
		printf("\t");

	i = 101 * name[0] + 103 * name[len - 1] + 107 * len;
 
    //確認用
	//printf("sum=%d\tKey=%d\n", i, i % Len);

	return i % Len;
}


/* データ格納 */
int store(char *name, int dat) {
	int i, count = 0;
	i = hash(name);
	while (strlen(a[i].k)) {
		if (strcmp(a[i].k, name) == 0 || ++count == Len) {
			printf("テーブルがいっぱいか,名前が重なっています.(%s,%d)は格納できません.", name, dat);
			return 0;
		}

		if (++i == Len)
			i = 0;
	}
	strcpy(a[i].k, name);
	a[i].d = dat;
	return 1;
}

/* メニュー表示 */
void menu(void){
	printf("\n\n");
	printf("\e[10C    Load Data ==> .L\n");
	printf("\e[10C    Find Data ==> .F\n");
	printf("\e[10C         Quit ==> .Q\n");
	printf("\e[12C");
	printf("Enter Command >>");
}

/* データロード */
void load(void){
	FILE *fp;
	char name[50], filenam[100];
	int dat;
    int j;
    
    printf("開くファイルの名前を入力してください.");
    scanf("%s",filenam);
	fp = fopen(filenam, "r");
	if (fp == NULL) {
		printf("ファイルデータが不明です.");
		exit(1);
	}
	while (fscanf(fp, "%s %d", name, &dat) > 0) {
		if (store(name, dat) == 0) {
			printf("テーブルがいっぱいかハッシュキーが重なっています.(%s,%d)は格納できません.", name, dat);
        }
	}
	fclose(fp);

	printf("\n\n");

	for (j = 0; j < Len; j++) {
		if(a[j].d != 0)
			printf("Array Pos.=%d %s %d\n",j,a[j].k,a[j].d);
	}
    menu();
}

/* 探索して出力 */
void find(void){
    char str[100];
    int i;

    printf("検索する文字列を入力：");
    if(scanf("%s",str)==EOF){
        printf("エラーが発生しました.\n");
    }else{
        i = hash(str);
        if(a[i].d != 0)
            printf("Array Pos.=%d %s %d\n",i,a[i].k,a[i].d);
    }
    menu();
}
