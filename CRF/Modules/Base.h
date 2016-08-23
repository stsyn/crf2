#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

	#include "../Layer.h"
	void DrawVLine(Layer& id, unsigned int color, int x1, int y1, int k);
	inline void FDrawVLine(Layer& id, unsigned int color, int x1, int y1, int k);
	void DrawHLine(Layer& id, unsigned int color, int x1, int y1, int k);
	inline void FDrawHLine(Layer& id, unsigned int color, int x1, int y1, int k);
	void DrawFrame(Layer& id, unsigned int color, int x, int y, int xk, int yk);
	inline void FDrawRect(Layer& id, unsigned int color, int x1, int y1, int xk, int yk);
	void DrawRect(Layer& id, unsigned int color, int x1, int y1, int xk, int yk);
	void DrawRect(Layer& id, unsigned int color, int x1, int y1, int xk, int yk, int mode);
	void DoGray(Layer& id, Layer& tid, unsigned int value, int x1, int y1);
	void VGradient(Layer& id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode);
	void HGradient(Layer& id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode);
	void IncludeLayer(Layer& id, Layer& tid, int x1, int y1, int mode);
	inline void IncludeLayer(Layer& id, Layer& tid, int x1, int y1);
	void FragmentLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode);
	inline void FragmentLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk);
	inline void cloneLayer(Layer& id,Layer& tid);
	void ColorFill (Layer& id, unsigned int msc, int x, int y);
	void StackedRender(int count, int first,...);

#endif