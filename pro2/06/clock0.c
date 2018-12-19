// clock0. c 
//
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
//
// Program start
//
int main(int argc, char **argv)
{
	time_t tt;		//present time
	struct tm *ts;	//pointe to tm structure
	int h, m, s;	//Time . Minute . Second
	int yy, mm, dd;	//Year . Month . Day
	int ww;		//Day of Week
	char yb[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	char opt_hour;	//12 hour system or 24 hour system
	char opt_month;	// if represents date english
	int i;		// for Loop counter
	char tstr [40];	// String for Time display
	char dstr [40];	// String for Date display


	while(1)
	{
		time(&tt);		// present Time
		ts = localtime(&tt);	// time_t --> struct tm

		h = ts->tm_hour;	// Time
		m = ts->tm_min;		// Minute
		s = ts->tm_sec;		// Second

		yy = ts->tm_year+1900;	// Year
		mm = ts->tm_mon+1;	// Month
		dd = ts->tm_mday;	// Day
		ww = ts->tm_wday;	// Day of Week

		strcpy(dstr, "");
		strcpy(tstr, "");

		// Day
		sprintf(dstr, "%04d/%02d/%02d (%s)", yy, mm, dd, yb[ww]);
		//Time
		sprintf(tstr, "%02d:%02d:%02d", h, m, s);

		printf("%s - %s\n", dstr, tstr);
		sleep (1);
	}

	return(0);
}

