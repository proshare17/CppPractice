/***************************/
/*  Internal Bit sequence  */
/*   of floating data      */ 
/***************************/

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	float a;
	void bit(float);

	printf("Input float data :");
	while(scanf("%f",&a)==1){
		bit(a);
		printf("Input float data :");
	}
	return(0);
}

void bit(float x)
{
	union{
		float xx;
		long  ii;
	} data;

	int   i;
	long jj;


	data.xx=x;
	printf(" x=%e\n",x);
	for(i=31; i>=0 ; i--){
		jj=data.ii>>i;
		printf("%ld",jj & 0x0001);
		if(i%8 == 0) printf(" ");
	}
	putchar('\n');
}

