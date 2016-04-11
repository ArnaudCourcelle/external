/*
 ArNO Courcelle 2014, simple Reader du ViewPort en openGL 2
 width GEM.
 */
//ffmpeg -r 60 -f rawvideo -pix_fmt rgba -s 1280x720 -i -  -threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip /Volumes/media/tst/output.mp4
#include "ffmpegWrite.h"

CPPEXTERN_NEW(ffmpegWrite);

ffmpegWrite :: ffmpegWrite()
{	
	
	bin="/usr/local/bin/ffmpeg";
	string path="out.mp4";
	char buf[MAXPDSTRING];
  	canvas_makefilename(const_cast<t_canvas*>(getCanvas()), (char*)path.c_str(), buf, MAXPDSTRING);
	output=buf;
	char _size[256];
	snprintf(_size, sizeof(_size), "-s %ix%i",500,500);
	size=_size;
	arg="-y -f rawvideo -pix_fmt rgb24 -r 25  -i -  -an -b:v 1000k";
	_mode="viewPort";
	textureIsOk=false;
	startCapture=false;
	
}
ffmpegWrite :: ~ffmpegWrite(){
if(ffmpeg)
pclose(ffmpeg);
free (buffer);
}

void ffmpegWrite :: tst()
{
commande=bin+" "+size+" "+arg+" "+output;
post(commande.c_str());
if(ffmpeg){
	startCapture=false;
	pclose(ffmpeg);
}
ffmpeg=popen(commande.c_str(), "w");
if(!ffmpeg){post("ffmpeg : failed to create");}
}


void ffmpegWrite :: file(int argc, t_atom *argv)
{
commande="";
for (int i=0;i<argc;i++){
string tmp=atom_getsymbol(&argv[i])->s_name;
if (tmp=="float"){
char buffer[256]; 
snprintf(buffer, sizeof(buffer), "%f", atom_getfloat(&argv[i]));
commande+=buffer;}
else 
{commande+=tmp;}
commande+=" ";
}
post(commande.c_str());
if(ffmpeg){
	startCapture=false;
	pclose(ffmpeg);
}
ffmpeg=popen(commande.c_str(), "w");
if(!ffmpeg){post("ffmpeg : failed to create");}
}


void ffmpegWrite :: startRendering() 
{
};

void ffmpegWrite :: find(int x)
{
	if (x!=0&&(ffmpeg)){
	startCapture=true;
	}
	else {
	startCapture=false;
	if (ffmpeg)
	pclose(ffmpeg);
	}

	
};
void ffmpegWrite :: texture(int id, int h,  int w, int gl_, int flip){
	if (gl_==34037) {
		extTex = id;
		Tw=w;
		Th=h;
		textureIsOk=true;
		}
	else {
		textureIsOk=false;
		post("ERROR : must be texture rectangle");
	}
}

void ffmpegWrite :: render(GemState *state)
{
	if (_mode=="viewPort"){
	glGetIntegerv(GL_VIEWPORT, dims);
	buf_size=dims[2]*dims[3]*3;
	if (startCapture){	
	if (!(buffer = (unsigned char *) calloc(1, buf_size))){
		return;
		}
		glReadPixels(0, 0, dims[2], dims[3], GL_RGB, GL_UNSIGNED_BYTE, buffer);
		if(ffmpeg){
			fwrite(buffer, sizeof(unsigned char),buf_size, ffmpeg);
		}else{
			post ("error: can't write into buffer");}
		}
	}
	
	else if (_mode=="texture"){
	buf_size=Tw*Th*3;
	if (startCapture&&textureIsOk){	
	if (!(buffer = (unsigned char *) calloc(1, buf_size))){
		return;
		}
		glEnable(GL_TEXTURE_RECTANGLE_EXT);
		glBindTexture(GL_TEXTURE_RECTANGLE_EXT, extTex);
		glGetTexImage(GL_TEXTURE_RECTANGLE_EXT,0,GL_RGB, GL_UNSIGNED_BYTE, buffer);
		if(ffmpeg){
			fwrite(buffer, sizeof(unsigned char),buf_size, ffmpeg);
		}else{
			post ("error: can't write into buffer");}
		}
	}
	else {
	_mode="viewPort";
		}


}


void ffmpegWrite :: mode(int argc, t_atom *argv){
_mode=atom_getsymbol(&argv[0])->s_name;
 if (_mode=="viewPort"){
 	glGetIntegerv(GL_VIEWPORT, dims);
 	char _size[256];
	snprintf(_size, sizeof(_size), "-s %ix%i",dims[2],dims[3]);
	size=_size;
	}
 else if (_mode=="texture"){
 char _size[256];
	snprintf(_size, sizeof(_size), "-s %ix%i",Th,Tw);
	size=_size;
	}
}
void ffmpegWrite::openMsg(t_symbol *tst){
	
 	char buf[MAXPDSTRING];
  	canvas_makefilename(const_cast<t_canvas*>(getCanvas()), tst->s_name, buf, MAXPDSTRING);
	output=buf;
}
void ffmpegWrite::binMsg(t_symbol *tst){
	
 	char buf[MAXPDSTRING];
  	canvas_makefilename(const_cast<t_canvas*>(getCanvas()), tst->s_name, buf, MAXPDSTRING);
	bin=buf;
}
void ffmpegWrite :: argMsg(int argc, t_atom *argv)
{
arg="";
for (int i=0;i<argc;i++){
string tmp=atom_getsymbol(&argv[i])->s_name;
if (tmp=="float"){
char buffer[256]; 
snprintf(buffer, sizeof(buffer), "%f", atom_getfloat(&argv[i]));
arg+=buffer;}
else 
{arg+=tmp;}
arg+=" ";
}
}

void ffmpegWrite :: stopRendering()
{
};



void ffmpegWrite :: obj_setupCallback(t_class *classPtr)
{
  CPPEXTERN_MSG0(classPtr, "bang",   tst);
  CPPEXTERN_MSG1(classPtr, "output", openMsg, t_symbol*);
  CPPEXTERN_MSG1(classPtr, "bin", binMsg, t_symbol*);
	class_addmethod(classPtr, reinterpret_cast<t_method>(&ffmpegWrite::argMC),
		  gensym("arg"), A_GIMME, A_NULL);
 class_addmethod(classPtr, reinterpret_cast<t_method>(&ffmpegWrite::fileMessCallback),
		  gensym("cmd"), A_GIMME, A_NULL);
class_addmethod(classPtr, reinterpret_cast<t_method>(&ffmpegWrite::modeMC),
		  gensym("mode"), A_GIMME, A_NULL);
	CPPEXTERN_MSG1(classPtr, "capture",find,int);
	class_addmethod(classPtr, reinterpret_cast<t_method>(&ffmpegWrite::texMC),
					gensym("texture"), A_FLOAT,A_FLOAT,A_FLOAT,A_FLOAT,A_FLOAT, A_NULL);
};
void ffmpegWrite :: texMC(void *data, t_floatarg Tsize, t_floatarg Theight,  t_floatarg Twidth, t_floatarg Tnum, t_floatarg Tmode)
{
    GetMyClass(data)->texture(static_cast<int>(Tsize),static_cast<int>(Theight),static_cast<int>(Twidth),static_cast<int>(Tnum),static_cast<int>(Tmode));
}
void ffmpegWrite :: fileMessCallback(void *data, t_symbol *s, int argc, t_atom *argv)
{
  GetMyClass(data)->file(argc, argv);
}
void ffmpegWrite :: argMC(void *data, t_symbol *s, int argc, t_atom *argv)
{
  GetMyClass(data)->argMsg(argc, argv);
}
void ffmpegWrite :: modeMC(void *data, t_symbol *s, int argc, t_atom *argv)
{
  GetMyClass(data)->mode(argc, argv);
}