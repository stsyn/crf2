#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#define INVERT_VERTICAL		1
#define INVERT_HORISONTAL	2
#define INVERT_DIAGONAL		4


	void TransformLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode);
	extern inline void TransformLayer(Layer& id, Layer& tid, int tx, int ty, int mode);
	extern inline void RotateLayer(Layer& id, Layer& tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode);
	extern inline void RotateLayer(Layer& id, Layer& tid, int tx, int ty, int mode);
	void MoveLayer(Layer& id, int xa, int ya);

#endif