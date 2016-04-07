/*
 ArNO Courcelle 2014, simple Reader du ViewPort en openGL 2
 width GEM.
 */


#include "Base/GemBase.h"


class GEM_EXTERN readPixel : public GemBase
{
	CPPEXTERN_HEADER(readPixel, GemBase);
	
public:
	// Constructor
	readPixel();
	int ok;
	t_outlet	*m_outTexInfo;
	GLuint worldTexture;
	int xx,yy;
protected:
	void find(int,int);
	// Rendering    
	
	virtual void startRendering();
	virtual void render(GemState *state);
	virtual void postrender(GemState *state){};
	
	// Stop Transfer
	virtual void stopRendering();
	
};
