#include <stdio.h>
#include <stdlib.h>
#define	NUM	10

struct student{
		char	name[20];
		float	height;
		float	weight;
		int	age;} data[NUM];

void input();
void display();

void main(void)
{
	input();

	display();
}

void input()
{
	int	i;
	char	buf[50];

	for(i=0; i<NUM; i++){

		printf("name? : ");
		gets( data[i].name);

		printf("Height? : ");
		data[i].height=atof(gets(buf));

		printf("Weight? : ");
		data[i].weight=atof(gets(buf));

		printf("Age? : ");
		data[i].age=atoi(gets(buf));
	}
}
void display()
{
	int	j;

	printf("\n No.	     name         Height   Weight     Age\n");

	printf("--- --------------------- -------- -------- --------\n");
	for(j=0; j<NUM; j++)
	{
		printf("%3d %-20s  %6.1f  %6.1f %8d \n",
			j+1,data[j].name,data[j].height,data[j].weight,data[j].age);
	}
	printf("--- --------------------- -------- -------- --------\n");
}

