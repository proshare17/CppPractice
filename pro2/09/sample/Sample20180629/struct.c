/*************************/
/*    Sample Program     */
/*  for structured data  */
/*************************/

#include <stdio.h>

struct table{
        float x;
        float y;};

// Prototyping
float hokan(float, float, float, float, float, float, float); 

int main(void)
{
    static struct table alpha[] = { 
                             { 21.1, 2.01},{ 37.8, 2.04},
                             { 65.6, 2.09},{ 93.3, 2.12},
                             {121.1, 2.15},{148.9, 2.16},
                             {176.7, 2.16},{204.4, 2.16},
                             {232.2, 2.16},{260.0, 2.14},
                             {287.8, 2.12},{315.6, 2.10},
                             {343.3, 2.07},{371.1, 2.04},
                             {398.9, 2.02},{426.7, 1.99},
                             {454.4, 1.95},{482.2, 1.92},
                             {510.0, 1.89},{537.8, 1.86}};
    int i;
    float x1, x2, x3, xx;
    float y1, y2, y3,yy;

    float hokan(float,float,float,float,float,float,float);

    printf("Enter X-cordinate:");

    while( scanf("%f",&xx) == 1){

	for(i=2; i<19; i++){
            if( xx < alpha[i].x ) break;
        }
        x1 = alpha[i-2].x;
        x2 = alpha[i-1].x;
        x3 = alpha[i].x;
        y1 = alpha[i-2].y;
        y2 = alpha[i-1].y;
        y3 = alpha[i].y;

        yy = hokan(xx, x1, x2, x3, y1, y2, y3);

        printf("*** X-cordinate: %6.2f \n",xx);
        printf("*** Y-cordinate: %6.2f \n",yy);

        printf("Enter X-cordinate:");
    }
	return(0);
}

// Interpolation
float hokan(float xx, float x1, float x2, float x3, 
                      float y1, float y2, float y3) 
{
    float a, b, c, det;

    det = x3*x2*(x2-x3) + x2*x1*(x1-x2) + x1*x3*(x3-x1);
    a   = x3*(y2-y1) + x2*(y1-y3) + x1*(y3-y2);
    b   = x3*x3*(y2-y1) + x2*x2*(y1-y3) + x1*x1*(y3-y2);
    c   = x3*x3*(x1*y2-x2*y1)
        + x2*x2*(x3*y1-x1*y3)
        + x1*x1*(x2*y3-x3*y2);

    return (a*xx*xx-b*xx+c)/det;
}
