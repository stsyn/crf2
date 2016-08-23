#include "../../Core.h"
#define LSPRITE_FRAMES_MAX 65536
#define LSPRITE_ANIMS_MAX 256
#define LSPRITE_MAX_ANIMSIZE 65536
#define LSPRITE_MAX_METASIZE 256
#define LSPRITE_MAX_CHILDREN 256

class LSprite
{
	
private:
	int animcounter,framecounter,nextanim;

bool getBit(int i, int pos)
{
	return (i >> pos) && 1;
}

public:
	int metas,children;
	int frames,anims,*frameOffsets[2],*frameSizes[2],*frameFix[2],**anim[3],*childPos[2];
	char *animsize, **childName;
	int *meta, pos_x, pos_y, speed, angle,cam_x,cam_y,statx,staty,animtype;
	LSprite *Child;
	Layer contentlayer;

void Load(char *str, int stx, int sty)
{
#define ALWAYS_SHOW_FIRST 1
	unsigned char oe;
	int i,j;
	char strn[128], fname[64];
	FILE *spr_file;
	spr_file = fopen(str, "r"); 

	statx=stx;
	staty=sty;
/*

  FILE CONTENT:
  x1 - name lenght
  x2~ - texturename
  x3 - frames counter
  x4:
	x1 - offSetX
	x2 - offSetY
	x3 - sizeX
	x4 - sizeY
  x5 - anims counter
  ; 0 - static
  ; 1 - active
  ; 2 - die
  x6:
	x1 - anim size
	x2:
	  x1 - frame num
	  x2 - frame time
	  x3 - allow changing (bool)
  x7 - meta content size
  x8~ - meta content
  x9 - childs count
  x10:
	x1 - name lenght
	x2~ - child name
	x3 - posx
	x4 - posy

*/
	fread(&oe, 1, 1, spr_file);

	for (i=0; i<oe; i++) fread(&fname[i], 1, 1, spr_file);
	fname[i]='\0';

	tex_read(strn,contentlayer);

	fread(&frames, 1, 2, spr_file);
	frameOffsets[0] = new int[frames];
	frameOffsets[1] = new int[frames];
	frameSizes[0] = new int[frames];
	frameSizes[1] = new int[frames];
	frameFix[0] = new int[frames];
	frameFix[1] = new int[frames];

	for (i=0; i<frames; i++)
	{
		fread(&frameOffsets[0][i], 1, 2, spr_file);		
		fread(&frameOffsets[1][i], 1, 2, spr_file);		
		fread(&frameSizes[0][i], 1, 2, spr_file);		
		fread(&frameSizes[1][i], 1, 2, spr_file);		
		fread(&frameFix[0][i], 1, 2, spr_file);		
		fread(&frameFix[1][i], 1, 2, spr_file);	
		frameFix[0][i] -= 32768;
		frameFix[1][i] -= 32768;
	}

	fread(&anims, 1, 2, spr_file);
	anim[0] = new int*[anims];
	anim[1] = new int*[anims];
	anim[2] = new int*[anims];
	animsize = new char[anims];
	
	for (i=0; i<anims; i++)
	{
		fread(&animsize[i], 1, 2, spr_file);
		anim[0][i] = new int[animsize[i]];
		anim[1][i] = new int[animsize[i]];
		anim[2][i] = new int[animsize[i]];
		
		for (j=0; j<animsize[i]; j++)
		{
			fread(&anim[0][i][j], 1, 2, spr_file);
			fread(&anim[1][i][j], 1, 2, spr_file);	
			fread(&anim[2][i][j], 1, 4, spr_file);
		}
		
	}
	fread(&metas, 1, 1, spr_file);
	meta = new int[metas];

	for (i=0; i<metas; i++)
	{
		fread(&meta[i], 1, 2, spr_file);				
	}
	fread(&children, 1, 1, spr_file);
	childPos[0] = new int[children];
	childPos[1] = new int[children];
	childName = new char*[children];
	Child = new LSprite[children];
	for (i=0; i<children; i++)
	{
		fread(&oe, 1, 1, spr_file);
		childName[i] = new char[oe];
		for (int j=0; j<oe; j++) fread(&childName[i][j], 1, 1, spr_file);
		childName[i][j]='\0';	
		
		fread(&childPos[0][i], 1, 2, spr_file);
		fread(&childPos[1][i], 1, 2, spr_file);

		Child[i].Load(childName[i],statx+childPos[0][i],staty+childPos[1][i]);
	}

	fclose(spr_file); 

	animtype=0;
	nextanim = 0;
	framecounter = 0;
	animcounter=0;
	pos_x=xmax*100/2;
	pos_y=ymax*100/2;
	cam_x = 0;
	cam_y = 0;
}

void Load(char *str)
{
	Load(str,0,0);
}

void ChangeAnim(int n, bool force)
{
	nextanim = n;
	if (force)
	{
		animtype = n;
		framecounter = 0;
		animcounter = 0;
	}
	for (int i=0; i<children; i++) Child[i].ChangeAnim(n,force);
}

void Update()
{
	pos_x = pos_x+cos(3.14*angle/180)*speed;
	pos_y = pos_y-sin(3.14*angle/180)*speed;
	framecounter++;
	if (framecounter == anim[1][animtype][animcounter]) 
	{
		if (nextanim != animtype)
		{
			if (anim[2][animtype][animcounter])
			{
				animcounter = 0;
				animtype = nextanim;
			}
			else animcounter++;
		}
		else animcounter++;
		if (animcounter == animsize[animtype]) animcounter = 0;
		framecounter = 0;
	}
	for (int i=0; i<children; i++) Child[i].Update();
}

void Draw(Layer& id)
{
	int t = anim[0][animtype][animcounter];
	FragmentLayer(contentlayer,id,statx+cam_x-frameSizes[0][t]/2+pos_x/100+frameFix[0][t],staty+cam_y-frameSizes[1][t]/2+pos_y/100+frameFix[1][t],frameOffsets[0][t],frameOffsets[1][t],frameSizes[0][t],frameSizes[1][t],0);
	for (int i=0; i<children; i++) Child[i].Draw(id);
}
};
