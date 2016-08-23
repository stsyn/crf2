#include <stdlib.h>
#include "../Layer.h"
#include "../Core.h"

int gener(int max)
{
	return max?(rand()%max):0; 
}

void BWNoise(Layer& id, int x1, int y1, int xk, int yk)
{
	int i,j,t;
	for (i = 0; i<xk; i++)
		for (j = 0; j<yk; j++)
		{	
			t = gener(256);
			plot(id,x1+i,y1+j,t,t,t);
		}
}

void ANoise(Layer& id, int x1, int y1, int xk, int yk)
{
	int i,j,t;
	for (i = 0; i<xk; i++)
		for (j = 0; j<yk; j++)
		{	
			t = gener(256);
			transparency(id,x1+i,y1+j,t);
		}
}