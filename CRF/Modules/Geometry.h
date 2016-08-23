#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED
	#include "../Layer.h"
	void DrawLine(Layer& id, unsigned int color, int x0, int y0, int x1, int y1);
	void DrawCircle(Layer& id, unsigned int color, int xc, int yc, int r);
	void DrawFillCircle(Layer& id, unsigned int color, int x, int y, int radius);
	void DrawPoligon(Layer& id, int color, int x1, int y1, int x2, int y2, int x3, int y3);
	void DrawFillPoligon(Layer& id, int color, int x1, int y1, int x2, int y2, int x3, int y3);

#endif
