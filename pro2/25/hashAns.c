/**************************************
*******  Hash Table using array *******
**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#define LEN 1000
#define LEN 100

// Definision of Structured Data
struct {
	char k[32];
	int  d;} a[LEN];

// Menu Function
void menu(void)
{
	printf("\n\n");
	printf("\e[10C    Load Data ==> .L\n");
	printf("\e[10C    Find Data ==> .F\n");
	printf("\e[10C         Quit ==> .Q\n");
	printf("\e[12C");
	printf("Enter Command >>");
}

// Hashing Function
int hash(char *name)
{
	int i=0, j, nu;

	nu = strlen(name);
//
//	Create Hash Key;
//
//  adjust format 
//	printf("%s",name);
	if(nu<8)printf("\t\t");
	if(nu>=8)printf("\t");
	i = 101 * name[0] + 103 * name[nu-1] + 107 *nu;
//	printf("sum=%d\tKey=%d \n", i, i%LEN);

	return i % LEN;
}

/* Storing Data  */

int store(char *name, int dat)
{
	int i, count=0;
	i = hash(name);
	while (strlen(a[i].k)){
		if(strcmp(a[i].k, name) == 0 || ++count == LEN){
			printf("Table full or duplicate Key, (%s, %d)not stored\n",name, dat);
			return 0;}

		if(++i ==LEN){
//			printf("Table full or duplicate Key, (%s, %d)not stored\n",name, dat);
			i=0;}
	}
	strcpy(a[i].k, name);
	a[i].d = dat;
	return 1;
}

/* Finding Data  */
int find()
{
	char name[100];
	int i, count=0;

//	Enter strings for find
//
	printf("   Enter strings for find: ");
	scanf("%s",name);

	i = hash(name);
	while (strcmp(a[i].k,name)){
		if(strlen(a[i].k) == 0 || ++count == LEN){
			printf("Not found %s\n",name);
			menu();
			return 0;}

		if(++i ==LEN){
			i=0;}
	}
	printf("Found data ==>  %s  %d  \n",a[i].k, a[i].d);
	menu();
	return 1;
}

// Load File
int load()
{
	char filnam[50],name[100];
	long dat;
	long i, ii;
	FILE *fp;

	printf("\e[18C");
	printf("File name:");
	scanf("%s", filnam);

// Open File
	fp = fopen(filnam, "r");
	if (fp == NULL){
		printf("Unknown file\n");
		return 1;
	}

// Read Data from File
	while(fscanf(fp,"%s %ld",name,&dat) > 0){
		if (store(name, dat) == 0){
			printf("Table full or duplicate name, (%s, %ld)not stored \n",name,dat);
		}
	} 

	fclose(fp);
	menu();
	return 0;
}

// Finish Program
void bye(void)
{
	exit(0);
}

// Main Function
void main(void)
{
	char str[100];

	printf("\e[2J");
	printf("\e[1m\e[33m");

	menu();

	while(1){
		scanf("%s",str);
		if (str[0] == '.')
			switch (toupper(str[1])){
				case 'L':  load();				break;
				case 'F':  find();				break;
				case 'Q':  bye();
				default :  printf("\nWrong command use L, F, or Q\n");
			}
	}

}

