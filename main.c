#include <pspdisplay.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <time.h>
#include <pspgu.h>
#include <pspdebug.h>
#include <string.h>
#include <stdio.h>
#include <pspgum.h>
#include "src/glib2d.h"
#include "src/callbacks.h"
#include <psputility.h>
#include "src/data.h"
#include <stdlib.h>
#include <math.h>
#include <pspmoduleinfo.h>
#define DATABUFFLEN   0x20
#define printf	pspDebugScreenPrintf
#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */


PSP_MODULE_INFO("Gruniozerca",0,1,1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#if _PSP_FW_VERSION >= 200
PSP_HEAP_SIZE_KB(20480);
#endif
static int running = 1;
char string[128];
int score = 152420;
int startpoint = 10;
int endpoint = 470;
int dir = 0;
int car_lau;
int counter = 0;
int rev = 0;
int car1 = 0,
	car2 = 0,
	car3 = 0,
	car4 = 0,
	car5 = 0;
int car1h = 0,
	car2h = 0,
	car3h = 0,
	car4h = 0,
	car5h = 0;	
int car1x = 0,
	car2x = 0,
	car3x = 0,
	car4x = 0,
	car5x = 0;	
int scor1 = 0,
	scor2 = 0,
	scor3 = 0,
	scor4 = 0,
	scor5 = 0,
	scor6 = 0;
int blue = 0,
	red = 0,
	right = 0,
	left = 0;
	void score_math()
	{
	if(score<=99) scor2=score/10;
	if(score<=999) 
	{
	scor3=score/100;
	scor2=(score-scor3*100)/10;
	}
	if(score<=9999)
	{
	scor4=score/1000;
	scor3=(score-scor4*1000)/100;
	scor2=(score-((scor3*100)+(scor4*1000)))/10;
	}
	if(score<=99999) scor5=score/10000;
	if(score<=999999) scor6=score/100000;
    }
	
	void carrot_launcher()
{
	if(car_lau <=endpoint)
		{
			if(dir == 0)
			{
			car_lau = car_lau+10;
			}
		}
	if(car_lau == endpoint)
		{
		dir = 1;
		}
	if(dir == 1)
		{
		car_lau = car_lau-10;
		if(car_lau == startpoint)
			{
				dir = 0;
			}
		}
}

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

void launch_carrot()
{
	if(car1==0) car1x = car_lau;
	if(car2==0) car2x = car_lau;
	if(car3==0) car3x = car_lau;
	if(car4==0) car4x = car_lau;
	if(car5==0) car5x = car_lau;
	car1 = 1;
	if(car4 == 1)
	{
		car5 = 1;
	}
	if(car3 == 1)
	{
		car4 = 1;
	}
	if(car2 == 1)
	{
		car3 = 1;
	}
	if(car1 == 1)
	{
		car2 = 1;
	}
	car1 = 1;
}


int main()
{
  //int mode = 0;
  SceCtrlData pad;
  callbacks_setup();
  g2dTexture* background = g2dTexLoad("img/background.png",G2D_SWIZZLE);
  g2dTexture* grunio = g2dTexLoad("img/grunio.png",G2D_SWIZZLE); 	
  g2dTexture* testmove = g2dTexLoad("img/testmove.png",G2D_SWIZZLE);
  g2dTexture* blue_carrot = g2dTexLoad("img/marchewblue.png",G2D_SWIZZLE);
  g2dTexture* red_carrot = g2dTexLoad("img/marchewred.png",G2D_SWIZZLE);
  g2dTexture* num0 = g2dTexLoad("font/0.png",G2D_SWIZZLE);
  g2dTexture* num1 = g2dTexLoad("font/1.png",G2D_SWIZZLE);
  g2dTexture* num2 = g2dTexLoad("font/2.png",G2D_SWIZZLE);
  g2dTexture* num3 = g2dTexLoad("font/3.png",G2D_SWIZZLE);
  g2dTexture* num4 = g2dTexLoad("font/4.png",G2D_SWIZZLE);
  g2dTexture* num5 = g2dTexLoad("font/5.png",G2D_SWIZZLE);
  g2dTexture* num6 = g2dTexLoad("font/6.png",G2D_SWIZZLE);
  g2dTexture* num7 = g2dTexLoad("font/7.png",G2D_SWIZZLE);
  g2dTexture* num8 = g2dTexLoad("font/8.png",G2D_SWIZZLE);
  g2dTexture* num9 = g2dTexLoad("font/9.png",G2D_SWIZZLE);			
  int x_back = G2D_SCR_W/2,
      y_back = G2D_SCR_H/2,	  
      xg = 200;
  car_lau = startpoint;
  red = 1;
  //SetupGu();
  while (1)
  {	
	counter_();
	score_math();
	if (pad.Buttons & PSP_CTRL_SQUARE) 
	{
		red = 1;
		blue = 0;
	}
    if (pad.Buttons & PSP_CTRL_CIRCLE) 
	{
		red = 0;
		blue = 1;
	}
	if (counter==0) launch_carrot();
     sceCtrlPeekBufferPositive(&pad,1);
	carrot_launcher();
    // Display routines
    g2dClear(BLACK);
	g2dBeginRects(background);
    if (background == NULL) g2dSetColor(BLACK);
    g2dSetCoordMode(G2D_CENTER);
    g2dSetAlpha(255);
    g2dSetScaleWH(480,272);
    g2dSetCoordXY(x_back,y_back);
    g2dSetRotation(0);		
    g2dAdd();
    g2dEnd();
    g2dBeginRects(testmove);
    if (testmove == NULL) g2dSetColor(GREEN);
    g2dSetCoordMode(G2D_CENTER);
    g2dSetAlpha(255);
    g2dSetScaleWH(20,20);
    g2dSetCoordXY(car_lau,0);
    g2dSetRotation(0);
    g2dAdd();
    g2dEnd();
	g2dBeginRects(testmove);
    if (testmove == NULL) g2dSetColor(GREEN);
    g2dSetCoordMode(G2D_CENTER);
    g2dSetAlpha(255);
    g2dSetScaleWH(20,20);
    g2dSetCoordXY(0,counter);
    g2dSetRotation(90);
    g2dAdd();
    g2dEnd();
	if (pad.Buttons & PSP_CTRL_LEFT)    
	{
		if (xg >=startpoint)xg-=5;
		left=1;
		right=0;
	}
	if (pad.Buttons & PSP_CTRL_RIGHT)
	{
		if (xg <=endpoint)xg+=5;
		left=0;
		right=1;
	}
	if(car1 == 1)
	{	
		if(car1h <=220) car1h = car1h+2;
		g2dBeginRects(blue_carrot);
		if(car1h >=220) 
		{
			g2dReset();
			car1h = 0;
			car1 = 0;
			if(car1x>=xg-22 && car1x<=xg+22)
			{
				score+=10;
			}
		}
		if (testmove == NULL) g2dSetColor(BLUE);
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(255);
		g2dSetScaleWH(20,32);
		g2dSetCoordXY(car1x,car1h);
		g2dSetRotation(0);
		g2dAdd();
		g2dEnd();
	}
	if(car5 == 1)
	{
		if(car2h <=220) car2h = car2h+2;
		g2dBeginRects(blue_carrot);
		if(car2h >=220) 
		{
			g2dReset();
			car2h = 0;
			car2 = 0;
		}
		if (testmove == NULL) g2dSetColor(BLUE);
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(255);
		g2dSetScaleWH(20,32);
		g2dSetCoordXY(car2x,car2h);
		g2dSetRotation(0);
		g2dAdd();
		g2dEnd();
	}
	if(car3 == 1)
	{
		if(car3h <=220) car3h = car3h+2;
		g2dBeginRects(blue_carrot);
		if(car3h >=220) 
		{
			g2dReset();
			car3h = 0;
			car3 = 0;
		}
		if (testmove == NULL) g2dSetColor(BLUE);
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(255);
		g2dSetScaleWH(20,32);
		g2dSetCoordXY(car3x,car3h);
		g2dSetRotation(0);
		g2dAdd();
		g2dEnd();
	}	
	if(car4 == 1)
	{
		if(car4h <=220) car4h = car4h+2;
		g2dBeginRects(blue_carrot);
		if(car4h >=220) 
		{
			g2dReset();
			car4h = 0;
			car4 = 0;
		}
		if (testmove == NULL) g2dSetColor(BLUE);
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(255);
		g2dSetScaleWH(20,32);
		g2dSetCoordXY(car4x,car4h);
		g2dSetRotation(0);
		g2dAdd();
		g2dEnd();
	}		
	g2dBeginRects(grunio);
    if (grunio == NULL) g2dSetColor(BLUE);
    g2dSetCoordMode(G2D_CENTER);
	g2dSetCoordXY(xg,220);
    g2dSetCropWH(40,28);
	g2dSetScaleWH(40,28);
	if(right==1)
	{
	if(blue==1)g2dSetCropXY(1,1);
	if(red==1)g2dSetCropXY(80,1);	
	}
	if(left==1)
	{
	if(blue==1)g2dSetCropXY(40,1);
	if(red==1)g2dSetCropXY(120,1);	
	}	
    g2dAdd();
    g2dEnd();  
	g2dBeginRects(num0);	
	g2dSetCoordMode(G2D_CENTER);
	g2dSetAlpha(0);
	g2dSetScaleWH(18,18);
	g2dSetCoordXY(470,12);
	g2dSetRotation(0);
	g2dAdd();
	g2dEnd();
	if(scor2==0)g2dBeginRects(num0);	
	if(scor2==1)g2dBeginRects(num1);	
	if(scor2==2)g2dBeginRects(num2);	
	if(scor2==3)g2dBeginRects(num3);	
	if(scor2==4)g2dBeginRects(num4);		
	if(scor2==5)g2dBeginRects(num5);	
	if(scor2==6)g2dBeginRects(num6);	
	if(scor2==7)g2dBeginRects(num7);	
	if(scor2==8)g2dBeginRects(num8);	
	if(scor2==9)g2dBeginRects(num9);
	g2dSetCoordMode(G2D_CENTER);
	g2dSetAlpha(0);
	g2dSetScaleWH(18,18);
	g2dSetCoordXY(450,12);
	g2dSetRotation(0);
	g2dAdd();
	g2dEnd();
	if(scor3==0)g2dBeginRects(num0);	
	if(scor3==1)g2dBeginRects(num1);	
	if(scor3==2)g2dBeginRects(num2);	
	if(scor3==3)g2dBeginRects(num3);	
	if(scor3==4)g2dBeginRects(num4);		
	if(scor3==5)g2dBeginRects(num5);	
	if(scor3==6)g2dBeginRects(num6);	
	if(scor3==7)g2dBeginRects(num7);	
	if(scor3==8)g2dBeginRects(num8);	
	if(scor3==9)g2dBeginRects(num9);		
	g2dSetCoordMode(G2D_CENTER);
	g2dSetAlpha(255);
	g2dSetScaleWH(18,18);
	g2dSetCoordXY(430,12);
	g2dSetRotation(0);
	g2dAdd();
	g2dEnd();
	if(scor4==0)g2dBeginRects(num0);	
	if(scor4==1)g2dBeginRects(num1);	
	if(scor4==2)g2dBeginRects(num2);	
	if(scor4==3)g2dBeginRects(num3);	
	if(scor4==4)g2dBeginRects(num4);		
	if(scor4==5)g2dBeginRects(num5);	
	if(scor4==6)g2dBeginRects(num6);	
	if(scor4==7)g2dBeginRects(num7);	
	if(scor4==8)g2dBeginRects(num8);	
	if(scor4==9)g2dBeginRects(num9);	
	g2dSetCoordMode(G2D_CENTER);
	g2dSetAlpha(255);
	g2dSetScaleWH(18,18);
	g2dSetCoordXY(410,12);
	g2dSetRotation(0);
	g2dAdd();
	g2dEnd();	
	if(scor5==0)g2dBeginRects(num0);	
	if(scor5==1)g2dBeginRects(num1);	
	if(scor5==2)g2dBeginRects(num2);	
	if(scor5==3)g2dBeginRects(num3);	
	if(scor5==4)g2dBeginRects(num4);		
	if(scor5==5)g2dBeginRects(num5);	
	if(scor5==6)g2dBeginRects(num6);	
	if(scor5==7)g2dBeginRects(num7);	
	if(scor5==8)g2dBeginRects(num8);	
	if(scor5==9)g2dBeginRects(num9);		
	g2dSetCoordMode(G2D_CENTER);
	g2dSetAlpha(255);
	g2dSetScaleWH(18,18);
	g2dSetCoordXY(390,12);
	g2dSetRotation(0);
	g2dAdd();
	g2dEnd();
	if(scor6==0)g2dBeginRects(num0);	
	if(scor6==1)g2dBeginRects(num1);	
	if(scor6==2)g2dBeginRects(num2);	
	if(scor6==3)g2dBeginRects(num3);	
	if(scor6==4)g2dBeginRects(num4);		
	if(scor6==5)g2dBeginRects(num5);	
	if(scor6==6)g2dBeginRects(num6);	
	if(scor6==7)g2dBeginRects(num7);	
	if(scor6==8)g2dBeginRects(num8);	
	if(scor6==9)g2dBeginRects(num9);	
	g2dSetCoordMode(G2D_CENTER);
	g2dSetAlpha(255);
	g2dSetScaleWH(18,18);
	g2dSetCoordXY(370,12);
	g2dSetRotation(0);
	g2dAdd();
	g2dEnd();	
    g2dFlip(G2D_VSYNC);	
  }

  sceKernelExitGame();
  return 0;
}
void wait(int numOfSec)
{
	int numOfMilliSec = 1000 * numOfSec;
	time_t startTime = clock();
	while(clock() < startTime + numOfMilliSec);
}

