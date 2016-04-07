////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// tigital AT mac DOT com
//
// Implementation file
//
//    Copyright (c) 1997-1999 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//    Copyright (c) 2005-2006 James Tittle II, tigital At mac DoT com
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

#include "nViewPort.h"

CPPEXTERN_NEW(nViewPort);


nViewPort :: nViewPort()
{
  m_outTexInfo = outlet_new(this->x_obj, 0);
	init=false;
}


nViewPort :: ~nViewPort()
{
if(worldTexture)	glDeleteTextures(1, &worldTexture);
  outlet_free(m_outTexInfo);
}


void nViewPort :: render(GemState *state)
{
	initFBO();
	GLint dims[4];
	glGetIntegerv(GL_VIEWPORT, dims);
	glEnable(GL_TEXTURE_RECTANGLE_EXT);
	glBindTexture(GL_TEXTURE_RECTANGLE_EXT, worldTexture);
	glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, 0, GL_RGBA8, dims[2], dims[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glCopyTexSubImage2D(GL_TEXTURE_RECTANGLE_EXT, 0, 0, 0, dims[0], dims[1], dims[2], dims[3]);
	t_atom ap[5];
 	SETFLOAT(ap+0, static_cast<t_float>(worldTexture));
  	SETFLOAT(ap+1, dims[2]);
  	SETFLOAT(ap+2, dims[3]);
  	SETFLOAT(ap+3, static_cast<t_float>(GL_TEXTURE_RECTANGLE_EXT));
  	SETFLOAT(ap+4, static_cast<t_float>(0.));
  	outlet_list(m_outTexInfo, 0, 5, ap);
}


void nViewPort :: initFBO()
{
if (!init)
{glGenTextures(1, &worldTexture);}
init=true;
}




void nViewPort :: obj_setupCallback(t_class *classPtr)
{

}
