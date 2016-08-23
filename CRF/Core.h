#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include "Layer.h"

	extern int xmax, ymax;

	void buildLayer(Layer& id,const int x,const int y);
	void delLayer(Layer& id);
	void destroy();
	inline unsigned int ARGB(unsigned int a,unsigned int r,unsigned int g,unsigned int b);
	inline unsigned int tRGB(unsigned int r,unsigned int g,unsigned int b);
	inline unsigned int getColor(Layer& id, int x, int y);
	inline void RGBt(unsigned int color, unsigned int *r,unsigned int *g,unsigned int *b);
	inline void ARGBt(unsigned int color, unsigned int *a, unsigned int *r,unsigned int *g,unsigned int *b);
	inline void RGBt(unsigned int color, int *r, int *g, int *b);
	inline void ARGBt(unsigned int color, int *a, int *r, int *g, int *b);
	inline unsigned int At(unsigned int color);
	inline unsigned int tA(unsigned int color, unsigned int a);
	inline unsigned int tA(unsigned int color, int a);
	inline int getHeight(Layer& id);
	inline int getWidth(Layer& id);
	inline void reset(Layer& id);
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
	inline void plot(Layer& id, int x,int y,unsigned int color);
	inline void plot(Layer& id, int x,int y,int r,int g,int b);
	void plot(Layer& id, int x,int y, int a, int r,int g,int b);
	inline void transparency(Layer& id,int x,int y, int a);
	void grayer(Layer& id, int x,int y,int a);
	void swap(Layer& id, int x, int y, int ch1, int ch2);
	void renderer(Layer& id);
	bool tex_read(char *tl, Layer& target);
	inline void MSDrawC(Layer& id, int x, int y, int a, int r, int g, int b, int mode);

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
