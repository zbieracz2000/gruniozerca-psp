#include "src/includes.h"
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
int hiscore;
int randomcolor = 0;
int buttondelay = 0;
static int running = 1;
char string[128];
int screen = 1;
int score = 0;
int life = 3;
int startpoint = 10;
int endpoint = 470;
int dir = 0;
int car_lau;
int counter = 0;
int rev = 0;
int startvisible = 0;
int waitend = 0;
int car1 = 0,
	car2 = 0,
	car3 = 0,
	car4 = 0,
	car5 = 0,
	car6 = 0,
	car7 = 0;
int xgcom1,
	xgcom2,
	xgcom3,
	xgcom4,
	xgcom5,
	xgcom6,
	xgcom7;
int car1color = 5,
	car2color = 5,
	car3color = 5,
	car4color = 5,
	car5color = 5,
	car6color = 5,
	car7color = 5;
int car1h = 0,
	car2h = 0,
	car3h = 0,
	car4h = 0,
	car5h = 0,
	car6h = 0,
	car7h = 0;	
int car1x = 0,
	car2x = 0,
	car3x = 0,
	car4x = 0,
	car5x = 0,	
	car6x = 0,
	car7x = 0;
int blue = 1,
	red = 0,
	green = 0,
	white = 0,
	right = 0,
	left = 0,
	color = 2;
int startcounter = 0;
	

	
	void carrot_launcher()
{
	if(car_lau <=endpoint)
		{
			if(dir == 0)
			{
			car_lau = car_lau+5;
			}
		}
	if(car_lau == endpoint)
		{
		dir = 1;
		}
	if(dir == 1)
		{
		car_lau = car_lau-5;
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
PspUtilitySavedataListSaveNewData newData;

char *titleShow = "New Save";

char nameMultiple[][20] =	// End list with ""
{
 "0000",
 "0001",
 "0002",
 "0003",
 "0004",
 ""
};

char key[] = "ofkqk2342favca3";	// Key to encrypt or decrypt savedata

void initSavedata(SceUtilitySavedataParam * savedata, int mode)
{
	memset(savedata, 0, sizeof(SceUtilitySavedataParam));
	savedata->base.size = sizeof(SceUtilitySavedataParam);

	savedata->base.language = PSP_SYSTEMPARAM_LANGUAGE_ENGLISH;
	savedata->base.buttonSwap = PSP_UTILITY_ACCEPT_CROSS;
	savedata->base.graphicsThread = 0x11;
	savedata->base.accessThread = 0x13;
	savedata->base.fontThread = 0x12;
	savedata->base.soundThread = 0x10;

	savedata->mode = mode;
	savedata->overwrite = 1;
	savedata->focus = PSP_UTILITY_SAVEDATA_FOCUS_LATEST; // Set initial focus to the newest file (for loading)

#if _PSP_FW_VERSION >= 200
	strncpy(savedata->key, key, 16);
#endif

	strcpy(savedata->gameName, "Gruniozerca");	// First part of the save name, game identifier name
	strcpy(savedata->saveName, "0000");	// Second part of the save name, save identifier name

	// List of multiple names
	savedata->saveNameList = nameMultiple;

	strcpy(savedata->fileName, "DATA.BIN");	// name of the data file

	// Allocate buffers used to store various parts of the save data
	savedata->dataBuf = malloc(DATABUFFLEN);
	savedata->dataBufSize = DATABUFFLEN;
	savedata->dataSize = DATABUFFLEN;

	// Set some data
	if (mode == PSP_UTILITY_SAVEDATA_AUTOSAVE)
	{
	memset(savedata->dataBuf, 0, DATABUFFLEN);
	sprintf(savedata->dataBuf,"%d",hiscore);
	strcpy(savedata->sfoParam.title,"Gruniozerca Highscore");
	strcpy(savedata->sfoParam.savedataTitle,"Highscore:");
	sprintf(savedata->sfoParam.detail,"%d",hiscore);
	savedata->sfoParam.parentalLevel = 1;
	
	// No icon1
	savedata->icon1FileData.buf = NULL;
	savedata->icon1FileData.bufSize = 0;
	savedata->icon1FileData.size = 0;

	savedata->pic1FileData.buf = pic1;
	savedata->pic1FileData.bufSize = size_pic1;
	savedata->pic1FileData.size = size_pic1;

	savedata->icon0FileData.buf = icon0;
	savedata->icon0FileData.bufSize = size_icon0;
	savedata->icon0FileData.size = size_icon0;
	
	// No snd0
	savedata->snd0FileData.buf = snd0;
	savedata->snd0FileData.bufSize = size_snd0;
	savedata->snd0FileData.size = size_snd0;

	// Set title
	newData.title = titleShow;

	// Set new data
	savedata->newData = &newData;
	
	savedata->focus = PSP_UTILITY_SAVEDATA_FOCUS_FIRSTEMPTY; // If saving, set inital focus to the first empty slot
	}
}

static void ShowSaveDialog (int mode)
{
	SceUtilitySavedataParam dialog;
	
    initSavedata(&dialog, mode);
	
    sceUtilitySavedataInitStart(&dialog);

    while(running) {
			g2dFlip(G2D_VSYNC);

	switch(sceUtilitySavedataGetStatus()) {

	case PSP_UTILITY_DIALOG_VISIBLE :

	    sceUtilitySavedataUpdate(1);
	    break;

	case PSP_UTILITY_DIALOG_QUIT :

	    sceUtilitySavedataShutdownStart();
	    break;
	    
	case PSP_UTILITY_DIALOG_FINISHED :
		if(mode == PSP_UTILITY_SAVEDATA_LISTSAVE)
			sprintf(string, "Saved: score = 10");
		else
			hiscore=atoi((char*)dialog.dataBuf);
		screen=0;

	case PSP_UTILITY_DIALOG_NONE :
	    return;
	}
    }
}


void counter_start()
{
	if(startcounter <=20)
		{
			if(rev == 0)
			{
			startcounter = startcounter+1;
			}
		}
	if(startcounter == 20)
		{
		rev = 1;
		}
	if(rev == 1)
		{
		startcounter = startcounter-1;
		if(startcounter == 0)
			{
				rev = 0;
			}
		}
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
void launch_carrot()
{
	if(car1==0) car1x = car_lau;
	if(car2==0) car2x = car_lau;
	if(car3==0) car3x = car_lau;
	if(car4==0) car4x = car_lau;
	if(car5==0) car5x = car_lau;
	if(car6==0) car4x = car_lau;
	if(car7==0) car5x = car_lau;
	if (car1==0) car1 = 1;
	else if (car2==0) car2 = 1;
	else if (car3==0) car3 = 1;
	else if (car4==0) car4 = 1;
	else if (car5==0) car5 = 1;
	else if (car6==0) car6 = 1;
	else if (car7==0) car7 = 1;
}
int main()
{
  int mode = 0;
  SceCtrlData pad;
  callbacks_setup();
  g2dTexture* background = g2dTexLoad("img/background.png",G2D_SWIZZLE);
  g2dTexture* logo = g2dTexLoad("img/logo.png",G2D_SWIZZLE);
  g2dTexture* start = g2dTexLoad("img/start.png",G2D_SWIZZLE);
  g2dTexture* game_over = g2dTexLoad("img/game_over.png",G2D_SWIZZLE);
  g2dTexture* grunio = g2dTexLoad("img/grunio.png",G2D_SWIZZLE); 	
  g2dTexture* testmove = g2dTexLoad("img/testmove.png",G2D_SWIZZLE);
  g2dTexture* blue_carrot = g2dTexLoad("img/marchewblue.png",G2D_SWIZZLE);
  g2dTexture* red_carrot = g2dTexLoad("img/marchewred.png",G2D_SWIZZLE);
  g2dTexture* green_carrot = g2dTexLoad("img/marchewgreen.png",G2D_SWIZZLE);
  g2dTexture* white_carrot = g2dTexLoad("img/marchewwhite.png",G2D_SWIZZLE);
  g2dTexture* heart = g2dTexLoad("img/heart.png",G2D_SWIZZLE);
  g2dTexture* emptyheart = g2dTexLoad("img/emptyheart.png",G2D_SWIZZLE);  
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
  void drawsprite(g2dTexture* texture, int alpha, int w, int h, int x, int y, int rotation)
  {
	g2dBeginRects(texture);	
	g2dSetCoordMode(G2D_CENTER);
	g2dSetAlpha(alpha);
	g2dSetScaleWH(w,h);
	g2dSetCoordXY(x,y);
	g2dSetRotation(rotation);
	g2dAdd();
	g2dEnd();
  }			
  int x_back = G2D_SCR_W/2,
      y_back = G2D_SCR_H/2,	  
      xg = 200;
  car_lau = startpoint;
  while (1)
  {	sceCtrlPeekBufferPositive(&pad,1);
	if(screen==1)
	{
		/*if(pad.Buttons & PSP_CTRL_TRIANGLE)
		{
			screen=4;
			mode = PSP_UTILITY_SAVEDATA_AUTOSAVE;
			running = 1;
		}
		else if(pad.Buttons & PSP_CTRL_SQUARE)
		{
			running=1;
			screen=4;
			mode = PSP_UTILITY_SAVEDATA_LISTLOAD;
		}	*/
		g2dClear(BLACK);
		drawsprite(num0, 0, 18, 18, 290, 240, 0);
		score=hiscore;
		score_math(score);
		if(scoredigit[4]==0)g2dBeginRects(num0);	
		if(scoredigit[4]==1)g2dBeginRects(num1);	
		if(scoredigit[4]==2)g2dBeginRects(num2);	
		if(scoredigit[4]==3)g2dBeginRects(num3);	
		if(scoredigit[4]==4)g2dBeginRects(num4);		
		if(scoredigit[4]==5)g2dBeginRects(num5);	
		if(scoredigit[4]==6)g2dBeginRects(num6);	
		if(scoredigit[4]==7)g2dBeginRects(num7);	
		if(scoredigit[4]==8)g2dBeginRects(num8);	
		if(scoredigit[4]==9)g2dBeginRects(num9);
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(0);
		g2dSetScaleWH(18,18);
		g2dSetCoordXY(270,240);
		g2dSetRotation(0);
		g2dAdd();
		g2dEnd();
		if(scoredigit[3]==0)g2dBeginRects(num0);	
		if(scoredigit[3]==1)g2dBeginRects(num1);	
		if(scoredigit[3]==2)g2dBeginRects(num2);	
		if(scoredigit[3]==3)g2dBeginRects(num3);	
		if(scoredigit[3]==4)g2dBeginRects(num4);		
		if(scoredigit[3]==5)g2dBeginRects(num5);	
		if(scoredigit[3]==6)g2dBeginRects(num6);	
		if(scoredigit[3]==7)g2dBeginRects(num7);	
		if(scoredigit[3]==8)g2dBeginRects(num8);	
		if(scoredigit[3]==9)g2dBeginRects(num9);		
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(255);
		g2dSetScaleWH(18,18);
		g2dSetCoordXY(250,240);
		g2dSetRotation(0);
		g2dAdd();
		g2dEnd();
		if(scoredigit[2]==0)g2dBeginRects(num0);	
		if(scoredigit[2]==1)g2dBeginRects(num1);	
		if(scoredigit[2]==2)g2dBeginRects(num2);	
		if(scoredigit[2]==3)g2dBeginRects(num3);	
		if(scoredigit[2]==4)g2dBeginRects(num4);		
		if(scoredigit[2]==5)g2dBeginRects(num5);	
		if(scoredigit[2]==6)g2dBeginRects(num6);	
		if(scoredigit[2]==7)g2dBeginRects(num7);	
		if(scoredigit[2]==8)g2dBeginRects(num8);	
		if(scoredigit[2]==9)g2dBeginRects(num9);	
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(255);
		g2dSetScaleWH(18,18);
		g2dSetCoordXY(230,240);
		g2dSetRotation(0);
		g2dAdd();
		g2dEnd();	
		if(scoredigit[1]==0)g2dBeginRects(num0);	
		if(scoredigit[1]==1)g2dBeginRects(num1);	
		if(scoredigit[1]==2)g2dBeginRects(num2);	
		if(scoredigit[1]==3)g2dBeginRects(num3);	
		if(scoredigit[1]==4)g2dBeginRects(num4);		
		if(scoredigit[1]==5)g2dBeginRects(num5);	
		if(scoredigit[1]==6)g2dBeginRects(num6);	
		if(scoredigit[1]==7)g2dBeginRects(num7);	
		if(scoredigit[1]==8)g2dBeginRects(num8);	
		if(scoredigit[1]==9)g2dBeginRects(num9);		
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(255);
		g2dSetScaleWH(18,18);
		g2dSetCoordXY(210,240);
		g2dSetRotation(0);
		g2dAdd();
		g2dEnd();
		if(scoredigit[0]==0)g2dBeginRects(num0);	
		if(scoredigit[0]==1)g2dBeginRects(num1);	
		if(scoredigit[0]==2)g2dBeginRects(num2);	
		if(scoredigit[0]==3)g2dBeginRects(num3);	
		if(scoredigit[0]==4)g2dBeginRects(num4);		
		if(scoredigit[0]==5)g2dBeginRects(num5);	
		if(scoredigit[0]==6)g2dBeginRects(num6);	
		if(scoredigit[0]==7)g2dBeginRects(num7);	
		if(scoredigit[0]==8)g2dBeginRects(num8);	
		if(scoredigit[0]==9)g2dBeginRects(num9);	
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(255);
		g2dSetScaleWH(18,18);
		g2dSetCoordXY(190,240);
		g2dSetRotation(0);
		g2dAdd();
		g2dEnd();	
		drawsprite(start, 255, 172, 14, 240, 156, 0);
		drawsprite(logo, 255, 176, 40, 240, 76, 0); 
	    g2dFlip(G2D_VSYNC);	
		if(pad.Buttons & PSP_CTRL_START)
		{
			screen=2;
			resetscore();
		}
	}
	if(screen==2)
	{
		if (color == 1) 
		{
			green=0;
			blue=0;
			red=1;
			white=0;
		}
		if (color == 2) 
		{
			green=0;
			blue=1;
			red=0;
			white=0;
		}
		if (color == 3) 
		{
			green=1;
			blue=0;
			red=0;
			white=0;
		}
		if (color == 4) 
		{
			green=0;
			blue=0;
			red=0;
			white=1;
		}
		counter_();
		score_math(score);
		if (buttondelay==0){
			if (pad.Buttons & PSP_CTRL_SQUARE) 
			{
				if(color>=2)color--;
				else color=4;
				buttondelay=1;
			}
			if (pad.Buttons & PSP_CTRL_CIRCLE) 
			{
				if(color<=3)color++;
				else color=1;
				buttondelay=1;
			}
		}
		if (buttondelay>=1) buttondelay++;
		if (buttondelay==10) buttondelay=0;
		if (counter==0) launch_carrot();
		carrot_launcher();
		// Display routines
		g2dClear(BLACK);
		drawsprite(background, 255, 480, 272, x_back,y_back,0);
		if (pad.Buttons & PSP_CTRL_LEFT)    
		{
			if (xg >=startpoint)xg-=6;
			left=1;
			right=0;
		}
		if (pad.Buttons & PSP_CTRL_RIGHT)
		{
			if (xg <=endpoint)xg+=6;
			left=0;
			right=1;
		}
		if(car1 == 1)
		{	
			if(car1color==5)
			{
			randomcolor = rand() % 40;
			if (randomcolor>=0) if (randomcolor<=10) car1color=1;
			if (randomcolor>=11) if (randomcolor<=20) car1color=2;		
			if (randomcolor>=21) if (randomcolor<=30) car1color=3;
			if (randomcolor>=31) if (randomcolor<=40) car1color=4;		
			}
			if (car1color==1) g2dBeginRects(red_carrot);
			else if (car1color==2) g2dBeginRects(blue_carrot);
			else if (car1color==3) g2dBeginRects(green_carrot);
			else if (car1color==4) g2dBeginRects(white_carrot);
			
			if(car1h <=220) car1h = car1h+1;
			 if(car1h >=200) 
			 {	
				if(car1x>=xg) xgcom1=car1x-xg;
				else if(car1x<=xg) xgcom1=xg-car1x;
				if(xgcom1>=1) if(xgcom1<=30) if(car1color==color)
					{
						score=score+10;
						g2dReset();
						car1h = 0;
						car1 = 0;
						car1color=5;
					}

				xgcom1=0;
			 }
					if (car1h >=220) 
					{
					g2dReset();
					car1h = 0;
					car1 = 0;
					car1color=5;
					life--;
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
		if(car2 == 1)
		{	
			if(car2color==5)
			{
			randomcolor = rand() % 40;
			if (randomcolor>=0) if (randomcolor<=10) car2color=1;
			if (randomcolor>=11) if (randomcolor<=20) car2color=2;		
			if (randomcolor>=21) if (randomcolor<=30) car2color=3;
			if (randomcolor>=31) if (randomcolor<=40) car2color=4;		
			}
			if (car2color==1) g2dBeginRects(red_carrot);
			else if (car2color==2) g2dBeginRects(blue_carrot);
			else if (car2color==3) g2dBeginRects(green_carrot);
			else if (car2color==4) g2dBeginRects(white_carrot);
			
			if(car2h <=220) car2h = car2h+1;
			 if(car2h >=200) 
			 {	
				if(car2x>=xg) xgcom2=car2x-xg;
				else if(car2x<=xg) xgcom2=xg-car2x;
				if(xgcom2>=1) if(xgcom2<=30) if(car2color==color)
					{
						score=score+10;
						g2dReset();
						car2h = 0;
						car2 = 0;
						car2color=5;
					}

				xgcom2=0;
			 }
				if (car2h >=220) 
				{
					g2dReset();
					car2h = 0;
					car2 = 0;
					car2color=5;
					life--;
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
			if(car3color==5)
			{
			randomcolor = rand() % 40;
			if (randomcolor>=0) if (randomcolor<=10) car3color=1;
			if (randomcolor>=11) if (randomcolor<=20) car3color=2;		
			if (randomcolor>=21) if (randomcolor<=30) car3color=3;
			if (randomcolor>=31) if (randomcolor<=40) car3color=4;		
			}
			if (car3color==1) g2dBeginRects(red_carrot);
			else if (car3color==2) g2dBeginRects(blue_carrot);
			else if (car3color==3) g2dBeginRects(green_carrot);
			else if (car3color==4) g2dBeginRects(white_carrot);
			
			if(car3h <=220) car3h = car3h+1;
			 if(car3h >=200) 
			 {	
				if(car3x>=xg) xgcom3=car3x-xg;
				else if(car3x<=xg) xgcom3=xg-car3x;
				if(xgcom3>=1) if(xgcom3<=30) if(car3color==color)
					{
						score=score+10;
						g2dReset();
						car3h = 0;
						car3 = 0;
						car3color=5;
					}

				xgcom3=0;
			 }
				if (car3h >=220) 
				{
					g2dReset();
					car3h = 0;
					car3 = 0;
					car3color=5;
					life--;
				}
			if (testmove == NULL)g2dSetColor(BLUE);	
			g2dSetCoordMode(G2D_CENTER);
			g2dSetAlpha(255);
			g2dSetScaleWH(20,32);
			g2dSetCoordXY(car3x,car3h);
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
			if(blue==1)g2dSetCropXY(0,1);
			if(red==1)g2dSetCropXY(80,1);	
			if(green==1)g2dSetCropXY(160,1);
			if(white==1)g2dSetCropXY(240,1);
		}
		if(left==1)
		{
			if(blue==1)g2dSetCropXY(40,1);
			if(red==1)g2dSetCropXY(120,1);	
			if(green==1)g2dSetCropXY(200,1);
			if(white==1)g2dSetCropXY(280,1);	
		}	
		g2dAdd();
		g2dEnd();  
		drawsprite(num0, 0, 18, 18, 470, 12, 0);
		if(scoredigit[4]==0)drawsprite(num0, 0, 18, 18, 450, 12, 0);
		if(scoredigit[4]==1)drawsprite(num1, 0, 18, 18, 450, 12, 0);	
		if(scoredigit[4]==2)drawsprite(num2, 0, 18, 18, 450, 12, 0);
		if(scoredigit[4]==3)drawsprite(num3, 0, 18, 18, 450, 12, 0);
		if(scoredigit[4]==4)drawsprite(num4, 0, 18, 18, 450, 12, 0);		
		if(scoredigit[4]==5)drawsprite(num5, 0, 18, 18, 450, 12, 0);
		if(scoredigit[4]==6)drawsprite(num6, 0, 18, 18, 450, 12, 0);	
		if(scoredigit[4]==7)drawsprite(num7, 0, 18, 18, 450, 12, 0);
		if(scoredigit[4]==8)drawsprite(num8, 0, 18, 18, 450, 12, 0);	
		if(scoredigit[4]==9)drawsprite(num9, 0, 18, 18, 450, 12, 0);
		//next digit
		if(scoredigit[3]==0)drawsprite(num0, 0, 18, 18, 430, 12, 0);	
		if(scoredigit[3]==1)drawsprite(num1, 0, 18, 18, 430, 12, 0);	
		if(scoredigit[3]==2)drawsprite(num2, 0, 18, 18, 430, 12, 0);	
		if(scoredigit[3]==3)drawsprite(num3, 0, 18, 18, 430, 12, 0);	
		if(scoredigit[3]==4)drawsprite(num4, 0, 18, 18, 430, 12, 0);
		if(scoredigit[3]==5)drawsprite(num5, 0, 18, 18, 430, 12, 0);
		if(scoredigit[3]==6)drawsprite(num6, 0, 18, 18, 430, 12, 0);
		if(scoredigit[3]==7)drawsprite(num7, 0, 18, 18, 430, 12, 0);
		if(scoredigit[3]==8)drawsprite(num8, 0, 18, 18, 430, 12, 0);
		if(scoredigit[3]==9)drawsprite(num9, 0, 18, 18, 430, 12, 0);	
		//next digit
		if(scoredigit[2]==0)drawsprite(num0, 0, 18, 18, 410, 12, 0);
		if(scoredigit[2]==1)drawsprite(num1, 0, 18, 18, 410, 12, 0);
		if(scoredigit[2]==2)drawsprite(num2, 0, 18, 18, 410, 12, 0);
		if(scoredigit[2]==3)drawsprite(num3, 0, 18, 18, 410, 12, 0);
		if(scoredigit[2]==4)drawsprite(num4, 0, 18, 18, 410, 12, 0);
		if(scoredigit[2]==5)drawsprite(num5, 0, 18, 18, 410, 12, 0);	
		if(scoredigit[2]==6)drawsprite(num6, 0, 18, 18, 410, 12, 0);
		if(scoredigit[2]==7)drawsprite(num7, 0, 18, 18, 410, 12, 0);
		if(scoredigit[2]==8)drawsprite(num8, 0, 18, 18, 410, 12, 0);
		if(scoredigit[2]==9)drawsprite(num9, 0, 18, 18, 410, 12, 0);	
		//next digit
		if(scoredigit[1]==0)drawsprite(num0, 0, 18, 18, 390, 12, 0);
		if(scoredigit[1]==1)drawsprite(num1, 0, 18, 18, 390, 12, 0);
		if(scoredigit[1]==2)drawsprite(num2, 0, 18, 18, 390, 12, 0);	
		if(scoredigit[1]==3)drawsprite(num3, 0, 18, 18, 390, 12, 0);
		if(scoredigit[1]==4)drawsprite(num4, 0, 18, 18, 390, 12, 0);		
		if(scoredigit[1]==5)drawsprite(num5, 0, 18, 18, 390, 12, 0);
		if(scoredigit[1]==6)drawsprite(num6, 0, 18, 18, 390, 12, 0);	
		if(scoredigit[1]==7)drawsprite(num7, 0, 18, 18, 390, 12, 0);
		if(scoredigit[1]==8)drawsprite(num8, 0, 18, 18, 390, 12, 0);
		if(scoredigit[1]==9)drawsprite(num9, 0, 18, 18, 390, 12, 0);	
		//next digit
		if(scoredigit[0]==0)drawsprite(num0, 0, 18, 18, 370, 12, 0);
		if(scoredigit[0]==1)drawsprite(num1, 0, 18, 18, 370, 12, 0);		
		if(scoredigit[0]==2)drawsprite(num2, 0, 18, 18, 370, 12, 0);	
		if(scoredigit[0]==3)drawsprite(num3, 0, 18, 18, 370, 12, 0);	
		if(scoredigit[0]==4)drawsprite(num4, 0, 18, 18, 370, 12, 0);		
		if(scoredigit[0]==5)drawsprite(num5, 0, 18, 18, 370, 12, 0);	
		if(scoredigit[0]==6)drawsprite(num6, 0, 18, 18, 370, 12, 0);	
		if(scoredigit[0]==7)drawsprite(num7, 0, 18, 18, 370, 12, 0);	
		if(scoredigit[0]==8)drawsprite(num8, 0, 18, 18, 370, 12, 0);	
		if(scoredigit[0]==9)drawsprite(num9, 0, 18, 18, 370, 12, 0);	
		if(life>=1)drawsprite(heart, 255, 18, 16, 12, 11, 0);
		else drawsprite(emptyheart, 255, 18, 16, 12, 11, 0);
		if(life>=2)drawsprite(heart, 255, 18, 16, 32, 11, 0);
		else drawsprite(emptyheart, 255, 18, 16, 32, 11, 0);
		if(life==3)drawsprite(heart, 255, 18, 16, 52, 11, 0);
		else drawsprite(emptyheart, 255, 18, 16, 52, 11, 0);
		g2dFlip(G2D_VSYNC);	
	}
	if(screen==3)
	{
		if(pad.Buttons & PSP_CTRL_CROSS)
		{
			screen=1;
			life=3;
			if(score>=hiscore)
			{
				hiscore=score;
				screen=4;
				mode = PSP_UTILITY_SAVEDATA_AUTOSAVE;
				running = 1;
			}
			score=0;
		}
		g2dClear(BLACK);
		drawsprite(background, 255, 480, 272, x_back, y_back, 0);
		drawsprite(game_over, 255, 143, 14, 240, 136, 0);
		g2dFlip(G2D_VSYNC);	
	}
	if(screen==4)
	{
	while(running)
	{g2dClear(BLACK);
	g2dFlip(G2D_VSYNC);
		if(mode)
		{
			ShowSaveDialog(mode);
			mode = 0;
			screen = 1;
			running =0;
		}
	}
	}
	if(life==0) screen=3;
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

