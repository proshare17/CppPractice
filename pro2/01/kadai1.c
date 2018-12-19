#include <stdio.h>

struct table
{
	float x;
	float y;
};

int main(void){
	struct table data[20];

	data[0].x = 21.1;
	data[0].y = 2.01;
	data[1].x = 37.8;
	data[1].y = 2.04;
	data[2].x = 65.6;
	data[2].y = 2.09;
	data[3].x = 93.3;
	data[3].y = 2.12;
	data[4].x = 121.1;
	data[4].y = 2.15;
	data[5].x = 148.9;
	data[5].y = 2.16;
	data[6].x = 176.7;
	data[6].y = 2.16;
	data[7].x = 204.4;
	data[7].y = 2.16;
	data[8].x = 232.2;
	data[8].y = 2.16;
	data[9].x = 260;
	data[9].y = 2.14;
	data[10].x = 287.8;
	data[10].y = 2.12;
	data[11].x = 315.6;
	data[11].y = 2.1;
	data[12].x = 343.3;
	data[12].y = 2.07;
	data[13].x = 371.1;
	data[13].y = 2.04;
	data[14].x = 398.9;
	data[14].y = 2.02;
	data[15].x = 426.7;
	data[15].y = 1.99;
	data[16].x = 454.4;
	data[16].y = 1.95;
	data[17].x = 482.2;
	data[17].y = 1.92;
	data[18].x = 510;
	data[18].y = 1.89;
	data[19].x = 537.8;
	data[19].y = 1.86;

	float x1, x2, x3, xx, y1, y2, y3, yy, a, b, c, d;
	int i;

	while(1){
		if(scanf("%f",&xx) == 0)
			return(-1);
		for(i = 2;i<20;i++){
			if(xx < data[i].x)
				break;
		}
		x1 = data[i-2].x;
		x2 = data[i-1].x;
		x3 = data[i].x;
		y1 = data[i-2].y;
		y2 = data[i-1].y;
		y3 = data[i].y;

		a = x3 * (y2 - y1) + x2 * (y1 - y3) + x1 * (y3 - y2);
		b = x3 * x3 * (y2 - y1) + x2 *  x2 * (y1 - y3) + x1 * x1 * (y3 - y2);
		c = x3 * x3 * (x1 * y2 - x2 * y1) + x2 *  x2 * (x3 * y1 - x1 * y3) + x1 * x1 * (x2 * y3 - x3 * y2);
		d = x2 * x3 * (x2 - x3) + x1 * x2 * (x1 - x2) + x3 * x1 * (x3 - x1);

		yy = (a * xx * xx - b * xx + c) / d;

		printf("%lf\n",yy);

	}

	return 0;

}
