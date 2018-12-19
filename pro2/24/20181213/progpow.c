#include <stdio.h>

int power(int, int);

int main(void)
{
	int n,m;

	printf("pleaseinput two numbers (n, m) ?");
	scanf("%d %d",&n,&m);

	printf("%d to the %dth power is %d\n",n,m,power(n,m));
}

int power(int x, int y)
{
	int i,p;

	for(p=1,i=1;i<=y; ++i)
	p = p * x;
	return(p);
}

