#include "../Core.h"
#include "../Layer.h"

void TransformLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode)
{
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

void MoveLayer(Layer& id, int xa, int ya)
{
	int sx,sy,dx,dy,ex,ey;
	int atxa=xa, atya=ya;

	if (atxa<=0)
	{
		sx=atxa; ex=getWidth(id)-1; dx=1;
	}
	else if (atxa>0)
	{
		sx=getWidth(id)-1; ex=atxa; dx=-1;
	}
	while (1)
	{
		if (sx == ex) break;
		if (atya<=0)
		{
			sy=atya; ey=getHeight(id)-1; dy=1;
		}
		else if (atya>0)
		{
			sy=getHeight(id)-1; ey=atya; dy=-1;
		}
		while (1)
		{
			if (sy == ey) break;
			plot(id,sx,sy,getColor(id,sx-atxa,sy-atya));
			sy+=dy;
		}
		sx+=dx;
	}
}
