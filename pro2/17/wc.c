/**************************/
/*        word count      */
/* Usage: wc < filename   */
/**************************/

#include <stdio.h>
#define ON  1
#define OFF 0

void main(void)
{
	int c, nb, nt, nl, nw, nc, inword;

	inword = OFF;
	nb = nt = nl = nw = nc = 0;

	while (( c=getchar()) !=EOF) {
		++nc;

		if ( c == '\n') ++nl;
		if ( c == ' ')  ++nb;
		if ( c == '\t') ++nt;

		if ( c == ' ' || c == '\n' || c=='\t')
			inword=OFF;

		else if ( inword == OFF ) {
			inword = ON;
			++nw;}
	}

	printf("      blank:%d\n",nb);
	printf("        tab:%d\n",nt);
	printf("      lines:%d\n",nl);
	printf("      words:%d\n",nw);
	printf(" characters:%d\n",nc);
}

