#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

	#include "CRF/Layer.h"
	#include "CRF/Core.h"
	#include "CRF/Platform.h"
	#include "CRF/Modules/Base.h"
	#include "CRF/Modules/Binaries.h"
	#include "CRF/Modules/Geometry.h"
	#include "CRF/Modules/Random.h"
	#include "CRF/Modules/Transform.h"
	#include "CRF/Modules/ExDrawing/Mask.h"
	#include "CRF/Modules/ExDrawing/Solar.h"
	#include "CRF/Modules/ExDrawing/Zoom.h"
	#include "CRF/Modules/Sprites/LSprite.h"
	#include "CRF/Modules/Text/Text.h"

#ifdef WIN32
	#include <windows.h>
	#include <GL\gl.h>
	#include <GL\glu.h>
	#include "SDL2\SDL.h"
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include "SDL2/SDL.h"
#else //UNIX
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <SDL2/SDL.h>
#endif

Font PS2P;
Layer BG,context,sky,nightsky,tsky,srgrad,moon,lunarshine,borders_n,borders,virtualsky,hdr,scenery;
int stime=1000; 
/*
0 - midnight
1000 - moonset
1350 - dawn 
1800 - sunrise 
3600 - midday
5400 - sunset
5850 - twilight
6200 - moonrise
*/

int init()
{
	buildLayer(context,xmax,ymax);
	buildLayer(sky,xmax,ymax);
	buildLayer(tsky,xmax,ymax);
	buildLayer(virtualsky,xmax,ymax);
	buildLayer(hdr,xmax,ymax);
	buildLayer(scenery,xmax,ymax);
	buildLayer(borders_n,xmax,ymax);
	buildLayer(borders,xmax,ymax);
	buildLayer(lunarshine,60,60);
	hdr.mode = 1;
	tex_read("TEST/bg.tga",BG);
	tex_read("TEST/sunrise.tga",srgrad);
	tex_read("TEST/nightsky.tga",nightsky);
	tex_read("TEST/moon.tga",moon);
	FindTransparencyBorder(BG,borders_n,128,true);
//	Fill(borders_n,128,0,199);
	FixBorder(borders_n,128);
	FDrawRect(lunarshine,0x00FFFFFF,0,0,60,60);
	CircularShine(lunarshine,92,29,29,20,10,RENDER_ADD_ALPHA);
	PS2P.CreateMonospacedFont("FONT/font10p.tga",8);
	return 0;
}

void OP()
{
	//sky
	reset(sky);
	reset(virtualsky);
	FDrawRect(hdr,0x00FFFFFF,0,0,xmax,ymax);
	int standarttime = stime>3600?stime-7200:stime;
	int nighttime = standarttime+1800;
	FDrawRect(tsky,0xFF000000,0,0,xmax,ymax);
	if (nighttime < 3200 && nighttime>0) 
	{
		FragmentLayer(nightsky,sky,0,0,nighttime*320/3200,0,xmax,ymax);
		if (abs(standarttime)>1000) DrawRect(sky,tA(255-(((abs(standarttime)-1000)*255)/400)),0,0,xmax,ymax,RENDER_MULT_ALPHA);
	}
	if (stime>1000 && stime<2400)
	{
		int otime = stime-1200;
		ZoomRender(srgrad,tsky,0,0,xmax,ymax,(stime-1000)*255/1400,0,1,256,0);
	}
	IncludeLayer(sky,tsky,0,0,1);
	//moon
	if (nighttime < 3200) 
	{
		int lunax = -(float)cos((standarttime/20+90)*3.14/180)*150+150;
		int lunay = -(float)sin((standarttime/20+90)*3.14/180)*250+270;
		IncludeLayer(lunarshine,tsky,lunax-10,lunay-10,1);
		IncludeLayer(moon,tsky,lunax,lunay);
		RadialShine(virtualsky,255,lunax+20,lunay+20,40,RENDER_ADD_ALPHA);
		SetBordersBySize(hdr,lunax+10,lunay+10,60,60);
		SetBordersBySize(borders_n,lunax+10,lunay+10,60,60);
		LinearTransparencyBorder(borders_n,hdr,128,lunax+20,lunay+20,8);
		IncludeLayer(virtualsky,hdr,0,0,RENDER_MULT_ALPHA);
	}

	//scenery
	reset (scenery);
	IncludeLayer(BG,scenery,0,0);
	if (nighttime > 0 && nighttime < 3200) 
	{
		int b,t;
		if (nighttime<1900) b=64;
		else if (nighttime<2200) b=(2200-nighttime)*60/300+4;
		else b = 4;
		if (abs(standarttime)>1000) t = 60+((abs(standarttime)-1000)*191)/400;
		else t = 60;
		DrawRect(scenery,tRGB(t+b,t+b,t+2*b-4),0,0,xmax,ymax,RENDER_MULT);
	}
	reset(context);
	char strn[64];
	sprintf(strn,"%i | %i | %i",fps,nighttime, standarttime);
	PrintText(context,PS2P,strn,ARGB(128,255,255,255),0,0);

	StackedRender(4,tsky.id,scenery.id,hdr.id,context.id);
	stime++;
	(stime==7200)?stime=0:0;
}

void KOP()
{
}

bool set_read()
{
	FILE *set_file;
	char set_path[] = "DATA/SETTINGS.DAT";
	int tmp;
	set_file = fopen(set_path, "r"); 
	fscanf(set_file, "%i %i", &rxmax, &rymax);
	fscanf(set_file, "%i %i", &xmax, &ymax);
	fscanf(set_file, "%i", &tmp);
	if (tmp == 1) 
	{
		fullscreen=true;
	}
	else
	{
		fullscreen=false;
	}
	fscanf(set_file, "%i %i", &l_targetfps, &l_minframeskip);
	fclose(set_file);
	return true;
}

int main(int argc, char** argv)
{
	if(!set_read())
	{
		fprintf(stderr, "Failed to load settings\n");
        return 1;							
	}

	if (exec() != 0) Quit(1);

	if (init() != 0) Quit(1);

	while(1)
	{
		if (process() !=0) Quit(1);
		OP();		
		KOP();
		
	}
	
	return 0;
}
