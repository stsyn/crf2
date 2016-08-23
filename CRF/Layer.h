#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

	
	#define CRF_MAX_LAYERS 1024
	class Layer
	{
	public: int **cnv, cnvd[2],id,mode;
			Layer();
			~Layer();
			int lcnv[4];
	};
	extern Layer *_cnv[CRF_MAX_LAYERS];

#endif