#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#define INVERT_VERTICAL		1
#define INVERT_HORISONTAL	2
#define INVERT_DIAGONAL		4


	void TransformLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode);
	void MoveLayer(Layer& id, int xa, int ya);


inline void TransformLayer(Layer& id, Layer& tid, int tx, int ty, int mode)
{
	TransformLayer(id,tid,tx,ty,0,0,getWidth(id),getHeight(id),mode);
	return;
}

inline void RotateLayer(Layer& id, Layer& tid, int tx, int ty, int mode)
{
	if (mode == 0) TransformLayer(id,tid,tx,ty,0,0,getWidth(id),getHeight(id),0);
	else if (mode == 1) TransformLayer(id,tid,tx,ty,0,0,getWidth(id),getHeight(id),6);
	else if (mode == 2) TransformLayer(id,tid,tx,ty,0,0,getWidth(id),getHeight(id),3);
	else if (mode == 3) TransformLayer(id,tid,tx,ty,0,0,getWidth(id),getHeight(id),5);
}

inline void RotateLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode)
{
	if (mode == 0) TransformLayer(id,tid,tx,ty,x2,y2,xk,yk,0);
	else if (mode == 1) TransformLayer(id,tid,tx,ty,x2,y2,xk,yk,6);
	else if (mode == 2) TransformLayer(id,tid,tx,ty,x2,y2,xk,yk,3);
	else if (mode == 3) TransformLayer(id,tid,tx,ty,x2,y2,xk,yk,5);
}
#endif