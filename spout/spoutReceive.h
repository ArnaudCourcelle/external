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

#ifndef _INCLUDE__GEM_OPENGL_spoutReceive_H_
#define _INCLUDE__GEM_OPENGL_spoutReceive_H_

#include "Base/GemGLBase.h"
//nclude "ofxSpout.h"
//#include "ofxSpout.h"
#include "SpoutLibrary.h"
#include <string>
/*
 CLASS
	spoutReceive
 */

class GEM_EXTERN spoutReceive : public GemBase
{
	CPPEXTERN_HEADER(spoutReceive, GemBase);

	public:
	  // Constructor
	  spoutReceive (t_symbol* s);	// CON

	protected:
	  // Destructor
	  virtual ~spoutReceive ();
	  virtual void	render (GemState *state);
	t_symbol* s2;
	char sym[256];
	GLuint spoutTexture;
	GLuint num;
	int h,w,mode;
	//bool isTextureShared;
	bool texture;
	bool bMemoryMode;
	GLuint sendertexture;			// Local OpenGL texture used for sharing
	bool bInitialized;				// Initialization result
	bool bMemoryShare;	
	t_symbol *m_bindname;
	void initTexture();
	static void setMessCallback  (void*data, t_symbol*indexed);
	static void info(void* data);
	void infoMess();
	virtual void setMess(t_symbol*indexed);
	private:
	t_outlet	*m_outTexInfo;

	// we need some inlets
//	t_inlet         *m_inTexID;
//	bool InitGLtexture(GLuint &texID, unsigned int width, unsigned int height);

	SPOUTLIBRARY *spoutreceiver;  // A Spout receiver object
	//Spout test;
	// static member functions

};
#endif // for header file
