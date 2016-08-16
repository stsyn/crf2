#include "../../Core.h"
#include "../Base.h"

void FindTransparencyBorder(int id, int resid, unsigned int msc)
{
	if (getWidth(id) != getWidth(resid) && getHeight(id) != getHeight(resid)) buildLayer(resid,getWidth(id),getHeight(id));
	for (int i=0; i<getWidth(id); i++)
		for (int j=0; j<getHeight(id); j++)
		{
			if (At(getColor(id,i,j)) < 128)
			{
				if (i>0 && At(getColor(id,i-1,j))>127) 
				{
					transparency(resid,i,j,msc);
					continue;
				}
				if (j>0 && At(getColor(id,i,j-1))>127) 
				{
					transparency(resid,i,j,msc);
					continue;
				}
				if (i+1<getWidth(id) && At(getColor(id,i+1,j))>127) 
				{
					transparency(resid,i,j,msc);
					continue;
				}
				if (j+1<getHeight(id) && At(getColor(id,i,j+1))>127) transparency(resid,i,j,msc);
			}
		}
}

void Smooth(int id, int v,unsigned int msc)
{
	for (int i=v; i>1; i--)
	{
		int at = msc*i/v;
		int at2 = msc*(i-1)/v;
		for (int x=0; x<getWidth(id); x++)
			for (int y=0; y<getHeight(id); y++)
				if (At(getColor(id,x,y)) == at) 
				{
					if (x>0 && At(getColor(id,x-1,y))<at2)
						transparency(id,x-1,y,at2);
					if (y>0 && At(getColor(id,x,y-1))<at2)
						transparency(id,x,y-1,at2);
					if (x+1<getWidth(id) && At(getColor(id,x+1,y))<at2)
						transparency(id,x+1,y,at2);
					if (y+1<getHeight(id) && At(getColor(id,x,y+1))<at2)
						transparency(id,x,y+1,at2);
				}
	}
}

void Overlay (int id, int color)
{
	DrawRect(id,color,0,0,getWidth(id),getHeight(id),1);
}
