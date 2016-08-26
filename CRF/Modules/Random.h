#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

	int gener(int max);
	void BWNoise(Layer& id, int x1, int y1, int xk, int yk);
	void BWNoise(Layer& id, int x1, int y1, int xk, int yk, int m, int v);
	void ANoise(Layer& id, int x1, int y1, int xk, int yk);

#endif