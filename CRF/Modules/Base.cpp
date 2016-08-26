/*

  Basic drawing

*/

#include "../Core.h"
#include "../Layer.h"
#include "Base.h"
#include <stdarg.h>

void DrawVLine(Layer& id, unsigned int color, int x1, int y1, int k)
{
	unsigned int a,r,g,b;
	int i;
	ARGBt(color,&a,&r,&g,&b);
	for (i = 0; i<k; i++)
			MSDrawC(id,x1,y1+i,a,r,g,b,0);
	for (i = 0; i>=k; i--)
			MSDrawC(id,x1,y1+i,a,r,g,b,0);
}
	
void DrawHLine(Layer& id, unsigned int color, int x1, int y1, int k)
{
	unsigned int a,r,g,b;
	int i;
	ARGBt(color,&a,&r,&g,&b);
	for (i = 0; i<k; i++)
			MSDrawC(id,x1+i,y1,a,r,g,b,0);
	for (i = 0; i>=k; i--)
			MSDrawC(id,x1+i,y1,a,r,g,b,0);
}
	
void DrawRect(Layer& id, unsigned int color, int x1, int y1, int xk, int yk, int mode)
{
	unsigned int a,r,g,b;
	int i,j;
	ARGBt(color,&a,&r,&g,&b);
	for (i = 0; i<xk; i++)
		for (j = 0; j<yk; j++)
			MSDrawC(id,x1+i,y1+j,a,r,g,b,mode);
}
	
void VGradient(Layer& id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode)
{
	int a1,r1,g1,b1,a2,r2,g2,b2,da,dr,dg,db;
	int i,j;
	ARGBt(colorA,&a1,&r1,&g1,&b1);
	ARGBt(colorB,&a2,&r2,&g2,&b2);
	
	for (j=0; j<yk; j++)
	{
		da = a1 + ((a2 - a1) * j / yk);
		dg = g1 + ((g2 - g1) * j / yk);
		db = b1 + ((b2 - b1) * j / yk);
		dr = r1 + ((r2 - r1) * j / yk);
		for (i=0; i<xk; i++)
			MSDrawC(id, i+x1, j+y1, da, dr, dg, db, mode);
	}
}
	
void HGradient(Layer& id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode)
{
	int a1,r1,g1,b1,a2,r2,g2,b2,da,dr,dg,db;
	int i,j;
	ARGBt(colorA,&a1,&r1,&g1,&b1);
	ARGBt(colorB,&a2,&r2,&g2,&b2);
	
	for (i=0; i<xk; i++)
	{
		da = a1 + ((a2 - a1) * i / xk);
		dg = g1 + ((g2 - g1) * i / xk);
		db = b1 + ((b2 - b1) * i / xk);
		dr = r1 + ((r2 - r1) * i / xk);
		for (j=0; j<yk; j++)
			MSDrawC(id, i+x1, j+y1, da, dr, dg, db, mode);
	}
}
	
void FragmentLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode)
{
	unsigned int a,r,g,b;
	int i,j,mx,my,nx,ny;

	if (tx<0) nx = -tx;
	else nx = 0;
	if (ty<0) ny = -ty;
	else ny = 0;

	if (xk+tx>getWidth(tid)) mx = getWidth(tid)-tx;
	else mx = xk;
	if (yk+ty>getHeight(tid)) my = getHeight(tid)-ty;
	else my = yk;

	for (i = nx; i<mx; i++)
		for (j = ny; j<my; j++)
		{	
			ARGBt(getColor(id,x2 + i,y2 + j),&a,&r,&g,&b);
			MSDrawC(tid,tx+i,ty+j,a,r,g,b,mode);
		}
}

void DrawFrame(Layer& id, unsigned int color, int x, int y, int xk, int yk)
{
	DrawHLine(id,color,x,y,xk);
	DrawHLine(id,color,x,y+yk-1,xk);
	DrawVLine(id,color,x,y,yk);
	DrawVLine(id,color,x+xk-1,y,yk);
}

void ColorFill (Layer& id, unsigned int msc, int x, int y)
{
	unsigned int cvr = getColor(id,x,y);
	if (msc == cvr) return;
	plot(id,x,y,msc);
	if (x>0 && getColor(id,x-1,y) == cvr) ColorFill(id,msc,x-1,y);
	if (y>0 && getColor(id,x,y-1) == cvr) ColorFill(id,msc,x,y-1);
	if (x+1<getWidth(id) && getColor(id,x+1,y) == cvr) ColorFill(id,msc,x+1,y);
	if (y+1<getHeight(id) && getColor(id,x,y+1) == cvr) ColorFill(id,msc,x,y+1);
}

void StackedRender(int count, ...)
{
	va_list ap;
	va_start(ap,count);
	Layer context;
	buildLayer(context,xmax,ymax);
	for (int i=0; i<count; i++) IncludeLayer(*_cnv[va_arg(ap,int)],context,0,0);
	va_end(ap);
	renderer(context);
}

