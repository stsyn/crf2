#include "../../Core.h"

void MaskedLayer(int id, int tid, int tx, int ty, int ColorR, int ColorG, int ColorB)
{
	unsigned int colors[4][4];
	RGBt(ColorR,&colors[1][1],&colors[1][2],&colors[1][3]);
	RGBt(ColorG,&colors[2][1],&colors[2][2],&colors[2][3]);
	RGBt(ColorB,&colors[3][1],&colors[3][2],&colors[3][3]);

	int i,j,k;
	for (i = 0; i<getWidth(id); i++)
		for (j = 0; j<getHeight(id); j++)
		{	
			ARGBt(getColor(id,i,j),&colors[0][0],&colors[0][1],&colors[0][2],&colors[0][3]);
			if (colors[0][0] == 0) continue;
			plot(tid,tx+i,ty+j,colors[0][0],0,0,0); //Creating Darkness
			for (k=1; k<4; k++)
			{
				add(tid,tx+i,ty+j,colors[0][k],colors[k][1],colors[k][2],colors[k][3]); 
			}
		}

}
