#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

	void DrawVLine(int id, unsigned int color, int x1, int y1, int k);
	void FDrawVLine(int id, unsigned int color, int x1, int y1, int k);
	void DrawHLine(int id, unsigned int color, int x1, int y1, int k);
	void FDrawHLine(int id, unsigned int color, int x1, int y1, int k);
	void DrawFrame(int id, unsigned int color, int x, int y, int xk, int yk);
	void FDrawRect(int id, unsigned int color, int x1, int y1, int xk, int yk);
	void DrawRect(int id, unsigned int color, int x1, int y1, int xk, int yk);
	void DrawRect(int id, unsigned int color, int x1, int y1, int xk, int yk, int mode);
	void DoGray(int id, int tid, unsigned int value, int x1, int y1);
	void VGradient(int id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode);
	void HGradient(int id, unsigned int colorA, unsigned int colorB, int x1, int y1, int xk, int yk, int mode);
	void IncludeLayer(int id, int tid, int x1, int y1, int mode);
	void IncludeLayer(int id, int tid, int x1, int y1);
	void FragmentLayer(int id, int tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode);
	void FragmentLayer(int id, int tid, int tx, int ty, int x2, int y2, int xk, int yk);
	void TransformLayer(int id, int tid, int tx, int ty, int x2, int y2, int xk, int yk, int mode);
	void TransformLayer(int id, int tid, int tx, int ty, int mode);
	void BWNoise(int id, int x1, int y1, int xk, int yk);

#endif