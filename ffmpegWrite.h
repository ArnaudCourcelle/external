/*
 ArNO Courcelle 2014, simple Reader du ViewPort en openGL 2
 width GEM.
 */


#include "Base/GemBase.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string>
using namespace std;
class GEM_EXTERN ffmpegWrite : public GemBase
{
	CPPEXTERN_HEADER(ffmpegWrite, GemBase);
	
public:
	// Constructor
	ffmpegWrite();
	~ffmpegWrite();
protected:
	void find(int);
	void file(int argc, t_atom *argv);
	void argMsg(int argc, t_atom *argv);
	void mode(int argc, t_atom *argv);
	void texture(int id, int h,  int w, int gl_, int flip);
	void tst();
	void binMsg(t_symbol *tst);
	void openMsg(t_symbol *tst);
	// Rendering    
	
	virtual void startRendering();
	virtual void render(GemState *state);
	virtual void postrender(GemState *state){};

	
	// Stop Transfer
	virtual void stopRendering();
private:
	FILE* ffmpeg;
	unsigned char *buffer;
	string _mode;
	string commande;
	string bin,output,size,arg;
	bool startCapture;
	bool textureIsOk;
	GLint dims[4];
	int buf_size;
	int Tw,Th;
	
    t_inlet         *m_inTexID;
	GLuint extTex;
	//int xx,yy;
	static void 	fileMessCallback(void *data, t_symbol *s, int argc, t_atom *argv);
	static void 	modeMC(void *data, t_symbol *s, int argc, t_atom *argv);
	static void 	argMC(void *data, t_symbol *s, int argc, t_atom *argv);

	static void texMC(void *data, t_floatarg Tsize, t_floatarg Theight,  t_floatarg Twidth, t_floatarg Tnum, t_floatarg Tmode);
	
};
