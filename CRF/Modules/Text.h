#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

	void PrintText(int id, int fontn, char *str, int color, int x, int y);
	int TextWidth(int fontn, char *str);
	int TextHeight(int fontn, char *str);
	void PrintNum(int id, int fontn, int subj, int color, int x, int y, int k);

#endif