/*

  Zooming procedure. Using:

  ZoomRender(
  <int> source Layer& id,
  <int> target Layer& id,
  <int> x coordinate of top left corner at target,
  <int> y coordinate of top left corner at target,
  <int> final width,
  <int> final height,
  [<int> x coordinate of top left corner at source] | default 0,
  [<int> y coordinate of top left corner at source] | default 0,
  [<int> piece width] | default full,
  [<int> piece height] | default full,
  [<int> mode]);

*/

#include "../Base.h"
#include "../../Core.h"
#include "../../Layer.h"

void ZoomRender(Layer& id, Layer& tid, int tx, int ty, int x1, int y1, int cx, int cy, int x2, int y2, int mode)
{
	unsigned int a,r,g,b;
	int i,j,mx,my,nx,ny;
	float xt,yt;

	if (tx<0) nx = -tx;
	else nx = 0;
	if (ty<0) ny = -ty;
	else ny = 0;

	if (x1+tx>getWidth(tid)) mx = getWidth(tid)-tx;
	else mx = x1;
	if (y1+ty>getHeight(tid)) my = getHeight(tid)-ty;
	else my = y1;

	for (i = nx; i<mx; i++)
		for (j = ny; j<my; j++)
		{	
			xt = (float)x2/x1;
			yt = (float)y2/y1;
			ARGBt(getColor(id,cx + (int)(i*xt),cy + (int)(j*yt)),&a,&r,&g,&b);
			MSDrawC(tid,tx+i,ty+j,a,r,g,b,mode);
		}

}
