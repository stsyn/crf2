#ifndef ZOOM_H_INCLUDED
#define ZOOM_H_INCLUDED
	#include "../../Core.h"

	void ZoomRender(Layer& id, Layer& tid, int tx, int ty, int x1, int y1, int cx, int cy, int x2, int y2, int mode);

inline void ZoomRender(Layer& id, Layer& tid, int tx, int ty, int x1, int y1, int cx, int cy, int x2, int y2)
{
	ZoomRender(id,tid,tx,ty,x2,y2,cx,cy,x2,y2,0);
}

inline void ZoomRender(Layer& id, Layer& tid, int tx, int ty, int x1, int y1)
{
	ZoomRender(id,tid,tx,ty,x1,y1,0,0,getWidth(id),getHeight(id),0);
}
#endif