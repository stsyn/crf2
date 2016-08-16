#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

	extern int xmax, ymax;

	void buildLayer(int id,const int x,const int y);
	void delLayer(int id);
	void destroy();
	unsigned int ARGB(unsigned int a,unsigned int r,unsigned int g,unsigned int b);
	unsigned int tRGB(unsigned int r,unsigned int g,unsigned int b);
	unsigned int getColor(int id, int x, int y);
	void RGBt(unsigned int color, unsigned int *r,unsigned int *g,unsigned int *b);
	void ARGBt(unsigned int color, unsigned int *a, unsigned int *r,unsigned int *g,unsigned int *b);
	void RGBt(unsigned int color, int *r, int *g, int *b);
	void ARGBt(unsigned int color, int *a, int *r, int *g, int *b);
	unsigned int At(unsigned int color);
	unsigned int tA(unsigned int color, unsigned int a);
	unsigned int tA(unsigned int color, int a);
	int getHeight(int id);
	int getWidth(int id);
	void reset(int id);
	void invert(int id, int x, int y);
	void add(int id, int x,int y,int r,int g,int b);
	void add(int id, int x,int y,int a,int r,int g,int b);
	void rem(int id, int x,int y,int r,int g,int b);
	void rem(int id, int x,int y,int a,int r,int g,int b);
	void rema(int id, int x,int y,int a);
	void mult(int id, int x,int y,int r,int g,int b);
	void mult(int id, int x,int y,int a,int r,int g,int b);
	void multa(int id, int x,int y,int a);
	void screening(int id, int x,int y,int r,int g,int b);
	void plot(int id, int x,int y,unsigned int color);
	void Aplot(int id, int x,int y,unsigned int color);
	void plot(int id, int x,int y,int r,int g,int b);
	void plot(int id, int x,int y, int a, int r,int g,int b);
	void transparency(int id,int x,int y, int a);
	void grayer(int id, int tid, int x,int y,int x1,int y1,int a);
	int gener(int max);
	void renderer(int id);
	bool tex_read(int fname);
	bool tex_read(int fname, int target);
	bool tex_read(char *tl, int target);
	bool ctex_read(char *tl, int target);
	bool fnt_read(int fname);
	void tex_init();
	void font_init();

	void l_init();
	void l_close();
	void l_resize(int xs, int ys);
	
#endif //LIB_H_INCLUDED
