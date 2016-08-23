#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../Core.h"
#include "../Base.h"
#include "../../Layer.h"
#include "Font.h"

void Font::CreateMonospacedFont(char *fontname, int lettersize)
{
	tex_read(fontname, container);
	monospaced = true;
	letterspacing[0] = lettersize;
	height = getHeight(container);
}

void Font::CreateFont(char *fontname, int lettersize[256], bool add)
{
	tex_read(fontname, container);
	monospaced = false;
	for (int i=0; i<256; i++) letterspacing[i] = (add?letterspacing[i]:0)+lettersize[i];
	height = getHeight(container);
}

int TextWidth(Font& font, char *str)
{
	int k = strlen(str),l,ot=0;
	if (font.monospaced) return k*font.letterspacing[0];
	for (l=0; l<k; l++) ot+=(font.monospaced?font.letterspacing[0]:font.letterspacing[str[l]]-(str[l]>0?font.letterspacing[str[l]-1]:0));
	return ot;
}

int TextHeight(Font& font, char *str)
{
	return font.height;
}

void PrintText(Layer& id, Font& font, char *str, int color, int x, int y)
{
	Layer *ac = new Layer;
	int a2,r2,g2,b2,tch,l,i,j,k,sk=0;
	k = strlen(str);
	buildLayer(*ac,TextWidth(font,str),TextHeight(font,str));

	for (l=0; l<k; l++)
	{
		tch = str[l];
		for (i = 0; i<(font.monospaced?font.letterspacing[0]:font.letterspacing[tch]-(tch>0?font.letterspacing[tch-1]:0)); i++)
			for (j = 0; j<font.height; j++)
			{
				ARGBt(getColor(font.container,(font.monospaced?(font.letterspacing[0]*tch):(tch>0?font.letterspacing[tch-1]:0))+i,j),&a2,&r2,&g2,&b2);
				if (a2 == 0) continue;
				MSDrawC(*ac,i+sk,j,a2,r2,g2,b2,0);
			}
		sk+=(font.monospaced?font.letterspacing[0]:font.letterspacing[str[l]]-(str[l]>0?font.letterspacing[str[l]-1]:0));
	}
	DrawRect(*ac,color,0,0,getWidth(*ac),getHeight(*ac),2);
	DrawRect(*ac,color,0,0,getWidth(*ac),getHeight(*ac),6);
	IncludeLayer(*ac,id,x,y,0);
	delete ac;
}
