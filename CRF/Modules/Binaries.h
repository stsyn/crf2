#ifndef BINAR_MAIN_H_INCLUDED
#define BINAR_MAIN_H_INCLUDED
	#include "../Layer.h"

	void CalcBorder(Layer& id);
	void FindTransparencyBorder(Layer& id, Layer& resid,unsigned int msc, int overdrive);
	void Overlay(Layer& id, unsigned int color);
	void Smooth(Layer& id, int v,unsigned int msc);
	void Fill (Layer& id, unsigned int msc, int x, int y);
	void SetBorders(Layer& id, int x, int y, int x2, int y2);
	void SetBordersBySize(Layer& id, int x, int y, int xk, int yk);
	int BordersSize(Layer& id);
	void LinearTransparencyBorder(Layer& id,Layer& resid, unsigned int msc, int l_x, int l_y, int length);
	void FixBorder(Layer& id, int msc);
	void RadialShine(Layer& id, unsigned int msc, int x, int y, int r, int action);
	void CircularShine(Layer& id, unsigned int msc, int x, int y, int r, int ar, int action);

	void ANDNOT(Layer& id, Layer& op, Layer& result);
	void AND(Layer& id, Layer& op, Layer& result);
	void NOT(Layer& id, Layer& result);

#endif