#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include "Layer.h"

	extern int xmax, ymax;

	void buildLayer(Layer& id,const int x,const int y);
	void delLayer(Layer& id);
	void destroy();
	void invert(Layer& id, int x, int y);
	void add(Layer& id, int x,int y,int r,int g,int b);
	void add(Layer& id, int x,int y,int a,int r,int g,int b);
	void adda(Layer& id, int x,int y,int a);
	void rem(Layer& id, int x,int y,int r,int g,int b);
	void rem(Layer& id, int x,int y,int a,int r,int g,int b);
	void rema(Layer& id, int x,int y,int a);
	void mult(Layer& id, int x,int y,int r,int g,int b);
	void mult(Layer& id, int x,int y,int a,int r,int g,int b);
	void multa(Layer& id, int x,int y,int a);
	void screening(Layer& id, int x,int y,int r,int g,int b);
	void plot(Layer& id, int x,int y, int a, int r,int g,int b);
	void grayer(Layer& id, int x,int y,int a);
	void swap(Layer& id, int x, int y, int ch1, int ch2);
	void renderer(Layer& id);
	bool tex_read(char *tl, Layer& target);

inline unsigned int ARGB(unsigned int a,unsigned int r,unsigned int g,unsigned int b)
{
	return (a << 24) | (b << 16) | (g << 8) | r;
}

inline unsigned int tRGB(unsigned int r,unsigned int g,unsigned int b)
{
	return (0xFF << 24) | (b << 16) | (g << 8) | r;
}

inline unsigned int At(unsigned int color)
{
	return ((color >> 24) & 255);
}

inline unsigned int tA(unsigned int a)
{
	return (a << 24);
}

inline unsigned int tA(int a)
{
	return (a << 24);
}

inline void RGBt(unsigned int color, unsigned int *r,unsigned int *g,unsigned int *b)
{
	*b=((color >> 16) & 255);
	*g=((color >> 8) & 255);
	*r=(color & 255);
}

inline void ARGBt(unsigned int color, unsigned int *a, unsigned int *r,unsigned int *g,unsigned int *b)
{
	*a=((color >> 24) & 255);
	*b=((color >> 16) & 255);
	*g=((color >> 8) & 255);
	*r=(color & 255);
}

inline void RGBt(unsigned int color, int *r, int *g, int *b)
{
	*b=((color >> 16) & 255);
	*g=((color >> 8) & 255);
	*r=(color & 255);
}

inline void ARGBt(unsigned int color, int *a, int *r, int *g, int *b)
{
	*a=((color >> 24) & 255);
	*b=((color >> 16) & 255);
	*g=((color >> 8) & 255);
	*r=(color & 255);
}
	
inline unsigned int getColor(Layer& id, int x, int y)
{
	if (id.cnvd[0] != 0 && id.cnvd[0] > x && x >= 0 && id.cnvd[1] > y && y >= 0) return id.cnv[x][y];
	else return 0;
}

inline int getWidth(Layer& id)
{
	return id.cnvd[0];
}

inline int getHeight(Layer& id)
{
	return id.cnvd[1];
}

inline void reset(Layer& id)
{
	for (int i=0; i<id.cnvd[0]; i++)
		for (int j=0; j<id.cnvd[1]; j++)
			id.cnv[i][j]=0;
}

inline void plot(Layer& id, int x,int y,int r,int g,int b)
{
	id.cnv[x][y]= tRGB(r,g,b);
}

inline void plot(Layer& id, int x,int y,unsigned int color)
{
	if (x>=id.cnvd[0] || x<0 || y>=id.cnvd[1] || y<0) return;
	id.cnv[x][y]= color;
}	
	
inline void transparency(Layer& id,int x,int y, int a)
{
	if (x>=id.cnvd[0] || x<0 || y>=id.cnvd[1] || y<0) return;
	id.cnv[x][y]= id.cnv[x][y] & 0x00FFFFFF;
	id.cnv[x][y]= id.cnv[x][y] | (a << 24);
}
	
inline void MSDraw(Layer& id, int x, int y, int a, int r, int g, int b, int mode)
{
	if (mode == 0) plot(id,x,y,a,r,g,b);
	else if (mode == 1) add(id,x,y,a,r,g,b);
	else if (mode == 2) mult(id,x,y,a,r,g,b);
	else if (mode == 3) transparency(id,x,y,a);
	else if (mode == 4) invert(id,x,y);
	else if (mode == 5) rem(id,x,y,a,r,g,b);
	else if (mode == 6) multa(id,x,y,a);
	else if (mode == 7) rema(id,x,y,a);
	else if (mode == 8) swap(id,x,y,r,g);
	else if (mode == 9) grayer(id,x,y,a);
	else if (mode == 10) screening(id,x,y,r,g,b);
	else if (mode == 11) adda(id,x,y,a);
}

inline void MSDrawZA(Layer& id, int x, int y, int r, int g, int b, int mode)
{
	if (mode == 3) id.cnv[x][y] = id.cnv[x][y] & 0x00FFFFFF;
	else if (mode == 4) invert(id,x,y);
	else if (mode == 6) id.cnv[x][y] = id.cnv[x][y] & 0x00FFFFFF;
	else if (mode == 8) swap(id,x,y,r,g);
	else if (mode == 9) grayer(id,x,y,0);
}

inline void MSDrawFA(Layer& id, int x, int y, int r, int g, int b, int mode)
{
	if (mode == 0) plot(id,x,y,r,g,b);
	else if (mode == 1) add(id,x,y,r,g,b);
	else if (mode == 2) mult(id,x,y,r,g,b);
	else if (mode == 3) id.cnv[x][y] = id.cnv[x][y] | 0xFF000000;
	else if (mode == 4) invert(id,x,y);
	else if (mode == 5) rem(id,x,y,r,g,b);
	else if (mode == 7) id.cnv[x][y] = id.cnv[x][y] & 0x00FFFFFF;
	else if (mode == 8) swap(id,x,y,r,g);
	else if (mode == 9) grayer(id,x,y,255);
	else if (mode == 10) screening(id,x,y,r,g,b);
	else if (mode == 11) id.cnv[x][y] = id.cnv[x][y] | 0xFF000000;
}

inline void MSDrawC(Layer& id, int x, int y, int a, int r, int g, int b, int mode)
{
	if (x>=id.cnvd[0] || x<0 || y>=id.cnvd[1] || y<0) return;
	if (a == 255) MSDrawFA(id,x,y,r,g,b,mode);
	else if (a == 0) MSDrawZA(id,x,y,r,g,b,mode);
	else MSDraw(id,x,y,a,r,g,b,mode);
}

	void l_init(char *tx);
	void l_close();
	void l_resize(int xs, int ys);

#define RENDER_BASE			0
#define RENDER_ADD			1
#define RENDER_MULT			2
#define RENDER_ALPHA		3
#define RENDER_INVERT		4
#define RENDER_REM			5
#define RENDER_MULT_ALPHA	6
#define RENDER_REM_ALPHA	7
#define RENDER_SWAP			8
#define RENDER_GRAYSCALE	9
#define RENDER_SCREENING	10
#define RENDER_ADD_ALPHA	11

	
#endif //LIB_H_INCLUDED
