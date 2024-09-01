#include "game_math.h"
#include "game.h"
#include <time.h>
int scoredigit[6];
int accel;
void score_math(int score)
{
	if(score<=99) scoredigit[4]=score/10;
	else if(score<=999) 
	{
		scoredigit[3]=score/100;
		scoredigit[4]=(score-scoredigit[3]*100)/10;
	}
	else if(score<=9999)
	{
		scoredigit[2]=score/1000;
		scoredigit[3]=(score-scoredigit[2]*1000)/100;
		scoredigit[4]=(score-((scoredigit[3]*100)+(scoredigit[2]*1000)))/10;
	}
	else if(score<=99999)
	{
		scoredigit[1]=score/10000;
		scoredigit[2]=(score-scoredigit[1]*10000)/1000;
		scoredigit[3]=(score-((scoredigit[2]*1000)+(scoredigit[1]*10000)))/100;
		scoredigit[4]=(score-((scoredigit[3]*100)+(scoredigit[2]*1000)+(scoredigit[1]*10000)))/10;
	}
	else if(score<=999999)
	{
		scoredigit[0]=score/100000;
		scoredigit[1]=(score-scoredigit[0]*100000)/10000;
		scoredigit[2]=(score-((scoredigit[1]*10000)+(scoredigit[0]*100000)))/1000;
		scoredigit[3]=(score-((scoredigit[2]*1000)+(scoredigit[1]*10000)+(scoredigit[0]*100000)))/100;
		scoredigit[4]=(score-((scoredigit[3]*100)+(scoredigit[2]*1000)+(scoredigit[1]*10000)+(scoredigit[0]*100000)))/10;
	}
}
int counter = 0;
int rev = 0;
void counter_()
{
	if(counter <=200)
		{
			if(rev == 0)
			{
			counter = counter+5;
			}
		}
	if(counter == 200)
		{
		rev = 1;
		}
	if(rev == 1)
		{
		counter = counter-5;
		if(counter == 0)
			{
				rev = 0;
			}
		}
}
void wait(int numOfSec)
{
	int numOfMilliSec = 1000 * numOfSec;
	time_t startTime = clock();
	while(clock() < startTime + numOfMilliSec);
}
void resetscore()
{
	score=0;
	scoredigit[5]=0;
	scoredigit[4]=0;
	scoredigit[3]=0;
	scoredigit[2]=0;
	scoredigit[1]=0;
	scoredigit[0]=0;
}
void gainspeed()
{
	if (accel==10)
	{
		if (speed<=6) speed++;
		accel=0;
	}
	else accel++;
}