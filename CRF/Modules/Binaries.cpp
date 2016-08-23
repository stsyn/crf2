#include "../Core.h"
#include "Base.h"
#include "../Layer.h"
#include <math.h>

unsigned long int bin_dots=0;

void optimize(Layer& id)
{
	id.lcnv[0]=0;
	id.lcnv[1]=0;
	id.lcnv[2]=getWidth(id)-1;
	id.lcnv[3]=getHeight(id)-1;

	bool safe = false;
	int i, j;
	for (i=0;i<getWidth(id);i++) //left
	{
		for (j=0;j<getHeight(id);j++)
			if (At(getColor(id,i,j)) !=0) 
				goto ch_right;
		id.lcnv[0]++;
	}
ch_right:
	for (i=getWidth(id)-1;i>=0;i--) //right
	{
		for (j=0;j<getHeight(id);j++)
			if (At(getColor(id,i,j)) !=0) 
				goto ch_top;
		id.lcnv[2]--;
	}
ch_top:
	for (j=0;j<getHeight(id);j++) //top
	{
		for (i=id.lcnv[0];i<=id.lcnv[2];i++)
			if (At(getColor(id,i,j)) !=0) 
				goto ch_down;
		id.lcnv[1]++;
	}
ch_down:
	for (j=getHeight(id)-1;j>=0;j--) //down
	{
		for (i=id.lcnv[0];i<=id.lcnv[2];i++)
			if (At(getColor(id,i,j)) !=0) 
				return;
		id.lcnv[3]--;
	}
}

void SetBorders(Layer& id, int x, int y, int x2, int y2)
{
	id.lcnv[0]=x;
	id.lcnv[1]=y;
	id.lcnv[2]=x2;
	id.lcnv[3]=y2;
}

void SetBordersBySize(Layer& id, int x, int y, int xk, int yk)
{
	SetBorders(id,x,y,x+xk-1,y+yk-1);
}


int BordersSize(Layer& id)
{
	return abs(id.lcnv[2]-id.lcnv[0]+1)*(id.lcnv[3]-id.lcnv[1]+1);
}

void FindTransparencyBorder(Layer& id, Layer& resid, unsigned int msc, int overdrive)
{
	int l,r,t,d;
	if (overdrive)
	{
		l = 0; r = getWidth(id); t = 0; d = getHeight(id);
	}
	else
	{
		l = (resid.lcnv[0]<0?0:resid.lcnv[0]); r = (resid.lcnv[2]>=getWidth(id)?getWidth(id)-1:resid.lcnv[2]);
		t = (resid.lcnv[1]<0?0:resid.lcnv[1]); d = (resid.lcnv[3]>=getHeight(id)?getHeight(id)-1:resid.lcnv[3]);
	}
	for (int i=l; i<=r; i++)
		for (int j=t; j<=d; j++)
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
	if (overdrive) optimize(resid);
}

void FixBorder(Layer& id, int msc)
{
	int l,r,t,d;
	l = (id.lcnv[0]<0?0:id.lcnv[0]); r = (id.lcnv[2]>=getWidth(id)?getWidth(id)-1:id.lcnv[2]);
	t = (id.lcnv[1]<0?0:id.lcnv[1]); d = (id.lcnv[3]>=getHeight(id)?getHeight(id)-1:id.lcnv[3]);
	for (int i=l+1; i<r; i++)
		for (int j=t+1; j<d; j++)
		{
			if (At(getColor(id,i,j)) >127) continue;
			if (
				At(getColor(id,i-1,j))>0 && At(getColor(id,i,j-1))>0 && !(At(getColor(id,i-1,j-1))>0) ||//topleft
				At(getColor(id,i-1,j))>0 && At(getColor(id,i,j+1))>0 && !(At(getColor(id,i-1,j+1))>0) ||//topright
				At(getColor(id,i+1,j))>0 && At(getColor(id,i,j-1))>0 && !(At(getColor(id,i+1,j-1))>0) ||//downleft
				At(getColor(id,i+1,j))>0 && At(getColor(id,i,j+1))>0 && !(At(getColor(id,i+1,j+1))>0)   //downright
				) transparency(id,i,j,msc);
		}
}

void _LTBProc(Layer& id,Layer& resid,int l_x, int l_y, int i, int length, int msc, int x1, int y1)
{
	int x0,y0,o,pr_x,pr_y;
	bool marked;
		marked=false;
		x0 = l_x;
		y0 = l_y;
		o = length+1;
		int dx = abs(x1 - x0),
			sx = x0 < x1 ? 1 : -1;
		int dy = abs(y1 - y0),
			sy = y0 < y1 ? 1 : -1;
		int err = (dx > dy ? dx : -dy) / 2;
		while (true)
		{
			if (At(getColor(id,x0,y0))>0)
			{
				if (marked) 
				{
					if (pr_x!=x0 && pr_y!=y0) transparency(resid,x0,y0,0);
				}
				else marked = true;
			}
			if (marked && o>0)
			{
				transparency(resid,x0,y0,msc*o/length);
				pr_x=x0;
				pr_y=y0;
				o--;
			}
			else pr_x=-1;

			if (x0 == x1 && y0 == y1) break;
			int e2 = err;
			if (e2 > -dx) {
				err -= dy;
				x0 += sx;
			}
			if (e2 < dy) {
				err += dx;
				y0 += sy;
			}
        }
}

void LinearTransparencyBorder(Layer& id,Layer& resid, unsigned int msc, int l_x, int l_y, int length)
{
	int l,r,t,d,i;
	l = (id.lcnv[0]<0?0:id.lcnv[0]); r = (id.lcnv[2]>=getWidth(id)?getWidth(id)-1:id.lcnv[2]);
	t = (id.lcnv[1]<0?0:id.lcnv[1]); d = (id.lcnv[3]>=getHeight(id)?getHeight(id)-1:id.lcnv[3]);

	resid.lcnv[0] = l;
	resid.lcnv[1] = t;
	resid.lcnv[2] = r;
	resid.lcnv[3] = d;

	if (l_y>t) for (i=l; i<r; i++) _LTBProc(id,resid,l_x,l_y,i,length,msc,i,resid.lcnv[1]); //top
	if (l_y<d) for (i=l; i<r; i++) _LTBProc(id,resid,l_x,l_y,i,length,msc,i,resid.lcnv[3]); //bottom
	if (l_x>l) for (i=t; i<d; i++) _LTBProc(id,resid,l_x,l_y,i,length,msc,resid.lcnv[0],i); //left
	if (l_x<r) for (i=t; i<d; i++) _LTBProc(id,resid,l_x,l_y,i,length,msc,resid.lcnv[2],i); //right
}

void Smooth(Layer& id, int v,unsigned int msc)
{
	int l,r,t,d;
	l = (id.lcnv[0]<0?0:id.lcnv[0]); r = (id.lcnv[2]>=getWidth(id)?getWidth(id)-1:id.lcnv[2]);
	t = (id.lcnv[1]<0?0:id.lcnv[1]); d = (id.lcnv[3]>=getHeight(id)?getHeight(id)-1:id.lcnv[3]);
	v++;
	for (int i=v; i>1; i--)
	{
		int at = msc*i/v;
		int at2 = msc*(i-1)/v;
		for (int x=l; x<r; x++)
			for (int y=t; y<d; y++)
				if (At(getColor(id,x,y)) == at) 
				{
					if (x>0 && At(getColor(id,x-1,y))<at2)
					{
						transparency(id,x-1,y,at2);
						if (x == id.lcnv[0]) 
						{
							id.lcnv[0]--;
							l--;
						}
					}
					if (y>0 && At(getColor(id,x,y-1))<at2)
					{
						transparency(id,x,y-1,at2);
						if (y == id.lcnv[1]) 
						{
							id.lcnv[1]--;
							t--;
						}
					}
					if (x+1<getWidth(id) && At(getColor(id,x+1,y))<at2)
					{
						transparency(id,x+1,y,at2);
						if (x == id.lcnv[2]) 
						{
							id.lcnv[2]++;
							r++;
						}
					}
					if (y+1<getHeight(id) && At(getColor(id,x,y+1))<at2)
					{
						transparency(id,x,y+1,at2);
						if (y == id.lcnv[3]) 
						{
							id.lcnv[3]++;
							d++;
						}
					}
				}
	}
}

void Overlay (Layer& id, unsigned int color)
{
	int l,r,t,d;
	l = (id.lcnv[0]<0?0:id.lcnv[0]); r = (id.lcnv[2]>=getWidth(id)?getWidth(id):id.lcnv[2]);
	t = (id.lcnv[1]<0?0:id.lcnv[1]); d = (id.lcnv[3]>=getHeight(id)?getHeight(id):id.lcnv[3]);
	DrawRect(id,color,l,t,r-l,d-t,1);
}

void Fill (Layer& id, unsigned int msc, int x, int y)
{
	int l,r,t,d;
	l = (id.lcnv[0]<0?0:id.lcnv[0]); r = (id.lcnv[2]+1>=getWidth(id)?getWidth(id)-1:id.lcnv[2]);
	t = (id.lcnv[1]<0?0:id.lcnv[1]); d = (id.lcnv[3]+1>=getHeight(id)?getHeight(id)-1:id.lcnv[3]);
	unsigned int cvr = At(getColor(id,x,y));
	if (msc == cvr) return;
	transparency(id,x,y,msc);
	if (x-1>l && At(getColor(id,x-1,y)) == cvr) Fill(id,msc,x-1,y);
	if (y-1>t && At(getColor(id,x,y-1)) == cvr) Fill(id,msc,x,y-1);
	if (x+1<r && At(getColor(id,x+1,y)) == cvr) Fill(id,msc,x+1,y);
	if (y+1<d && At(getColor(id,x,y+1)) == cvr) Fill(id,msc,x,y+1);
}


void RadialShine(Layer& id, unsigned int msc, int x, int y, int r, int action)
{
	for (int i=-r; i<=r; i++)
		for (int j=-r; j<=r; j++)
		{
			float l = sqrt(i*i+j*j);
			if (l>r) continue;
			MSDrawC(id,x+i,y+j,msc*(r-l)/r,0,0,0,action);
		}
}

void CircularShine(Layer& id, unsigned int msc, int x, int y, int r, int dr, int action)
{
	for (int i=-r-dr; i<=r+dr; i++)
		for (int j=-r-dr; j<=r+dr; j++)
		{
			float l = sqrt(i*i+j*j);
			float dl = abs(l-r);
			if (dl>dr) continue;
			MSDrawC(id,x+i,y+j,msc*(dr-dl)/dr,0,0,0,action);
		}
}

void NOT(Layer& id, Layer& op)
{
	int l,r,t,d;
	l = (id.lcnv[0]<op.lcnv[0]?op.lcnv[0]:id.lcnv[0]); r = (id.lcnv[2]>op.lcnv[2]?op.lcnv[2]:id.lcnv[2]);
	t = (id.lcnv[1]<op.lcnv[1]?op.lcnv[1]:id.lcnv[1]); d = (id.lcnv[3]>op.lcnv[3]?op.lcnv[3]:id.lcnv[3]);
	for (int i=l; i<r; i++)
		for (int j=t; j<d; j++)
			if (At(getColor(op,i,j))>127) transparency(id,i,j,0);
}

void AND(Layer& id, Layer& op)
{
	int l,r,t,d;
	l = (id.lcnv[0]<op.lcnv[0]?op.lcnv[0]:id.lcnv[0]); r = (id.lcnv[2]>op.lcnv[2]?op.lcnv[2]:id.lcnv[2]);
	t = (id.lcnv[1]<op.lcnv[1]?op.lcnv[1]:id.lcnv[1]); d = (id.lcnv[3]>op.lcnv[3]?op.lcnv[3]:id.lcnv[3]);
	for (int i=l; i<r; i++)
		for (int j=t; j<d; j++)
			if (At(getColor(op,i,j))<127) transparency(id,i,j,0);
}
