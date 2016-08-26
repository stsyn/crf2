#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

	#include "../Layer.h"
	#include "../Core.h"
	void DrawVLine(Layer& id, unsigned int color, int x1, int y1, int k);
	void DrawHLine(Layer& id, unsigned int color, int x1, int y1, int k);
	void DrawFrame(Layer& id, unsigned int color, int x, int y, int xk, int yk);
	void DrawRect(Layer& id, unsigned int color, int x1, int y1, int xk, int yk, int mode);
	void DoGray(Layer& id, Layer& tid, unsigned int value, int x1, int y1);
	void VGradient(Layer& id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode);
	void HGradient(Layer& id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode);
	void FragmentLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode);
	void ColorFill (Layer& id, unsigned int msc, int x, int y);
	void StackedRender(int count,...);


inline void FDrawVLine(Layer& id, unsigned int color, int x1, int y1, int k)
{
	int i;
	for (i = 0; i<k; i++)
			plot(id,x1,y1+i,color);
	for (i = 0; i>=k; i--)
			plot(id,x1,y1+i,color);
}

inline void FDrawHLine(Layer& id, unsigned int color, int x1, int y1, int k)
{
	int i;
	for (i = 0; i<k; i++)
			plot(id,x1+i,y1,color);
	for (i = 0; i>=k; i--)
			plot(id,x1+i,y1,color);
}

inline void DrawRect(Layer& id, unsigned int color, int x1, int y1, int xk, int yk)
{
	DrawRect(id,color,x1,y1,xk,yk,0);
}

inline void FDrawRect(Layer& id, unsigned int color, int x1, int y1, int xk, int yk)
{
	int i,j;
	for (i = 0; i<xk; i++)
		for (j = 0; j<yk; j++)
			plot(id,x1+i,y1+j,color);
}

inline void FragmentLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk)
{
	FragmentLayer(id,tid,tx,ty,x2,y2,xk,yk,id.mode);
}
	
inline void IncludeLayer(Layer& id, Layer& tid, int x1, int y1, int mode)
{
	int l,t,r,d;
	borderCheck(id,&l,&t,&r,&d);
	FragmentLayer(id,tid,x1+l,y1+t,l,t,r-l+1,d-t+1,mode);
}

inline void IncludeLayer(Layer& id, Layer& tid, int x1, int y1)
{
	int l,t,r,d;
	borderCheck(id,&l,&t,&r,&d);
	FragmentLayer(id,tid,x1+l,y1+t,l,t,r-l+1,d-t+1,id.mode);
}

inline void cloneLayer(Layer& id,Layer& tid)
{
	buildLayer(tid,getWidth(id),getHeight(id));
	IncludeLayer(id,tid,0,0);	
}
#endif