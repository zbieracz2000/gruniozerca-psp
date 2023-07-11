// Gruniożerca for Sony Playstation Portable
// by zbieracz2000
// github.com/zbieracz2000 

#include "src/includes.h"
#include "src/callbacks.h"
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
int randomcolor = 0;
int buttondelay = 0;
const int startpoint = 10;
const int endpoint = 470;
int dir = 0;
int car_lau;
int startvisible = 0;
int waitend = 0;
struct carrot {
	int is; //stan
	int color; //kolor
	int h;
	int x;
	int col; //kolizja
};
  struct carrot c1;
  struct carrot c2;
  struct carrot c3;
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
void launch_carrot();
int main()
{
	c1.color = 5;
	c2.color = 5;
	c3.color = 5;
	SceCtrlData pad;
	callbacks_setup();
	g2dTexture* background = g2dTexLoad("img/background.png",G2D_SWIZZLE);
	g2dTexture* logo = g2dTexLoad("img/logo.png",G2D_SWIZZLE);
	g2dTexture* start = g2dTexLoad("img/start.png",G2D_SWIZZLE);
	g2dTexture* game_over = g2dTexLoad("img/game_over.png",G2D_SWIZZLE);
	g2dTexture* grunio = g2dTexLoad("img/grunio.png",G2D_SWIZZLE); 	
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
		g2dSetTexLinear(false);
		g2dSetCoordMode(G2D_CENTER);
		g2dSetAlpha(alpha);
		g2dSetScaleWH(w,h);
		g2dSetCoordXY(x,y);
		g2dSetRotation(rotation);
		g2dAdd();
		g2dEnd();
  	}			
	void drawcounter(int points, int x, int y)
	{
		score_math(points);
		drawsprite(num0, 0, 18, 18, x+100, y, 0);
		if(scoredigit[4]==0)drawsprite(num0, 255, 18, 18, x+80, y, 0); 	
		if(scoredigit[4]==1)drawsprite(num1, 255, 18, 18, x+80, y, 0); 	
		if(scoredigit[4]==2)drawsprite(num2, 255, 18, 18, x+80, y, 0); 	
		if(scoredigit[4]==3)drawsprite(num3, 255, 18, 18, x+80, y, 0); 	
		if(scoredigit[4]==4)drawsprite(num4, 255, 18, 18, x+80, y, 0); 		
		if(scoredigit[4]==5)drawsprite(num5, 255, 18, 18, x+80, y, 0); 	
		if(scoredigit[4]==6)drawsprite(num6, 255, 18, 18, x+80, y, 0); 	
		if(scoredigit[4]==7)drawsprite(num7, 255, 18, 18, x+80, y, 0); 	
		if(scoredigit[4]==8)drawsprite(num8, 255, 18, 18, x+80, y, 0); 	
		if(scoredigit[4]==9)drawsprite(num9, 255, 18, 18, x+80, y, 0); 
		//
		if(scoredigit[3]==0)drawsprite(num0, 255, 18, 18, x+60, y, 0); 	
		if(scoredigit[3]==1)drawsprite(num1, 255, 18, 18, x+60, y, 0); 	
		if(scoredigit[3]==2)drawsprite(num2, 255, 18, 18, x+60, y, 0); 	
		if(scoredigit[3]==3)drawsprite(num3, 255, 18, 18, x+60, y, 0); 	
		if(scoredigit[3]==4)drawsprite(num4, 255, 18, 18, x+60, y, 0); 		
		if(scoredigit[3]==5)drawsprite(num5, 255, 18, 18, x+60, y, 0); 	
		if(scoredigit[3]==6)drawsprite(num6, 255, 18, 18, x+60, y, 0); 	
		if(scoredigit[3]==7)drawsprite(num7, 255, 18, 18, x+60, y, 0); 	
		if(scoredigit[3]==8)drawsprite(num8, 255, 18, 18, x+60, y, 0); 	
		if(scoredigit[3]==9)drawsprite(num9, 255, 18, 18, x+60, y, 0); 		
		//
		if(scoredigit[2]==0)drawsprite(num0, 255, 18, 18, x+40, y, 0); 	
		if(scoredigit[2]==1)drawsprite(num1, 255, 18, 18, x+40, y, 0); 	
		if(scoredigit[2]==2)drawsprite(num2, 255, 18, 18, x+40, y, 0); 	
		if(scoredigit[2]==3)drawsprite(num3, 255, 18, 18, x+40, y, 0); 	
		if(scoredigit[2]==4)drawsprite(num4, 255, 18, 18, x+40, y, 0); 		
		if(scoredigit[2]==5)drawsprite(num5, 255, 18, 18, x+40, y, 0); 	
		if(scoredigit[2]==6)drawsprite(num6, 255, 18, 18, x+40, y, 0); 	
		if(scoredigit[2]==7)drawsprite(num7, 255, 18, 18, x+40, y, 0); 	
		if(scoredigit[2]==8)drawsprite(num8, 255, 18, 18, x+40, y, 0); 	
		if(scoredigit[2]==9)drawsprite(num9, 255, 18, 18, x+40, y, 0); 	
		//
		if(scoredigit[1]==0)drawsprite(num0, 255, 18, 18, x+20, y, 0);	
		if(scoredigit[1]==1)drawsprite(num1, 255, 18, 18, x+20, y, 0); 	
		if(scoredigit[1]==2)drawsprite(num2, 255, 18, 18, x+20, y, 0); 	
		if(scoredigit[1]==3)drawsprite(num3, 255, 18, 18, x+20, y, 0); 	
		if(scoredigit[1]==4)drawsprite(num4, 255, 18, 18, x+20, y, 0); 		
		if(scoredigit[1]==5)drawsprite(num5, 255, 18, 18, x+20, y, 0); 	
		if(scoredigit[1]==6)drawsprite(num6, 255, 18, 18, x+20, y, 0); 	
		if(scoredigit[1]==7)drawsprite(num7, 255, 18, 18, x+20, y, 0); 	
		if(scoredigit[1]==8)drawsprite(num8, 255, 18, 18, x+20, y, 0); 	
		if(scoredigit[1]==9)drawsprite(num9, 255, 18, 18, x+20, y, 0); 		
		//
		if(scoredigit[0]==0)drawsprite(num0, 255, 18, 18, x, y, 0); 
		if(scoredigit[0]==1)drawsprite(num1, 255, 18, 18, x, y, 0); 	
		if(scoredigit[0]==2)drawsprite(num2, 255, 18, 18, x, y, 0); 	
		if(scoredigit[0]==3)drawsprite(num3, 255, 18, 18, x, y, 0); 	
		if(scoredigit[0]==4)drawsprite(num4, 255, 18, 18, x, y, 0); 		
		if(scoredigit[0]==5)drawsprite(num5, 255, 18, 18, x, y, 0); 	
		if(scoredigit[0]==6)drawsprite(num6, 255, 18, 18, x, y, 0); 	
		if(scoredigit[0]==7)drawsprite(num7, 255, 18, 18, x, y, 0); 	
		if(scoredigit[0]==8)drawsprite(num8, 255, 18, 18, x, y, 0); 	
		if(scoredigit[0]==9)drawsprite(num9, 255, 18, 18, x, y, 0);

	}
	int x_back = G2D_SCR_W/2,
	y_back = G2D_SCR_H/2,	  
    xg = 200;
	car_lau = startpoint;  
	while (1)
	{
		sceCtrlPeekBufferPositive(&pad,1);
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
		drawcounter(hiscore, 190, 240);
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
		if(c1.is == 1)
		{	
			if(c1.color==5)
			{
				randomcolor = rand() % 40;
				if (randomcolor>=0) if (randomcolor<=10) c1.color=1;
				if (randomcolor>=11) if (randomcolor<=20) c1.color=2;		
				if (randomcolor>=21) if (randomcolor<=30) c1.color=3;
				if (randomcolor>=31) if (randomcolor<=40) c1.color=4;		
			}
			if (c1.color==1) g2dBeginRects(red_carrot);
			else if (c1.color==2) g2dBeginRects(blue_carrot);
			else if (c1.color==3) g2dBeginRects(green_carrot);
			else if (c1.color==4) g2dBeginRects(white_carrot);
			
			if(c1.h <=220) c1.h = c1.h+1;
			if(c1.h >=200) 
			{	
				if(c1.x>=xg) c1.col=c1.x-xg;
				else if(c1.x<=xg) c1.col=xg-c1.x;
				if(c1.col>=1) if(c1.col<=30) if(c1.color==color)
					{
						score=score+10;
						g2dReset();
						c1.h = 0;
						c1.is = 0;
						c1.color=5;
					}

				c1.col=0;
			}
					if (c1.h >=220) 
					{
					g2dReset();
					c1.h = 0;
					c1.is = 0;
					c1.color=5;
					life--;
					}
			g2dSetCoordMode(G2D_CENTER);
			g2dSetAlpha(255);
			g2dSetScaleWH(20,32);
			g2dSetCoordXY(c1.x,c1.h);
			g2dSetRotation(0);
			g2dAdd();
			g2dEnd();
		}		
		if(c2.is == 1)
		{	
			if(c2.color==5)
			{
			randomcolor = rand() % 40;
			if (randomcolor>=0) if (randomcolor<=10) c2.color=1;
			if (randomcolor>=11) if (randomcolor<=20) c2.color=2;		
			if (randomcolor>=21) if (randomcolor<=30) c2.color=3;
			if (randomcolor>=31) if (randomcolor<=40) c2.color=4;		
			}
			if (c2.color==1) g2dBeginRects(red_carrot);
			else if (c2.color==2) g2dBeginRects(blue_carrot);
			else if (c2.color==3) g2dBeginRects(green_carrot);
			else if (c2.color==4) g2dBeginRects(white_carrot);
			
			if(c2.h <=220) c2.h = c2.h+1;
			 if(c2.h >=200) 
			 {	
				if(c2.x>=xg) c2.col=c2.x-xg;
				else if(c2.x<=xg) c2.col=xg-c2.x;
				if(c2.col>=1) if(c2.col<=30) if(c2.color==color)
					{
						score=score+10;
						g2dReset();
						c2.h = 0;
						c2.is = 0;
						c2.color=5;
					}

				c2.col=0;
			 }
				if (c2.h >=220) 
				{
					g2dReset();
					c2.h = 0;
					c2.is = 0;
					c2.color=5;
					life--;
				}
			g2dSetCoordMode(G2D_CENTER);
			g2dSetAlpha(255);
			g2dSetScaleWH(20,32);
			g2dSetCoordXY(c2.x,c2.h);
			g2dSetRotation(0);
			g2dAdd();
			g2dEnd();
		}		
		if(c3.is == 1)
		{	
			if(c3.color==5)
			{
			randomcolor = rand() % 40;
			if (randomcolor>=0) if (randomcolor<=10) c3.color=1;
			if (randomcolor>=11) if (randomcolor<=20) c3.color=2;		
			if (randomcolor>=21) if (randomcolor<=30) c3.color=3;
			if (randomcolor>=31) if (randomcolor<=40) c3.color=4;		
			}
			if (c3.color==1) g2dBeginRects(red_carrot);
			else if (c3.color==2) g2dBeginRects(blue_carrot);
			else if (c3.color==3) g2dBeginRects(green_carrot);
			else if (c3.color==4) g2dBeginRects(white_carrot);
			
			if(c3.h <=220) c3.h = c3.h+1;
			 if(c3.h >=200) 
			 {	
				if(c3.x>=xg) c3.col=c3.x-xg;
				else if(c3.x<=xg) c3.col=xg-c3.x;
				if(c3.col>=1) if(c3.col<=30) if(c3.color==color)
					{
						score=score+10;
						g2dReset();
						c3.h = 0;
						c3.is = 0;
						c3.color=5;
					}

				c3.col=0;
			 }
				if (c3.h >=220) 
				{
					g2dReset();
					c3.h = 0;
					c3.is = 0;
					c3.color=5;
					life--;
				}
			g2dSetCoordMode(G2D_CENTER);
			g2dSetAlpha(255);
			g2dSetScaleWH(20,32);
			g2dSetCoordXY(c3.x,c3.h);
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
		drawcounter(score, 370, 12);
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
	{
	g2dClear(BLACK);
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

void launch_carrot()
{
	if(c1.is==0) c1.x = car_lau;
	if(c2.is==0) c2.x = car_lau;
	if(c3.is==0) c3.x = car_lau;
	if (c1.is==0) c1.is = 1;
	else if (c2.is==0) c2.is = 1;
	else if (c3.is==0) c3.is = 1;
}