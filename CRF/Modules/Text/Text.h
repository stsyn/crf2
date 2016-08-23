#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

	#include "Font.h"
	int TextWidth(Font& font, char *str);
	inline int TextHeight(Font& font, char *str);
	void PrintText(Layer& id, Font& font, char *str, int color, int x, int y);

#endif