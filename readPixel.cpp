/*
 ArNO Courcelle 2014, simple Reader du ViewPort en openGL 2
 width GEM.
 */

#include "readPixel.h"

CPPEXTERN_NEW(readPixel);

readPixel :: readPixel()
{		
	ok=0;
	m_outTexInfo = outlet_new(this->x_obj, 0);
	
}

void readPixel :: startRendering() 
{
	
	
};
void readPixel :: find(int x, int y)
{
	xx=x;
	yy=y;
	ok=1;
};
void readPixel :: render(GemState *state)
{
	if (ok==1){
	t_atom ap[4];
	float  pixels[4];
	glReadPixels(xx, yy, 1, 1, GL_RGBA, GL_FLOAT, &pixels[0]);
	SETFLOAT(ap, (float)pixels[0]);
	SETFLOAT(ap+1, (float)pixels[1]);
	SETFLOAT(ap+2,(float)pixels[2]);
	SETFLOAT(ap+3, (float)pixels[3]);
	outlet_list(m_outTexInfo, 0, 4, ap);
	}
	ok=0;
	
	
}

void readPixel :: stopRendering()
{
};



void readPixel :: obj_setupCallback(t_class *classPtr)
{
	CPPEXTERN_MSG2(classPtr, "find",find,int, int);
};
