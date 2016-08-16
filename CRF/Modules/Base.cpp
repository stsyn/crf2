/*

  Basic drawing

*/

#include <stdio.h>
#include <string.h>
#include "../Core.h"

void DrawVLine(int id, unsigned int color, int x1, int y1, int k)
{
	unsigned int a,r,g,b;
	int i;
	ARGBt(color,&a,&r,&g,&b);
	for (i = 0; i<k; i++)
			plot(id,x1,y1+i,a,r,g,b);
	for (i = 0; i>=k; i--)
			plot(id,x1,y1+i,a,r,g,b);
}

void FDrawVLine(int id, unsigned int color, int x1, int y1, int k)
{
	int i;
	for (i = 0; i<k; i++)
			plot(id,x1,y1+i,color);
	for (i = 0; i>=k; i--)
			plot(id,x1,y1+i,color);
}
	
void DrawHLine(int id, unsigned int color, int x1, int y1, int k)
{
	unsigned int a,r,g,b;
	int i;
	ARGBt(color,&a,&r,&g,&b);
	for (i = 0; i<k; i++)
			plot(id,x1+i,y1,a,r,g,b);
	for (i = 0; i>=k; i--)
			plot(id,x1+i,y1,a,r,g,b);
}

void FDrawHLine(int id, unsigned int color, int x1, int y1, int k)
{
	int i;
	for (i = 0; i<k; i++)
			plot(id,x1+i,y1,color);
	for (i = 0; i>=k; i--)
			plot(id,x1+i,y1,color);
}
	
void DrawRect(int id, unsigned int color, int x1, int y1, int xk, int yk)
{
	unsigned int a,r,g,b;
	int i,j;
	ARGBt(color,&a,&r,&g,&b);
	for (i = 0; i<xk; i++)
		for (j = 0; j<yk; j++)
			plot(id,x1+i,y1+j,a,r,g,b);
}

void FDrawRect(int id, unsigned int color, int x1, int y1, int xk, int yk)
{
	int i,j;
	for (i = 0; i<xk; i++)
		for (j = 0; j<yk; j++)
			plot(id,x1+i,y1+j,color);
}
	
void DrawRect(int id, unsigned int color, int x1, int y1, int xk, int yk, int mode)
{
	unsigned int a,r,g,b;
	int i,j;
	ARGBt(color,&a,&r,&g,&b);
	for (i = 0; i<xk; i++)
		for (j = 0; j<yk; j++)
		{	
			if (a != 255) {
				if (mode == 0) plot(id,x1+i,y1+j,a,r,g,b);
				else if (mode == 1) add(id,x1+i,y1+j,a,r,g,b);
				else if (mode == 2) mult(id,x1+i,y1+j,a,r,g,b);
				else if (mode == 3) transparency(id,x1+i,y1+j,a);
				else if (mode == 4) invert(id,x1+i,y1+j);
				else if (mode == 5) rem(id,x1+i,y1+j,a,r,g,b);
				else if (mode == 6) multa(id,x1+i,y1+j,a);
			}
			else
				{
				if (mode == 0) plot(id,x1+i,y1+j,r,g,b);
				else if (mode == 1) add(id,x1+i,y1+j,r,g,b);
				else if (mode == 2) mult(id,x1+i,y1+j,r,g,b);
				else if (mode == 3) transparency(id,x1+i,y1+j,a);
				else if (mode == 4) invert(id,x1+i,y1+j);
				else if (mode == 5) rem(id,x1+i,y1+j,r,g,b);
			}
		}
}

void DoGray(int id, int tid, unsigned int value, int x1, int y1)
{
	unsigned int a,r,g,b;
	int i,j;
	for (i = 0; i<getWidth(id); i++)
		for (j = 0; j<getHeight(id); j++)
		{	
			ARGBt(getColor(id,i,j),&a,&r,&g,&b);
			if (a == 0) continue;
			grayer(id,tid,x1+i,y1+j,i,j,value);
		}
}
	
void VGradient(int id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode)
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
		{
			if (mode == 0) plot(id, i+x1, j+y1, da, dr, dg, db);
			if (mode == 1) add(id, i+x1, j+y1, da, dr, dg, db);
			if (mode == 2) mult(id, i+x1, j+y1, da, dr, dg, db);
			if (mode == 3) transparency(id, i+x1, j+y1, da);
			if (mode == 5) rem(id, i+x1, j+y1, da, dr, dg, db);
		}
	}
}
	
void HGradient(int id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode)
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
		{
			if (mode == 0) plot(id, i+x1, j+y1, da, dr, dg, db);
			else if (mode == 1) add(id, i+x1, j+y1, da, dr, dg, db);
			else if (mode == 2) mult(id, i+x1, j+y1, da, dr, dg, db);
			else if (mode == 3) transparency(id, i+x1, j+y1, da);
			else if (mode == 5) rem(id, i+x1, j+y1, da, dr, dg, db);
		}
	}
}
	
void IncludeLayer(int id, int tid, int x1, int y1, int mode)
{
	unsigned int a,r,g,b;
	int i,j,mx,my,nx,ny;

	if (x1<0) nx = -x1;
	else nx = 0;
	if (y1<0) ny = -y1;
	else ny = 0;
	
	if (getWidth(id)+x1>getWidth(tid)) mx = getWidth(tid)-x1;
	else mx = getWidth(id);
	if (getHeight(id)+y1>getHeight(tid)) my = getHeight(tid)-y1;
	else my = getHeight(id);

	for (i = nx; i<mx; i++)
		for (j = ny; j<my; j++)
		{	
			ARGBt(getColor(id,i,j),&a,&r,&g,&b);
			if (a == 0 && mode!=6) continue;
			if (a != 255) 
			{
				if (mode == 0) plot(tid,x1+i,y1+j,a,r,g,b);
				else if (mode == 1) add(tid,x1+i,y1+j,a,r,g,b);
				else if (mode == 2) mult(tid,x1+i,y1+j,a,r,g,b);
				else if (mode == 3) transparency(tid, i+x1, j+y1, a);
				else if (mode == 5) rem(tid,x1+i,y1+j,a,r,g,b);
				else if (mode == 6) multa(tid,x1+i,y1+j,a);
				else if (mode == 7) rema(tid,x1+i,y1+j,a);
			}
			else
			{
				if (mode == 0) plot(tid,x1+i,y1+j,getColor(id,i,j));
				else if (mode == 1) add(tid,x1+i,y1+j,r,g,b);
				else if (mode == 2) mult(tid,x1+i,y1+j,r,g,b);
				else if (mode == 3) transparency(tid,i+x1, j+y1, 255);
				else if (mode == 5) rem(tid,x1+i,y1+j,r,g,b);
			}
		}
}

void IncludeLayer(int id, int tid, int x1, int y1)
{
	IncludeLayer(id,tid,x1,y1,0);
}
	
void FragmentLayer(int id, int tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode)
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
			if (a == 0 && mode!=6) continue;
			if (a != 255) 
			{
				if (mode == 0) plot(tid,tx+i,ty+j,a,r,g,b);
				else if (mode == 1) add(tid,tx+i,ty+j,a,r,g,b);
				else if (mode == 2) mult(tid,tx+i,ty+j,a,r,g,b);
				else if (mode == 5) rem(tid,tx+i,ty+j,a,r,g,b);
				else if (mode == 6) multa(tid,tx+i,ty+j,a);
			}
			else
			{
				if (mode == 0) plot(tid,tx+i,ty+j,getColor(id,x2 + i,y2 + j));
				else if (mode == 1) add(tid,tx+i,ty+j,r,g,b);
				else if (mode == 2) mult(tid,tx+i,ty+j,r,g,b);
				else if (mode == 5) rem(tid,tx+i,ty+j,r,g,b);
			}
		}
}

void FragmentLayer(int id, int tid, int tx, int ty, int x2, int y2, int xk, int yk)
{
	FragmentLayer(id,tid,tx,ty,x2,y2,xk,yk,0);
}

void BWNoise(int id, int x1, int y1, int xk, int yk)
{
	int i,j,t;
	for (i = 0; i<xk; i++)
		for (j = 0; j<yk; j++)
		{	
			t = gener(256);
			plot(id,x1+i,y1+j,t,t,t);
		}
}

void TransformLayer(int id, int tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode)
{
	/*

  modes:
  0 - none
  1 - invert vertical
  2 - invert horizontal
  3 - rotate 180
  4 - transponation //later
	*/
	unsigned int a,r,g,b;
	int i,j,mx,my,nx,ny,tdx, tdy, ax, ay;

	if (tx<0) nx = -tx;
	else nx = 0;
	if (ty<0) ny = -ty;
	else ny = 0;

	if ((mode & 4) == 4)
	{
		ax = yk;
		ay = xk;
	}
	else
	{
		ax = xk;
		ay = yk;
	}

	int bx = x2, by = y2;
	if ((mode & 4) == 4)
	{
		bx = y2;
		by = x2;
	}

	if (ax+tx>getWidth(tid)) mx = getWidth(tid)-tx;
	else mx = ax;
	if (ay+ty>getHeight(tid)) my = getHeight(tid)-ty;
	else my = ay;

	for (i = nx; i<mx; i++)
		for (j = ny; j<my; j++)
		{	
			if ((mode & 1) == 1) tdy=ay-j+by-1;
			else tdy=by + j;
			if ((mode & 2) == 2) tdx=ax-i+bx-1;
			else tdx=bx + i;
			if ((mode & 4) == 4) ARGBt(getColor(id,tdy,tdx),&a,&r,&g,&b);
			else ARGBt(getColor(id,tdx,tdy),&a,&r,&g,&b);
			if (a == 0) continue;
			if (a != 255) 
			{
				plot(tid,tx+i,ty+j,a,r,g,b);
			}
			else
			{
				if ((mode & 4) == 4) plot(tid,tx+i,ty+j,getColor(id,tdy,tdx));
				else plot(tid,tx+i,ty+j,getColor(id,tdx,tdy));
			}
		}
}

void TransformLayer(int id, int tid, int tx, int ty, int mode)
{
	/*
 0 6 3 5
  modes:
  0 - none
  1 - invert vertical
  2 - invert horizontal
  3 - rotate 180
  4 - invert diagonal
  5 - rotate left
  6 - rotate right
  7 - i dunno
	*/
	unsigned int a,r,g,b;
	int i,j,mx,my,nx,ny,tdx, tdy,ax,ay;

	if (tx<0) nx = -tx;
	else nx = 0;
	if (ty<0) ny = -ty;
	else ny = 0;

	if ((mode & 4) == 4)
	{
		ax = getHeight(id);
		ay = getWidth(id);
	}
	else
	{
		ax = getWidth(id);
		ay = getHeight(id);
	}
	
	if (ax+tx>getWidth(tid)) mx = getWidth(tid)-tx;
	else mx = ax;
	if (ay+ty>getHeight(tid)) my = getHeight(tid)-ty;
	else my = ay;

	for (i = nx; i<mx; i++)
		for (j = ny; j<my; j++)
		{	
			if ((mode & 1) == 1) tdy=ay-j-1;
			else tdy=j;
			if ((mode & 2) == 2) tdx=ax-i-1;
			else tdx=i;
			if ((mode & 4) == 4) ARGBt(getColor(id,tdy,tdx),&a,&r,&g,&b);
			else ARGBt(getColor(id,tdx,tdy),&a,&r,&g,&b);
			if (a == 0) continue;
			if (a != 255) 
			{
				plot(tid,tx+i,ty+j,a,r,g,b);
			}
			else
			{
				if ((mode & 4) == 4) plot(tid,tx+i,ty+j,getColor(id,tdy,tdx));
				else plot(tid,tx+i,ty+j,getColor(id,tdx,tdy));
			}
		}
}

void DrawFrame(int id, unsigned int color, int x, int y, int xk, int yk)
{
	FDrawHLine(id,color,x,y,xk);
	FDrawHLine(id,color,x,y+yk-1,xk);
	FDrawVLine(id,color,x,y,yk);
	FDrawVLine(id,color,x+xk-1,y,yk);
}


