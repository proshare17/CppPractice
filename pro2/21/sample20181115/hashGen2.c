#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100
//#define LEN 1000
struct {
	char k[32];
	int  d;} a[LEN];

int hash(char *name)
{
	int i=0, j, nu;

	nu = strlen(name);
//
//	Making Hash Key;
//
//  adjust format
	printf("%s",name);
	if(nu<8)printf("\t\t");
	if(nu>=8)printf("\t");
	i = 101 * name[0] + 103 * name[nu-1] + 107 *nu;
	printf("sum=%d\tKey=%d \n", i, i%LEN);

//	return (101 * key[0] + 103 * key[nu-1] + 107 *nu) % LEN;
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

void main(void)
{
	FILE *fp;
	char name[50];
	int dat;

	fp = fopen("DATA","r");
	if(fp == NULL){
		printf("File DATA ???");
		exit(1);
	}
//
//  Stored Position of Array
//
	while(fscanf(fp,"%s %d",name,&dat) > 0){
		name[20] = '\0';
		if (store(name, dat) == 0){
			printf("Table full or duplicate name, (%s, %d)not stored\n",name, dat);
		}
	}
	fclose(fp);

	printf("\n\n");
	int j;
	for(j=0; j<100;j++)
		if(a[j].d != 0) printf("Array Pos.=%d %s %d \n",
	j,a[j].k,a[j].d);
}
