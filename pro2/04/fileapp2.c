/**********************/
/*     fileapp2       */
/**********************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int c;
    char buff[256];
    FILE *fp1, *fp2, *fp3;

    if( argc != 4){
        printf("Usage fileapp2 [input file1] [input file file2] [outfile]\n");
        exit(1);
    }

    if ((fp1= fopen(argv[1],"r")) == NULL){
        fprintf(stderr," %s Fule Open Error!\n",argv[1]);
        exit(2);
    }

    if ((fp2= fopen(argv[2],"r")) == NULL){
        fprintf(stderr," %s Fule Open Error!\n",argv[2]);
        exit(3);
    }

    if ((fp3= fopen(argv[3],"w")) == NULL){
        fprintf(stderr," %s Fule Open Error!\n",argv[3]);
        exit(4);
    }

    while(( c = getc(fp1)) != EOF)
        putc(c,fp3);

    while(( c = getc(fp2)) != EOF)
        putc(c,fp3);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return(0);
}

