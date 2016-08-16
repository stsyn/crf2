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

int init()
{
	tex_read("DATA/TEXT/trixie.tga",101);
	buildLayer(100,xmax,ymax);
	buildLayer(103,xmax,ymax);
	buildLayer(104,xmax,ymax);
	return 0;
}

void OP()
{
	FDrawRect(103,tRGB(0,0,0),0,0,xmax,ymax);
	reset(104);
	plot(104,xmax/2,ymax/2,0,0,0);
	Smooth(104,192,255);
	Overlay(104,tRGB(128,128,128));
	IncludeLayer(104,103,0,0);
	reset(100);
	reset(200);
	ZoomRender(101,100,(xmax-getWidth(101)*ymax/getHeight(101))/2,0,getWidth(101)*ymax/getHeight(101),ymax);
	DrawRect(100,tRGB(64,64,64),0,0,xmax,ymax,2);
	FindTransparencyBorder(100,200,255);
	Smooth(200,8,255);
	Overlay(200,tRGB(64,64,64));
	IncludeLayer(104,200,0,0,7);
	IncludeLayer(200,100,0,0,1);
	IncludeLayer(100,103,0,0);
	renderer(103);
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
