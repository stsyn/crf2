#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "CRF.h"

#ifdef WIN32
	#include <windows.h>
	#include <GL\gl.h>
	#include <GL\glu.h>
	#include "SDL2\SDL.h"
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <SDL2/SDL.h>
#else //UNIX
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <SDL2/SDL.h>
#endif

Layer tech, trixie, context, lighting, circle, hdr;
Font PS2P;

int init()
{

	tex_read("trixie.tga",trixie);
	buildLayer(context,xmax,ymax);
	buildLayer(lighting,xmax,ymax);
	buildLayer(hdr,xmax,ymax);
	buildLayer(tech,xmax,ymax);
	buildLayer(circle,xmax,ymax);
	PS2P.CreateMonospacedFont("FONT/font10p.tga",8);
	return 0;
}

void OP()
{
	FDrawRect(tech,tRGB(0,0,0),0,0,xmax,ymax);
	reset(context);
	reset(lighting);
	ZoomRender(trixie,context,(xmax-getWidth(trixie)*ymax/getHeight(trixie))/2,0,getWidth(trixie)*ymax/getHeight(trixie),ymax);
	MoveLayer(context,-10,-10);
//	FindTransparencyBorder(context,lighting,255,true);
//	FixBorder(lighting,255);
//	LinearTransparencyBorder(lighting,hdr,255,260,100,16);
//	DrawRect(context,tRGB(64,64,64),0,0,xmax,ymax,2);
//	Overlay(hdr,tRGB(255,255,255));
//	IncludeLayer(hdr,context,0,0,1);
//	hdr.mode=RENDER_ADD;
	char strn[16];
	DrawRect(context,tRGB(128,128,128),0,0,xmax,ymax,2);

	sprintf(strn,"%i | %i | %i",fps,frameskip, dticks);
	PrintText(context,PS2P,strn,ARGB(128,255,255,255),0,0);

	renderer(context);
//	StackedRender(2,context.id,hdr.id);
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
