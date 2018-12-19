#include <stdio.h>
int main(int argc,char ** argv){
	union {
		float f;
		int i;}uni;

	int i;
	scanf("%f",&uni.f);
	printf("%f(%08X)\n",uni.f,uni.i);
for (i = 31;i>=0;i--){
	printf("%d",(uni.i>>i)&1);
}
	printf("s = %X\n",(uni.i >> 31)&1);
	printf("s = %X\n",(uni.i >> 23)&0xFF);
	printf("s = %X\n",uni.i &0x7FFFFF);
	return 0;
}
