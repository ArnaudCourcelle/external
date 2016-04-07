/*-----------------------------------------------------------------
  LOG
  GEM - Graphics Environment for Multimedia

  render to offscreen buffer and make texture
   
  created 11/27/2005
   
  Copyright (c) 2005-2006 James Tittle II, tigital AT mac DOT com
  For information on usage and redistribution, and for a DISCLAIMER OF ALL
  WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

  -----------------------------------------------------------------*/

#ifndef _INCLUDE__GEM_CONTROLS_nViewPort_H_
#define _INCLUDE__GEM_CONTROLS_nViewPort_H_

#include "Base/GemBase.h"

class GEM_EXTERN nViewPort : public GemBase
{
  CPPEXTERN_HEADER(nViewPort, GemBase);

    public:

  nViewPort();

 protected:

  ~nViewPort(void);

  void         render(GemState *state);
  
 private:
 void initFBO();
 GLuint worldTexture;
 t_outlet   *m_outTexInfo;
 bool init;
};

#endif   