#include "game_math.h"
int scoredigit[6];
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