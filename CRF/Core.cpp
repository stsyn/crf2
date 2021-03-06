#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Platform.h"
#include "Layer.h"
#include "Core.h"

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
	
void plot(Layer& id,int x,int y, int a, int r,int g,int b)
{
	unsigned int dr,dg,db,da;
	ARGBt(id.cnv[x][y],&da,&dr,&dg,&db);
	
	da=a+da;
	if (da>255) da=255;

	dr=( (dr * (255-a)) + (r * a)) /da;
	dg=( (dg * (255-a)) + (g * a)) /da;
	db=( (db * (255-a)) + (b * a)) /da;
	

	id.cnv[x][y]= ARGB(da,dr,dg,db);
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
