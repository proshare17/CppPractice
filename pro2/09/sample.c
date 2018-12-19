#include <stdio.h>
#include <stdlib.h>

void disp(int card[4][4], int cover[4][4]);
int conf(int card[4][4],int x1,int x2,int y1,int y2);

int main(void){

int card[4][4]={{1,1,2,2},{3,3,4,4},{5,5,6,6},{7,7,8,8}};
int cover[4][4];

int i, j, count=0, stage=0, x1, x2, y1, y2;

//初期化
for(i=0;i<4;i++){
for(j=0;j<4;j++){
cover[i][j]=0;
}
}


while(stage<8){
for(i=0;i<40;i++){
printf("-");
}
printf("<%2d>\n１回目カードを捲れ\n(x1,y1)>",count+1);
for(;;){
scanf("%d%d", &x1, &y1);
if(cover[y1-1][x1-1]==0){
break;
}else{
printf("範囲以外又は既に捲った場所です\nもう一度捲ってください\n(x1,y1)>");
}
}
cover[y1-1][x1-1]=1;
disp(card,cover);

printf("\n２回目カードを捲れ\n(x2,y2)>");
for(;;){
scanf("%d%d", &x2, &y2);
if(cover[y2-1][x2-1]==0){
break;
}else{
printf("範囲以外又は既に捲った場所です\nもう一度捲ってください\n(x2,y2)>");
}
}
cover[y2-1][x2-1]=1;
disp(card,cover);

if(conf(card,x1,x2,y1,y2)==1){
printf(">>合っています\n");
count++;
stage++;
}else{
printf(">>間違っています\n");
cover[y1-1][x1-1]=0;
cover[y2-1][x2-1]=0;
count++;
}


}

return 0;

}

void disp(int card[4][4], int cover[4][4]){

int i, j;

for(i=0;i<4;i++){
for(j=0;j<4;j++){
if(cover[i][j]==0){
printf(" #");
}else{
printf("%3d",card[i][j]);
}
}
printf("\n");
}

}

int conf(int card[4][4],int x1,int x2,int y1,int y2){

if(card[y1-1][x1-1]==card[y2-1][x2-1]){
return 1;
}else{
return 0;
}

}

/*
for(i=0;i<4;i++){
for(j=0;j<4;j++){
}
}
*/ 
