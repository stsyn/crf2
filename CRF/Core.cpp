#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Platform.h"
#include "Layer.h"

#ifdef WIN32
	#include <windows.h>
	#include <GL\gl.h>
	#include <GL\glu.h>
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else //UNIX
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

int	*ocnv;
int xmax=320, ymax=200;
Layer *_cnv[CRF_MAX_LAYERS];
char tex_path[64];

/******************************
 ***********SYS LEVEL**********
 ******************************/	

void reset(Layer& id)
{
	for (int i=0; i<id.cnvd[0]; i++)
		for (int j=0; j<id.cnvd[1]; j++)
			id.cnv[i][j]=0;
}

void delLayer(Layer& id)
{
	if (id.cnvd[0] == 0) return;
    for(int i = 0; i < id.cnvd[0]; i++)
        delete[] id.cnv[i];
    delete[] id.cnv;
	id.cnvd[0] = 0;
	id.cnvd[1] = 0;
}

void buildLayer(Layer& id,const int x,const int y)
{
	if (id.cnvd[0] != 0) delLayer(id);
    id.cnv = new int*[x];
    for(int i = 0; i < x; ++i)
        id.cnv[i] = new int[y];
	id.cnvd[0] = x;
	id.cnvd[1] = y;
	
	id.lcnv[0]=0;
	id.lcnv[1]=0;
	id.lcnv[2]=x-1;
	id.lcnv[3]=y-1;
	reset(id);
}

void destroy()
{
	for (int i=0; i<CRF_MAX_LAYERS; i++) delLayer(*_cnv[i]);
}

int getWidth(Layer& id)
{
	return id.cnvd[0];
}

int getHeight(Layer& id)
{
	return id.cnvd[1];
}

unsigned int ARGB(unsigned int a,unsigned int r,unsigned int g,unsigned int b)
{
	return (a << 24) | (b << 16) | (g << 8) | r;
}

unsigned int tRGB(unsigned int r,unsigned int g,unsigned int b)
{
	return (0xFF << 24) | (b << 16) | (g << 8) | r;
}
unsigned int At(unsigned int color)
{
	return ((color >> 24) & 255);
}
unsigned int tA(unsigned int a)
{
	return (a << 24);
}
unsigned int tA(int a)
{
	return (a << 24);
}
void RGBt(unsigned int color, unsigned int *r,unsigned int *g,unsigned int *b)
{
	*b=((color >> 16) & 255);
	*g=((color >> 8) & 255);
	*r=(color & 255);
}

void ARGBt(unsigned int color, unsigned int *a, unsigned int *r,unsigned int *g,unsigned int *b)
{
	*a=((color >> 24) & 255);
	*b=((color >> 16) & 255);
	*g=((color >> 8) & 255);
	*r=(color & 255);
}
void RGBt(unsigned int color, int *r, int *g, int *b)
{
	*b=((color >> 16) & 255);
	*g=((color >> 8) & 255);
	*r=(color & 255);
}

void ARGBt(unsigned int color, int *a, int *r, int *g, int *b)
{
	*a=((color >> 24) & 255);
	*b=((color >> 16) & 255);
	*g=((color >> 8) & 255);
	*r=(color & 255);
}
	
unsigned int getColor(Layer& id, int x, int y)
{
	if (id.cnvd[0] != 0 && id.cnvd[0] > x && x >= 0 && id.cnvd[1] > y && y >= 0) return id.cnv[x][y];
	else return 0;
}


void l_init(char *tx)
{
	sprintf(tex_path, tx);
	ocnv = new int[ymax*xmax];
}

void l_resize(int xs, int ys)
{
    delete[] ocnv;
	xmax = xs;
	ymax = ys;
	ocnv = new int[ymax*xmax];
}

void l_close()
{
    delete[] ocnv;
}

void renderer(Layer& id)
{
	for (int i=0; i<xmax; i++)
		for (int j=0; j<ymax; j++)
		{
			ocnv[(ymax-j-1)*xmax+i] = id.cnv[i][j];
		}
	glRasterPos2d(0,rymax-((rymax%240==0)?1:0)); //very black magic
	glPixelZoom((float)rxmax/xmax,(float)rymax/ymax);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glDrawPixels(xmax, ymax, GL_RGBA, GL_UNSIGNED_BYTE, ocnv);
	SwapBuffers();	
}

bool tex_read(char *tl, Layer& target)
{
	unsigned short int chr[9], w, h, bit;
	unsigned char b[4];
	char fname[128];

	FILE *tex_file;
	sprintf(fname,"%s%s",tex_path,tl);
	tex_file = fopen(fname, "rb" ); 
	fread(&chr, 1, 18, tex_file);
	
	delLayer(target);
	w = chr[6];
	h = chr[5];
	bit = (chr[8] % 256) / 8;
	if (target.cnvd[0]!=0)
		delLayer(target);
	buildLayer(target,w,h);
	
	for (int j = 0; j<h; j++)
		for (int i = 0; i<w; i++)
		{
			fread(&b, 1, bit, tex_file);
			if (bit == 4) target.cnv[i][j] = ARGB(b[3], b[2], b[1], b[0]);
			else target.cnv[i][j] = tRGB(b[2], b[1], b[0]);
		}
	fclose(tex_file);
	return true;
}


/******************************
 ***********LOW LEVEL**********
 ******************************/

void invert(Layer& id, int x, int y)
{
	unsigned int da,dr,dg,db;

	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);

	dr = 255-dr;
	dg = 255-dg;
	db = 255-db;

	id.cnv[x][y]= ARGB(da,dr,dg,db);
}
	
void add(Layer& id, int x,int y,int r,int g,int b)
{
	unsigned int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr+=r;
	if (dr>255) dr=255;
	dg+=g;
	if (dg>255) dg=255;
	db+=b;
	if (db>255) db=255;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}
	
void add(Layer& id, int x,int y,int a,int r,int g,int b)
{
	unsigned int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr=dr + ((r * a) >> 8);
	if (dr>255) dr=255;
	dg=dg + ((g * a) >> 8);
	if (dg>255) dg=255;
	db=db + ((b * a) >> 8);
	if (db>255) db=255;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}

void adda(Layer& id, int x,int y,int a)
{
	unsigned int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);

	da+=a;
	if (da>255) da=255;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}

void rem(Layer& id, int x,int y,int r,int g,int b)
{
	int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr-=r;
	if (dr<0) dr=0;
	dg-=g;
	if (dg<0) dg=0;
	db-=b;
	if (db<0) db=0;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}
	
void rem(Layer& id, int x,int y,int a,int r,int g,int b)
{
	int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr=dr - ((r * a) >> 8);
	if (dr<0) dr=0;
	dg=dg - ((g * a) >> 8);
	if (dg<0) dg=0;
	db=db - ((b * a) >> 8);
	if (db<0) db=0;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}

void rema(Layer& id, int x,int y,int a)
{
	int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	da-=a;
	if (da<0) da=0;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}
	
void mult(Layer& id, int x,int y,int r,int g,int b)
{
	unsigned int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr=(( dr * r) >> 8) & 255;
	dg=(( dg * g) >> 8) & 255;
	db=(( db * b) >> 8) & 255;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}
	

void multa(Layer& id, int x,int y,int a)
{
	unsigned int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	da=(( da * a) >> 8) & 255;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}
void mult(Layer& id, int x,int y,int a,int r,int g,int b)
{
	unsigned int dr=255 - (((255 - r) * a) >> 8);
	unsigned int dg=255 - (((255 - g) * a) >> 8);
	unsigned int db=255 - (((255 - b) * a) >> 8);
	mult(id,x,y,dr,dg,db);
}
	
void screening(Layer& id, int x,int y,int r,int g,int b)
{
	int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	if (dr<r) dr=r;
	if (dg<g) dg=g;
	if (db<b) db=b;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}


void plot(Layer& id, int x,int y,int r,int g,int b)
{
	id.cnv[x][y]= tRGB(r,g,b);
}

void plot(Layer& id, int x,int y,unsigned int color)
{
	if (x>=id.cnvd[0] || x<0 || y>=id.cnvd[1] || y<0) return;
	id.cnv[x][y]= color;
}
	
void plot(Layer& id,int x,int y, int a, int r,int g,int b)
{
	unsigned int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	
	dr=( (dr * (255 - a) ) + (r * a)) >> 8;
	dg=( (dg * (255 - a) ) + (g * a)) >> 8;
	db=( (db * (255 - a) ) + (b * a)) >> 8;
	da+=a;
	if (da>255) da=255;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
}
	
void transparency(Layer& id,int x,int y, int a)
{
	if (x>=id.cnvd[0] || x<0 || y>=id.cnvd[1] || y<0) return;
	id.cnv[x][y]= id.cnv[x][y] & 0x00FFFFFF;
	id.cnv[x][y]= id.cnv[x][y] | (a << 24);
}
	
	
void grayer(Layer& id, int x,int y,int a)
{	
	int ddg,ddb,ddr, dr,dg,db,da,de;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	de = (dg+dr+db)/3;
	ddb = db-de;
	ddg = dg-de;
	ddr = dr-de;
	dr = (dr*127-(ddr*(a-127)))/127;
	db = (db*127-(ddb*(a-127)))/127;
	dg = (dg*127-(ddg*(a-127)))/127;
	
	if (dr>255) dr=255;
	if (dg>255) dg=255;
	if (db>255) db=255;
	
	if (dr<0) dr=0;
	if (dg<0) dg=0;
	if (db<0) db=0;
	
	id.cnv[x][y]= ARGB(da,dr,dg,db);
	
}

void swap(Layer& id, int x, int y, int ch1, int ch2)
{
	int t[4], oc;
	ARGBt(id.cnv[x][y],&t[0],&t[1],&t[2],&t[3]);
	oc = t[ch2]; t[ch2] = t[ch1]; t[ch1] = oc;
	ARGB(t[0],t[1],t[2],t[3]);
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

void MSDrawC(Layer& id, int x, int y, int a, int r, int g, int b, int mode)
{
	if (x>=id.cnvd[0] || x<0 || y>=id.cnvd[1] || y<0) return;
	if (a == 255) MSDrawFA(id,x,y,r,g,b,mode);
	else if (a == 0) MSDrawZA(id,x,y,r,g,b,mode);
	else MSDraw(id,x,y,a,r,g,b,mode);
}