#include "Layer.h"
#include "Core.h"
#include <stdio.h>
#include <windows.h>
int pt=0;
Layer::Layer()
{
	mode = 0;
	cnvd[0]=0;
	cnvd[1]=0;
	id = -1;
	for (int i=0; i<pt; i++) 
		if (_cnv[i] == NULL)
		{
			id = i;
			_cnv[i] = this;
			break;
		}
	if (id == -1)
	{
		id = pt;
		_cnv[pt] = this;
		pt++;
	}
}

Layer::~Layer()
{
	_cnv[id] = NULL;
	delLayer(*this);
}