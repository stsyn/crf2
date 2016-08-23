#ifndef ZOOM_H_INCLUDED
#define ZOOM_H_INCLUDED
	#include "../../Core.h"

	void ZoomRender(Layer& id, Layer& tid, int tx, int ty, int x1, int y1, int cx, int cy, int x2, int y2, int mode);
	extern inline void ZoomRender(Layer& id, Layer& tid, int tx, int ty, int x1, int y1, int cx, int cy, int x2, int y2);
	extern inline void ZoomRender(Layer& id, Layer& tid, int cx, int cy, int x2, int y2);

#endif