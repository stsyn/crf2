#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Platform.h"

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
const int texmax=26;
int **cnv[512], cnvd[512][2];
int xmax=320, ymax=200;

char tex_list[texmax][64];
char tex_path[64];
char tex_mpath[64];

/******************************
 ***********SYS LEVEL**********
 ******************************/	
int gener(int max)
{
	return max?(rand()%max):0; 
}

void reset(int id)
{
	for (int i=0; i<cnvd[id][0]; i++)
		for (int j=0; j<cnvd[id][1]; j++)
			cnv[id][i][j]=0;
}

void delLayer(int id)
{
	if (cnvd[id][0] == 0) return;
    for(int i = 0; i < cnvd[id][0]; i++)
        delete[] cnv[id][i];
    delete[] cnv[id];
	cnvd[id][0] = 0;
	cnvd[id][1] = 0;
}

void buildLayer(int id,const int x,const int y)
{
	if (cnvd[id][0] != 0) delLayer(id);
    cnv[id] = new int*[x];
    for(int i = 0; i < x; ++i)
        cnv[id][i] = new int[y];
	cnvd[id][0] = x;
	cnvd[id][1] = y;
	reset(id);
}

void destroy()
{
	for (int i=0; i<512; i++) delLayer(i);
}

int getWidth(int id)
{
	return cnvd[id][0];
}

int getHeight(int id)
{
	return cnvd[id][1];
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
unsigned int tA(unsigned int color, unsigned int a)
{
	unsigned int tcolor = color & 0x00ffffff;
	return (a << 24) | tcolor;
}
unsigned int tA(unsigned int color, int a)
{
	unsigned int tcolor = color & 0x00ffffff;
	return (a << 24) | tcolor;
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
	
unsigned int getColor(int id, int x, int y)
{
	if (cnvd[id][0] != 0 && cnvd[id][0] > x && x >= 0 && cnvd[id][1] > y && y >= 0) return cnv[id][x][y];
	else return 0;
}


void l_init()
{
	sprintf(tex_mpath,"DATA/TEXT/");
	sprintf(tex_path,"DATA/TEXT/textures.dat");
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

void renderer(int id)
{
	for (int i=0; i<xmax; i++)
		for (int j=0; j<ymax; j++)
		{
			ocnv[(ymax-j-1)*xmax+i] = cnv[id][i][j];
		}
	glRasterPos2d(0,rymax-((rymax%240==0)?1:0)); //very black magic
	glPixelZoom((float)rxmax/xmax,(float)rymax/ymax);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glDrawPixels(xmax, ymax, GL_RGBA, GL_UNSIGNED_BYTE, ocnv);
	SwapBuffers();	
}

bool tex_read(char *tl, int target)
{
	unsigned short int chr[9], w, h, bit;
	unsigned char b[4];

	FILE *tex_file;
	tex_file = fopen(tl, "rb" ); 
	fread(&chr, 1, 18, tex_file);
	
	delLayer(target);
	w = chr[6];
	h = chr[5];
	bit = (chr[8] % 256) / 8;
	if (cnvd[target][0]!=0)
		delLayer(target);
	buildLayer(target,w,h);
	
	for (int j = 0; j<h; j++)
		for (int i = 0; i<w; i++)
		{
			fread(&b, 1, bit, tex_file);
			if (bit == 4) cnv[target][i][j] = ARGB(b[3], b[2], b[1], b[0]);
			else cnv[target][i][j] = tRGB(b[2], b[1], b[0]);
		}
	fclose(tex_file);
	return true;
}
bool tex_read(int fname, int target)
{
	char  tl[128];
	tl[0] = '\0';
	strcat(tl, tex_mpath);
	strcat(tl, tex_list[fname]);
	
	return tex_read(tl,target);
}
	
bool tex_read(int fname)
{
	return tex_read(fname, fname+16);
}
	
bool ctex_read(char *tl, int target)
{
	char  otl[128];
	otl[0] = '\0';
	strcat(otl, tex_mpath);
	strcat(otl, tl);
	return tex_read(otl,target);
}

void tex_init()
{
	FILE *tex_file;
	tex_file = fopen(tex_path, "r"); 
	for (int i=0; i<texmax; i++)
	{
		fscanf(tex_file, "%[^\r^\n]\n", tex_list[i]); // WTF,  why uppercase?
		for(char *p = (char*)&tex_list[i]; *p; ++p) *p = tolower(*p); // String to lowcase
		
		printf("tex_init: tex_list[%i]='%s'\n", i, tex_list[i]);
	}
	fclose(tex_file);
}


/******************************
 ***********LOW LEVEL**********
 ******************************/

void invert(int id, int x, int y)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	unsigned int da,dr,dg,db;

	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);

	dr = 255-dr;
	dg = 255-dg;
	db = 255-db;

	cnv[id][x][y]= ARGB(da,dr,dg,db);
}
	
void add(int id, int x,int y,int r,int g,int b)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	unsigned int dr,dg,db,da;
	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr+=r;
	if (dr>255) dr=255;
	dg+=g;
	if (dg>255) dg=255;
	db+=b;
	if (db>255) db=255;
	
	cnv[id][x][y]= ARGB(da,dr,dg,db);
}
	
void add(int id, int x,int y,int a,int r,int g,int b)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	unsigned int dr,dg,db,da;
	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr=dr + ((r * a) >> 8);
	if (dr>255) dr=255;
	dg=dg + ((g * a) >> 8);
	if (dg>255) dg=255;
	db=db + ((b * a) >> 8);
	if (db>255) db=255;
	
	cnv[id][x][y]= ARGB(da,dr,dg,db);
}

void rem(int id, int x,int y,int r,int g,int b)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	int dr,dg,db,da;
	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr-=r;
	if (dr<0) dr=0;
	dg-=g;
	if (dg<0) dg=0;
	db-=b;
	if (db<0) db=0;
	
	cnv[id][x][y]= ARGB(da,dr,dg,db);
}
	
void rem(int id, int x,int y,int a,int r,int g,int b)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	int dr,dg,db,da;
	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr=dr - ((r * a) >> 8);
	if (dr<0) dr=0;
	dg=dg - ((g * a) >> 8);
	if (dg<0) dg=0;
	db=db - ((b * a) >> 8);
	if (db<0) db=0;
	
	cnv[id][x][y]= ARGB(da,dr,dg,db);
}

void rema(int id, int x,int y,int a)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	int dr,dg,db,da;
	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	da-=a;
	if (da<0) da=0;
	
	cnv[id][x][y]= ARGB(da,dr,dg,db);
}
	
void mult(int id, int x,int y,int r,int g,int b)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	unsigned int dr,dg,db,da;
	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	dr=(( dr * r) >> 8) & 255;
	dg=(( dg * g) >> 8) & 255;
	db=(( db * b) >> 8) & 255;
	
	cnv[id][x][y]= ARGB(da,dr,dg,db);
}
	

void multa(int id, int x,int y,int a)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	unsigned int dr,dg,db,da;
	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	da=(( da * a) >> 8) & 255;
	
	cnv[id][x][y]= ARGB(da,dr,dg,db);
}
void mult(int id, int x,int y,int a,int r,int g,int b)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;

	unsigned int dr=255 - (((255 - r) * a) >> 8);
	unsigned int dg=255 - (((255 - g) * a) >> 8);
	unsigned int db=255 - (((255 - b) * a) >> 8);
	mult(id,x,y,dr,dg,db);
}
	
void screening(int id, int x,int y,int r,int g,int b)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	int dr,dg,db,da;
	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);
	if (da==0) return;
	
	if (dr<r) dr=r;
	if (dg<g) dg=g;
	if (db<b) db=b;
	
	cnv[id][x][y]= ARGB(da,dr,dg,db);
}


void plot(int id, int x,int y,int r,int g,int b)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	cnv[id][x][y]= tRGB(r,g,b);
}

void plot(int id, int x,int y,unsigned int color)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	cnv[id][x][y]= color;
}

void Aplot(int id, int x,int y,unsigned int color)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	cnv[id][x][y]= (color & 0x00FFFFFF) | (At(getColor(id,x,y)) << 24);
}
	
void plot(int id,int x,int y, int a, int r,int g,int b)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	unsigned int dr,dg,db,da;
	ARGBt(cnv[id][x][y],&da,&dr,&dg,&db);
	
	dr=( (dr * (255 - a) ) + (r * a)) >> 8;
	dg=( (dg * (255 - a) ) + (g * a)) >> 8;
	db=( (db * (255 - a) ) + (b * a)) >> 8;
	da+=a;
	if (da>255) da=255;
	
	cnv[id][x][y]= ARGB(da,dr,dg,db);
}
	
void transparency(int id,int x,int y, int a)
{
	if (x>=cnvd[id][0] || x<0 || y>=cnvd[id][1] || y<0) return;
	
	unsigned int dr,dg,db;
	RGBt(cnv[id][x][y],&dr,&dg,&db);
	cnv[id][x][y]= ARGB(a,dr,dg,db);
}
	
	
void grayer(int id, int tid, int x,int y,int x1,int y1,int a)
{
	if (x1>=cnvd[id][0] || x<0 || y1>=cnvd[id][1] || y<0) return;
	
	int ddg,ddb,ddr, dr,dg,db,da,de;
	ARGBt(cnv[id][x1][y1],&da,&dr,&dg,&db);
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
	
	cnv[tid][x][y]= ARGB(da,dr,dg,db);
	
}
