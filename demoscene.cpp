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
#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <SDL2/SDL.h>
#endif

Font PS2P;
Layer BG,		//tile
	lighting,	//at night
	context,	//counters
	sky,		//sky canvas
	nightsky,   //sky bg
	tsky,		//late canvas
	srgrad,		//sunrise gradient
	ssgrad,		//sunset gradient
	moon,		//moon sprite
	lunarshine,	//easy, right?
	sun,		//sun but not sprite
	sunshine,	//easy, right?
	borders_n,	//night borders
	borders,	//dunno
	virtualsky,	//shader
	hdr,		//shader too
	scenery,	//bg canvas
	blicks,		//graphonii
	din_water,  //moar
	din_water_proc,		//moar
	din_water_render,	//moar
	stat_water,			//moar
	stat_water_proc,	//moar
	stat_water_render,	//moar
	_moon_size;	//dinamic light (and for sun too)
int stime=500, l_size=6241, s_size = 2401;
long unsigned int stframe=0;
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
	buildLayer(hdr,xmax,ymax);
	buildLayer(scenery,xmax,ymax);
	buildLayer(borders_n,xmax,ymax);
	buildLayer(borders,xmax,ymax);
	buildLayer(din_water_proc,xmax,ymax);
	buildLayer(din_water_render,xmax,ymax);
	buildLayer(stat_water_render,xmax,ymax);
	buildLayer(lunarshine,60,60);
	buildLayer(sunshine,100,100);
	buildLayer(sun,50,50);
	buildLayer(blicks,xmax,ymax);
	hdr.mode = 1;
	tex_read("TEST/bg.tga",BG);
	tex_read("TEST/sunrise.tga",srgrad);
	tex_read("TEST/light.tga",lighting);
	tex_read("TEST/sunset.tga",ssgrad);
	tex_read("TEST/nightsky.tga",nightsky);
	tex_read("TEST/moon.tga",moon);
	tex_read("TEST/dinamic_water.tga",din_water);
	tex_read("TEST/static_water.tga",stat_water);

	FindTransparencyBorder(BG,borders_n,128,true);

	buildLayer(sky,borders_n.lcnv[2]-borders_n.lcnv[0]+1,borders_n.lcnv[3]-borders_n.lcnv[1]+1);
	buildLayer(tsky,borders_n.lcnv[2]-borders_n.lcnv[0]+1,borders_n.lcnv[3]-borders_n.lcnv[1]+1);
	buildLayer(virtualsky,borders_n.lcnv[2]-borders_n.lcnv[0]+1,borders_n.lcnv[3]-borders_n.lcnv[1]+1);

	CalcBorder(din_water);
	SetBorders(din_water_proc,din_water.lcnv[0],din_water.lcnv[1],din_water.lcnv[2],din_water.lcnv[3]);
	SetBorders(din_water_render,din_water.lcnv[0],din_water.lcnv[1],din_water.lcnv[2],din_water.lcnv[3]);
	BWNoise(din_water_proc,din_water.lcnv[0],din_water.lcnv[1],din_water.lcnv[2]-din_water.lcnv[0]+1,din_water.lcnv[3]-din_water.lcnv[1]+1,128,64);

	CalcBorder(stat_water);
	buildLayer(stat_water_proc,stat_water.lcnv[2]-stat_water.lcnv[0]+1,stat_water.lcnv[3]-stat_water.lcnv[1]+1);

	FixBorder(borders_n,128);

	FDrawRect(lunarshine,0x00FFFFFF,0,0,60,60);
	CircularShine(lunarshine,92,29,29,20,10,RENDER_ADD_ALPHA);

	DrawFillCircle(sun,0xff48cfff,25,25,24);
	FDrawRect(sunshine,0x0048cfff,0,0,100,100);
	CircularShine(sunshine,112,49,49,25,25,RENDER_ADD_ALPHA);

	blicks.mode = RENDER_ADD;

	PS2P.CreateMonospacedFont("FONT/font10p.tga",8);
	return 0;
}

void OP()
{

if (frameskip==0 || frame % frameskip == 0)
{
	int standarttime = stime>3600?stime-7200:stime;
	int nighttime = standarttime+1800;
	//sky
if (stframe % 4 == 0)
{
	reset(sky);
	reset(virtualsky);
	FDrawRect(tsky,0xFF000000,0,0,getWidth(tsky),getHeight(tsky));
	if (nighttime < 3200 && nighttime>0)
	{
		FragmentLayer(nightsky,sky,0,0,nighttime*320/3200,0,xmax,ymax);
		if (standarttime>1000) DrawRect(sky,tA(255-(((abs(standarttime)-1000)*255)/400)),0,0,xmax,ymax,RENDER_MULT_ALPHA);
		if (standarttime<-1400) DrawRect(sky,tA(255-(((abs(standarttime)-1400)*255)/400)),0,0,xmax,ymax,RENDER_MULT_ALPHA);
	}
	if (stime>1000 && stime<2200)
	{
		int otime = stime-1200;
		ZoomRender(srgrad,tsky,0,0,getWidth(tsky),getHeight(tsky),(stime-1000)*255/1200,0,1,256,0);
	}
	else if (standarttime>-2400 && standarttime<-1400)
	{
		int otime = stime-1200;
		ZoomRender(ssgrad,tsky,0,0,getWidth(tsky),getHeight(tsky),(2400+standarttime)*255/1000,0,1,256,0);
	}
	else if (nighttime < 3200 && nighttime>0) {}
	else
	{
		FDrawRect(tsky,0xFFfdbb75,0,0,getWidth(tsky),getHeight(tsky));
	}
	IncludeLayer(sky,tsky,0,0);

	//moon
	if (nighttime < 3200 && nighttime>0)
	{
		int lunax = -(float)cos((standarttime/20+90)*3.14/180)*150+150;
		int lunay = -(float)sin((standarttime/20+90)*3.14/180)*250+270;
		IncludeLayer(lunarshine,tsky,lunax-10,lunay-10,1);
		IncludeLayer(moon,tsky,lunax,lunay);
if (stframe % 8 == 0)
{
		FDrawRect(hdr,0x00FFFFFF,0,0,xmax,ymax);
		SetBorders(virtualsky,0,0,getWidth(virtualsky)-1,getHeight(virtualsky)-1);
		RadialShine(virtualsky,255,lunax+20,lunay+20,40,RENDER_ADD_ALPHA);
		SetBordersBySize(hdr,lunax-10,lunay-10,80,80);
		SetBordersBySize(borders_n,lunax-10,lunay-10,80,80);
		LinearTransparencyBorder(borders_n,hdr,128,lunax+20,lunay+20,8);
		IncludeLayer(virtualsky,hdr,0,0,RENDER_MULT_ALPHA);

		ANDNOT(virtualsky,BG,_moon_size);
		CalcBorder(_moon_size);
}
	}

	//sun
	if (nighttime > 3200 || nighttime<0)
	{
		int lunax = -(float)cos((standarttime/20-75)*3.14/180)*150+150;
		int lunay = -(float)sin((standarttime/20-75)*3.14/180)*250+170;
		IncludeLayer(sunshine,tsky,lunax-20,lunay-20,1);
		IncludeLayer(sun,tsky,lunax+5,lunay+5);
if (stframe % 8 == 0)
{
		FDrawRect(hdr,0x00FFFFFF,0,0,xmax,ymax);
		FDrawRect(blicks,0xFF000000,0,0,xmax,ymax);
		IncludeLayer(sun,virtualsky,lunax+5,lunay+5);
		CalcBorder(virtualsky);
		ANDNOT(virtualsky,BG,_moon_size);
		CalcBorder(_moon_size);

		if (lunay+30<ymax && lunax<240)
		{
			SetBordersBySize(hdr,0,0,xmax,ymax);
			SetBordersBySize(borders_n,0,0,xmax,ymax);
			LinearTransparencyBorder(borders_n,hdr,196,lunax+30,lunay+30,10);
		}
		if (stime<2200) DrawRect(hdr,tA(BordersSize(_moon_size)*255/s_size),0,0,xmax,ymax,RENDER_MULT_ALPHA);
		if (BordersSize(_moon_size)>100)
		{
			SolarShine(blicks,lunax+30,lunay+30,128);
			DrawRect(blicks,tA(BordersSize(_moon_size)*255/s_size),0,0,xmax,ymax,RENDER_MULT_ALPHA);
		}
	}
}
}
if ((stframe % 4 == 2) || stframe == 0)
{
	//scenery
	reset (scenery);
	IncludeLayer(BG,scenery,0,0);

	//water

	reset(din_water_render);
	MoveLayer(din_water_proc,0,1);
	BWNoise(din_water_proc,din_water.lcnv[0],din_water.lcnv[1],din_water.lcnv[2]-din_water.lcnv[0]+1,1,128,64);
	IncludeLayer(din_water_proc,din_water_render,0,0);
	IncludeLayer(din_water,din_water_render,0,0,RENDER_MULT_ALPHA);
	IncludeLayer(din_water_render,scenery,0,0,RENDER_MULT);

	if (nighttime > 0 && nighttime < 3400)
	{
		int b,t;
		b = BordersSize(_moon_size)*60/6241+4;
		if (standarttime>1200) t = 60+((standarttime-1200)*191)/400;
		else if (standarttime<-1400) t = 60+((abs(standarttime)-1400)*191)/400;
		else t = 60;
		if (t+2*b>255) b = (255-t)/2;
		DrawRect(scenery,tRGB(t+b,t+b,t+2*b),0,0,xmax,ymax,RENDER_MULT);
	}
	else
	{
		DrawRect(scenery,tRGB(BordersSize(_moon_size)*64/s_size,BordersSize(_moon_size)*64/s_size,0),0,0,xmax,ymax,RENDER_ADD);
	}
	if (nighttime > 200 && nighttime < 1400) IncludeLayer(lighting,scenery,0,0,1);
}
	//compilation
	reset(context);
	IncludeLayer(tsky,context,0,0);
	if (nighttime > 3200 || nighttime<0)
	{
		if ((stframe % 4 == 2) || stframe == 0)IncludeLayer(hdr,scenery,0,0);
		IncludeLayer(scenery,context,0,0);
	}
	else
	{
		IncludeLayer(scenery,context,0,0);
		IncludeLayer(hdr,context,0,0);
	}

if ((stframe % 8 == 3) || stframe == 0)
{
	//refractions
	ZoomRender(context,stat_water_proc,0,0,getWidth(stat_water_proc),getHeight(stat_water_proc),stat_water.lcnv[0],0,getWidth(stat_water_proc),stat_water.lcnv[1],0);
	TransformLayer(stat_water_proc,stat_water_render,stat_water.lcnv[0],stat_water.lcnv[1],1);
	IncludeLayer(stat_water,stat_water_render,0,0,RENDER_MULT_ALPHA);
}
	IncludeLayer(stat_water_render,context,0,0);
	IncludeLayer(blicks,context,0,0);

	char strn[64];
	sprintf(strn,"%i | %i | %i",fps,frameskip, dticks);
	PrintText(context,PS2P,strn,ARGB(196,255,255,255),0,0);
	renderer(context);
	stframe++;
}
(frame%2==0)?stime++:0;
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
