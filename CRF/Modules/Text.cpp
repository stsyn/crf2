#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Core.h"
#include "Base.h"

const int fontmax=3;
int fontdata[fontmax][3];
char font_path[64];
char font_list[fontmax][64];

bool fnt_read(int fname)
{
	char  tl[128];
	tl[0] = '\0';
	strcat(tl, font_path);
	strcat(tl, font_list[fname]);
	
	return tex_read(tl, fname+1);
}

void font_init()
{
	sprintf(font_path,"DATA/TEXT/FONT/");
	FILE *tex_file;
	tex_file = fopen(font_path, "r");
	for (int i=0; i<fontmax; i++)
	{
		fscanf(tex_file, "%[^\r^\n]\n", font_list[i]);
		for(char *p = (char*)&font_list[i]; *p; ++p) *p = tolower(*p); 
		
		printf("font_init: font_list[%i]='%s'\n", i, font_list[i]);
		fnt_read(i);
	}
	fclose(tex_file);

	fontdata[0][0]=7;
	fontdata[1][0]=8;
	fontdata[2][0]=5;
	fontdata[0][1]=14;
	fontdata[1][1]=10;
	fontdata[2][1]=6;
	fontdata[0][2]=0;
	fontdata[1][2]=1;
	fontdata[2][2]=0;
}

void PrintText(int id, int fontn, char *str, int color, int x, int y)
{
	int a2,r2,g2,b2,tch,l,i,j,k;
	k = strlen(str);
	buildLayer(0,k*fontdata[fontn][0],fontdata[fontn][1]);
	reset(0);

	for (l=0; l<k; l++)
	{
		tch = str[l];
		for (i = 0; i<fontdata[fontn][0]; i++)
			for (j = 0; j<fontdata[fontn][1]; j++)
			{
				ARGBt(getColor(fontn+1,fontdata[fontn][0]*tch+i,j),&a2,&r2,&g2,&b2);
				if (a2 == 0) continue;
				if (a2 != 255) 
				{
					plot(0,i+fontdata[fontn][0]*l,j,a2,r2,g2,b2);
				}
				else
				{
					plot(0,i+fontdata[fontn][0]*l,j,getColor(fontn+1,fontdata[fontn][0]*tch+i,j));
				}
			}
	}
	DrawRect(0,color,0,0,getWidth(0),getHeight(0),2);
	IncludeLayer(0,id,x,y,0);
	delLayer(0);
}

int TextWidth(int fontn, char *str)
{
	int k = strlen(str);
	return k*fontdata[fontn][0];
}

int TextHeight(int fontn, char *str)
{
	return fontdata[fontn][1];
}

void PrintNum(int id, int fontn, int subj, int color, int x, int y, int k)
{
	int a2,r2,g2,b2,tch,l,i,j;
	char str[9];
	sprintf(str,"%09i",subj);
	for (i = 0; i<9; i++) if (str[i] == ' ') str[i] = '0';
	buildLayer(0,k*fontdata[fontn][0],fontdata[fontn][1]);
	reset(0);

	for (l=0; l<k; l++)
	{
		tch = str[l+9-k]-48;
		for (i = 0; i<fontdata[fontn][0]; i++)
			for (j = 0; j<fontdata[fontn][1]; j++)
			{
				ARGBt(getColor(fontn+1,fontdata[fontn][0]*tch+i,j),&a2,&r2,&g2,&b2);
				if (a2 == 0) continue;
				if (a2 != 255) 
				{
					plot(0,i+fontdata[fontn][0]*l,j,a2,r2,g2,b2);
				}
				else
				{
					plot(0,i+fontdata[fontn][0]*l,j,getColor(fontn+1,fontdata[fontn][0]*tch+i,j));
				}
			}
	}
	DrawRect(0,color,0,0,getWidth(0),getHeight(0),2);
	IncludeLayer(0,id,x,y,0);
	delLayer(0);
}