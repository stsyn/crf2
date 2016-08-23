#include "../Core.h"
#include "Base.h"
#include "../Layer.h"
#include <math.h>

void DrawLine(Layer& id, unsigned int color, int x0, int y0, int x1, int y1) 
{
    int dx = abs(x1 - x0),
        sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0),
        sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    while (true) {
        plot(id, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}

void Pixel_circle (Layer& id, int xc,int yc,int x,int y,unsigned int pixel)
{
   plot(id, xc+x, yc+y, pixel);
   plot(id, xc+y, yc+x, pixel);
   plot(id, xc+y, yc-x, pixel);
   plot(id, xc+x, yc-y, pixel);
   plot(id, xc-x, yc-y, pixel);
   plot(id, xc-y, yc-x, pixel);
   plot(id, xc-y, yc+x, pixel);
   plot(id, xc-x, yc+y, pixel);
}

void DrawCircle (Layer& id, unsigned int color, int xc, int yc, int r)
{  int  x, y, d;
   x= 0;  y= r;  d= 3 - 2*r;
   while (x < y) {
      Pixel_circle (id,xc, yc, x, y, color);
      if (d < 0) d= d + 4*x + 6; else {
         d= d + 4*(x-y) + 10;  --y;
      }
      ++x;
   }
   if (x == y) Pixel_circle (id,xc, yc, x, y, color);
}

void DrawFillCircle(Layer& id, unsigned int color, int x, int y, int radius)
{
	DrawCircle(id,color,x, y,radius);
	ColorFill(id,color,x,y);
}

void DrawPoligon(Layer& id, int color, int x1, int y1, int x2, int y2, int x3, int y3) 
{ 
	DrawLine(id, color, x1, y1, x2, y2);
	DrawLine(id, color, x1, y1, x3, y3);
	DrawLine(id, color, x3, y3, x2, y2);
}

void DrawFillPoligon(Layer& id, int color, int x1, int y1, int x2, int y2, int x3, int y3) 
{ 
	DrawLine(id, color, x1, y1, x2, y2);
	DrawLine(id, color, x1, y1, x3, y3);
	DrawLine(id, color, x3, y3, x2, y2);
	ColorFill(id,color,(x1+x2+x3)/3,(y1+y2+y3)/3);
}