#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

	class Font
	{
	public:
		int letterspacing[256], height;
		Layer container;
		bool monospaced;
		void CreateMonospacedFont(char *fontname, int lettersize);
		void CreateFont(char *fontname, int lettersize[256], bool add);

	};

#endif