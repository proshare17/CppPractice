/**********************/
/*   Bit Operator     */
/**********************/

#include <stdio.h>

int main(void)
{
       unsigned short a1, a2;
       unsigned short x1, x2, x3;

       a1=0525;
       a2=0707;

       printf(" a1 & a2 (AND) = %o\n",a1 & a2);
       printf(" a1 | a2 (OR)  = %o\n",a1 | a2);
       printf(" a1 ^ a2 (XOR) = %o\n",a1 ^ a2);
       printf( "  ~a1   (NOT) = %o\n",~a1);

       x1=0x660;
       x2=0xbbb;
       x3=0x122;

       printf(" x1 & x2 & x3 = %x\n", x1 & x2 & x3);
       printf(" x1 | x2 | x3 = %x\n", x1 | x2 | x3);
       printf(" x1 | x2 & x3 = %x\n", x1 |( x2 & x3));
       printf(" ~(~x1 & ~x2) = %x\n", ~(~x1 & ~x2));

	   return(0);
}

