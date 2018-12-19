#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node{
	char name[30];
	long num;
	struct node *next;};

typedef struct node NODE;
NODE *start, *end, *gnode();

void menu(void)
{
	printf("\n\n");
	printf("\e[10C    Load Data ==> .L\n");
	printf("\e[10C Display Data ==> .P\n");
	printf("\e[10C    Save Data ==> .S\n");
	printf("\e[10C  Insert Data ==> .I\n");
	printf("\e[10C  Delete Data ==> .D\n");
	printf("\e[10C         Quit ==> .Q\n");
	printf("\e[12C");
	printf("Enter Command >>");
}

NODE *gnode()
{
	NODE *p;
	p = malloc(sizeof(NODE));
	if (p == NULL )
		printf("Not enouph memry\n");
	return p;
}

void printlist()
{
	NODE *p;
	printf("\n\nContents:\n\n");
	p = start;
	while (p != end){
		printf("%8ld %-40s %p\n", p->num, p->name, p->next);
		p = p->next;
	} 

	menu();
}

int loadlist()
{
	NODE *p;
	char filnam[50],str[100];
	long i, ii;
	FILE *fp;
	if (start != end){
		printf("List is not empty\n");
		return 1;
	}
	printf("\e[18C");
	printf("File name:");
	scanf("%s", filnam);

	fp = fopen(filnam, "r");
	if (fp == NULL){
		printf("Unknown file\n");
		return 1;
	}

	while (i=fscanf(fp, "%ld %s",&ii, str) == 2){

		p = end;
		end = gnode();
		p->next = end;
		strcpy(p->name,str);
		p->num = ii;
	} 

	fclose(fp);
	menu();
	return 0;
}

void savelist()
{
	NODE *p;
	char filnam[50];
	FILE *fp;

	printf("\e[18C");
	printf("File name: ");
	scanf("%s",filnam);
	fp = fopen(filnam,"w");
	p = start;
	while (p != end){
		fprintf(fp,"%ld %s\n", p->num, p->name);
		p = p->next;
	}
	fclose(fp);

	menu();

}

void insert()
{
	NODE *p;
	NODE *q;
	char str[100];
	long nu,	mat;
	
	p = end;
	printf("Enter Name and Number:");
	scanf("%s %ld",str,&nu);

/*	p = start;

	printf("Enter Name and Number:");
	scanf("%s %ld",str,&nu);

	while (p != end){
		mat = strcmp(p->name,str);
		if(mat==0){
			printf("Already Exist %s\n",str);
			break;
		}
		p = p->next;
	}  */

	q = gnode();
	if (p == end)
		end = q;
	else
		*q = *p;
	p->next = q;
	strcpy(p->name, str);
	p->num = nu;

	menu();

}

void delete(NODE *p)
{
	char str[100];
	int mat;
	NODE *q;

	p = start;

	printf("Enter Delete Name:");
	scanf("%s",str);

	while (p != end){
		mat = strcmp(p->name,str);
		if(mat==0){
				printf("Delete Name\n");
			free(p->name);
			q = p->next;
			if (q == end)
				end = p;
			else
				*p= *q;
			free(q);
			break;
		}
		p = p->next;
	}
 
	menu();

}

void bye(void)
{
	exit(0);
}

void main()
{
	char str[100];
	int  ch;
	long ii;
	int  indic, found;
	NODE *p;

//
// Initial Screen
//
	printf("\e[2J");
	printf("\e[1m\e[33m");

	menu();

	/* Preparing Empty list*/
	start = gnode();
	end = start;

	/* Load | Save | Delete */
	while(1){
		scanf("%s",str);
		if (str[0] == '.')
			switch (toupper(str[1])){
				case 'L':  loadlist();			break;
				case 'P':  printlist();			break;
				case 'I':  insert(p, ii, str);	break;
				case 'D':  delete(p);			break;
				case 'S':  savelist();			break;
				case 'Q':  bye();
				default :  printf("\nWrong command use L, P, S, I, D or Q\n");
			}
	}
}

