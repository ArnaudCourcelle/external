////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
// Implementation file
//
//    Copyright (c) 1997-1999 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

#include "ofGemhead.h"

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#endif

#include "Gem/Manager.h"
#include "Gem/State.h"
#include "Gem/Cache.h"
#include "Base/GemBase.h"

#include "Gem/GLStack.h"
#include "RTE/MessageCallbacks.h"
#include "Gem/Exception.h"

#include <stdio.h>

#ifdef _MSC_VER  /* This is only for Microsoft's compiler, not cygwin, e.g. */
# define snprintf _snprintf
#endif

CPPEXTERN_NEW(ofGemhead);



/////////////////////////////////////////////////////////
//
// ofGemhead
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
ofGemhead :: ofGemhead() :
  gemreceive(gensym("__gem_render")),

  m_cache(new GemCache(0)), m_renderOn(1)
{
    GLenum err = glewInit();
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
ofGemhead :: ~ofGemhead()
{
   
    if(m_cache)delete m_cache;
    m_cache=NULL;
}

/////////////////////////////////////////////////////////
// renderGL
//
/////////////////////////////////////////////////////////
void ofGemhead :: renderGL(GemState *state)
{
  static const GLfloat a_color[]={0.2,0.2,0.2,1};
  static const GLfloat d_color[]={0.8,0.8,0.8,1};
  static const GLfloat e_color[]={0.0,0.0,0.0,1};
  static const GLfloat s_color[]={0.0,0.0,0.0,1};
  static const GLfloat shininess[]={0.0};

  //if (!m_cache ) return;

  // set the default color and transformation matrix
  glColor4f(1.f, 1.f, 1.f, 1.f);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  a_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  d_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  gem::GLStack*stacks=NULL;
  if(state)
  {
    state->reset();
    // set the state dirty flag
    state->set(GemState::_DIRTY, m_cache->dirty);
    state->VertexDirty=m_cache->vertexDirty;

    state->get(GemState::_GL_STACKS, stacks);
    if(stacks)stacks->push();
  }

  // are we profiling and need to send new images?
  if (GemMan::getProfileLevel() >= 2)
	m_cache->resendImage = 1;

  t_atom ap[2];
  ap->a_type=A_POINTER;
  ap->a_w.w_gpointer=reinterpret_cast<t_gpointer*>(m_cache);  // the cache ?
  (ap+1)->a_type=A_POINTER;
  (ap+1)->a_w.w_gpointer=reinterpret_cast<t_gpointer*>(state);
  outlet_anything(this->m_outlet, gensym("gem_state"), 2, ap);

  m_cache->dirty = false;
  m_cache->vertexDirty=false;
  state->get(GemState::_GL_STACKS, stacks);
  if(stacks)stacks->pop();
}


/////////////////////////////////////////////////////////
// bangMess
//
/////////////////////////////////////////////////////////
void ofGemhead :: bangMess()
{

    if (m_cache) m_cache->reset(0);
  else         m_cache = new GemCache(0);
    GemState tempState;
    GemMan::fillGemState(tempState);

    renderGL(&tempState);
    glFlush();
}

/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void ofGemhead :: obj_setupCallback(t_class *classPtr)
{
  CPPEXTERN_MSG0(classPtr, "bang", bangMess);
}
