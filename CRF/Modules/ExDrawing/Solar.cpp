#include "../Base.h"
#include "../../Core.h"
#include "../Geometry.h"
#include "../Binaries.h"
#include "../../Layer.h"
#include <math.h>


void SolarShine(Layer& id, int sx, int sy, int zoom)
{
	Layer *pattern = new Layer;

	//getting length
	int dx = sx-getWidth(id)/2,
		dy = sy-getHeight(id)/2;
	int ln = sqrt(dx*dx+dy*dy);
	if (ln<40*zoom/128) return;

	//central point
	buildLayer(*pattern,5,5);
	FDrawRect(*pattern,0x00a8b492,0,0,5,5);
	transparency(*pattern,2,2,255);
	Smooth(*pattern,1,255);
	IncludeLayer(*pattern,id,getWidth(id)/2-2,getHeight(id)/2-2,1);

	//1/5 circle
	int sz = 17*zoom/128,
		psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0xFF0e1e38,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz+dx/5,getHeight(id)/2-psz+dy/5,1);

	//2/5 circles
	sz = 51*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0xFF1a120e,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz+2*dx/5,getHeight(id)/2-psz+2*dy/5,1);
	
	sz = 25*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0xFF1a120e,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz+2*dx/5-dx/18,getHeight(id)/2-psz+2*dy/5-dy/18,1);

	
	sz = 17*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0x801a120e,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz+2*dx/5+dx/20,getHeight(id)/2-psz+2*dy/5+dy/20,1);

	//large shine
	sz = 69*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	FDrawRect(*pattern,0x0042469c,0,0,sz,sz);
	CircularShine(*pattern,192,psz,psz,psz-6,6,11);
	IncludeLayer(*pattern,id,sx-psz,sy-psz,1);

	sz = 65*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	FDrawRect(*pattern,0x00FFFFFF,0,0,sz,sz);
	RadialShine(*pattern,255,psz,psz,psz,11);
	IncludeLayer(*pattern,id,sx-psz,sy-psz,1);

	sz = 131*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	FDrawRect(*pattern,0x0042469c,0,0,sz,sz);
	RadialShine(*pattern,192,psz,psz,psz,11);
	IncludeLayer(*pattern,id,sx-psz,sy-psz,1);

	//outer circle
	sz = 41*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0x80244869,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz+13*dx/10,getHeight(id)/2-psz+13*dy/10,1);

	//inner
	//point
	buildLayer(*pattern,7,7);
	FDrawRect(*pattern,0x00b0cd9f,0,0,7,7);
	RadialShine(*pattern,255,3,3,3,11);
	IncludeLayer(*pattern,id,getWidth(id)/2-3*dx/10-3,getHeight(id)/2-3*dy/10-3,1);

	//1/2 circles
	sz = 51*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0xFF000b15,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz-dx/2,getHeight(id)/2-psz-dy/2,1);
	
	sz = 27*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0xFF000b15,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz-dx/2+dx/18,getHeight(id)/2-psz-dy/2+dy/18,1);

	
	sz = 17*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0xFF000b15,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz-dx/2-dx/50,getHeight(id)/2-psz-dy/2-dy/50,1);

	//green

	sz = 21*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0xFF15200D,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz-dx*7/10,getHeight(id)/2-psz-dy*7/10,1);

	sz = 61*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	DrawFillCircle(*pattern,0xFF15200D,psz,psz,psz);
	RadialShine(*pattern,255,psz,psz,psz,RENDER_REM_ALPHA);
	DrawCircle(*pattern,0xFF031b20,psz,psz,psz);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz-dx,getHeight(id)/2-psz-dy,1);

	//blue
	buildLayer(*pattern,11,11);
	FDrawRect(*pattern,0x00ff0000,0,0,11,11);
	RadialShine(*pattern,255,5,5,5,11);
	IncludeLayer(*pattern,id,getWidth(id)/2-dx*7/10-dx/70,getHeight(id)/2-dy*7/10-dy/70,1);

	//outer
	sz = 121*zoom/128;
	psz = (sz-1)/2;
	buildLayer(*pattern,sz,sz);
	FDrawRect(*pattern,0x00050e11,0,0,sz,sz);
	DrawCircle(*pattern,0xff050e11,psz,psz,psz-4);
	Smooth(*pattern,6,255);
	IncludeLayer(*pattern,id,getWidth(id)/2-psz-5*dx/4,getHeight(id)/2-psz-5*dy/4,1);

	delete pattern;
}