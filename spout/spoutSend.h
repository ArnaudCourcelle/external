 /* ------------------------------------------------------------------
  * GEM - Graphics Environment for Multimedia
  *
  *  Copyright (c) 2002-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
  *	zmoelnig@iem.kug.ac.at
  *  For information on usage and redistribution, and for a DISCLAIMER
  *  OF ALL WARRANTIES, see the file, "GEM.LICENSE.TERMS"
  *
  *  this file has been generated...
  * ------------------------------------------------------------------
  */

#ifndef _INCLUDE__GEM_OPENGL_spoutSend_H_
#define _INCLUDE__GEM_OPENGL_spoutSend_H_

#include "Base/GemBase.h"
//nclude "ofxSpout.h"
//#include "ofxSpout.h"
#include "SpoutLibrary.h"
/*
 CLASS
	spoutSend
 */

class GEM_EXTERN spoutSend : public GemBase
{
	CPPEXTERN_HEADER(spoutSend, GemBase);

	public:
	  // Constructor
	  spoutSend (t_symbol* s);	// CON

	protected:
	  // Destructor
	  virtual ~spoutSend ();
	  virtual void	render (GemState *state);
	t_symbol* sym;
	GLuint spoutTexture;
	GLuint num;
	int h,w,mode;
	//bool isTextureShared;
	bool texture;
	GLuint sendertexture;			// Local OpenGL texture used for sharing
	bool bInitialized;				// Initialization result
	bool bMemoryShare;	
	t_symbol *m_bindname;
	static void info(void* data);
	void infoMess();
	static void setMessCallback  (void*data, t_symbol*indexed);
	static void heightMessCallback(void *data, t_floatarg Tsize, t_floatarg Theight,  t_floatarg Twidth, t_floatarg Tnum, t_floatarg Tmode);
	virtual void setMess(t_symbol*indexed);
	virtual void  heightMess(t_floatarg Tsize, t_floatarg Theight,  t_floatarg Twidth, t_floatarg Tnum, t_floatarg Tmode);
	private:

	// we need some inlets
	t_inlet         *m_inTexID;
	bool InitGLtexture(GLuint &texID, unsigned int width, unsigned int height);

		SPOUTLIBRARY *spoutsender; // A sender object
		char sendername[256];      // Sender name

};
#endif // for header file
