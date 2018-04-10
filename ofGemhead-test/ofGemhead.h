/*-----------------------------------------------------------------
  LOG
  GEM - Graphics Environment for Multimedia

  The starting point for all graphics trees

  Copyright (c) 1997-1998 Mark Danks. mark@danks.org
  Copyright (c) Günther Geiger. geiger@epy.co.at
  Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
  For information on usage and redistribution, and for a DISCLAIMER OF ALL
  WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

  -----------------------------------------------------------------*/

#ifndef _INCLUDE__GEM_CONTROLS_GEMHEAD_H_
#define _INCLUDE__GEM_CONTROLS_GEMHEAD_H_

#include "Base/CPPExtern.h"
#include "Controls/gemreceive.h"

class GemState;
class GemCache;

/*-----------------------------------------------------------------
  -------------------------------------------------------------------
  CLASS
  gemhead
    
  The starting point for all graphics trees

  DESCRIPTION
    
  "bang" - sends out a state list
    
  -----------------------------------------------------------------*/
class GEM_EXTERN ofGemhead : public gemreceive
{
  CPPEXTERN_HEADER(ofGemhead, gemreceive);

 public:

  //////////
  // Constructor
  ofGemhead();
    	
  //////////
  // A render message
  void	    	renderGL(GemState *state);
 
 protected:
    	
  //////////
  // Destructor
  virtual ~ofGemhead();

  std::string m_basename;
    	
 private:

  t_outlet    	*m_out1;

  GemCache    	*m_cache;   	    	    // The cache information

  int 	    	m_renderOn;

  void	    	bangMess();
};

#endif	// for header file
