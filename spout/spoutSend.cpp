////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// Implementation file
//
// Copyright (c) 2002-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//	zmoelnig@iem.kug.ac.at
//  For information on usage and redistribution, and for a DISCLAIMER
//  *  OF ALL WARRANTIES, see the file, "GEM.LICENSE.TERMS"
//
//  this file has been generated...
////////////////////////////////////////////////////////

#include "spoutSend.h"

CPPEXTERN_NEW_WITH_ONE_ARG(spoutSend, t_symbol*,A_DEFSYM);

/////////////////////////////////////////////////////////
// Constructor
//
spoutSend :: spoutSend	(t_symbol* s) 
{
	w=512;
	h=512;
	sym = s;
	texture=false;
	bInitialized	= false;							
	m_inTexID  = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("texture"));
	spoutsender = GetSpout();
	 	if(!spoutsender) {
	 		post("spout init failed");
	 	}
			
	sendertexture = 0;
}
/////////////////////////////////////////////////////////
// Destructor
//
spoutSend :: ~spoutSend () {
	spoutsender->ReleaseSender(); 
	delete spoutsender;
	spoutsender = NULL;

}

/////////////////////////////////////////////////////////
// Render
//
void spoutSend :: render(GemState *state) {

	if(!bInitialized) {
		// Create the sender
		bInitialized = spoutsender->CreateSender(sym->s_name, h, w);
	}
		if(bInitialized) {if(texture!=false){
		spoutsender->SendTexture(spoutTexture, num,w, h);
		}
	}
}

/////////////////////////////////////////////////////////
// Variables
//
void spoutSend :: heightMess(t_floatarg id, t_floatarg Theight,  t_floatarg Twidth, t_floatarg Tnum, t_floatarg Tmode) {
	spoutTexture=int(id);
	h=int(Twidth);
	w=int(Theight);
	num=int(Tnum);
	mode=Tmode;
	texture=true;
}
void spoutSend :: setMess(t_symbol*indexed) {
	sym=indexed;
	bInitialized=false;
	spoutsender->ReleaseSender(); 

}
void spoutSend :: infoMess()
{
	post("spoutSend v.1 by ArNO Courcelle, 01/2015 \n enjoy!");
}
/////////////////////////////////////////////////////////
// static member functions
//

void spoutSend :: obj_setupCallback(t_class *classPtr) {
		class_addmethod(classPtr, reinterpret_cast<t_method>(&spoutSend::setMessCallback),
					gensym("set"), A_SYMBOL, A_NULL);
    class_addmethod(classPtr, reinterpret_cast<t_method>(&spoutSend::heightMessCallback),
					gensym("texture"), A_FLOAT,A_FLOAT,A_FLOAT,A_FLOAT,A_FLOAT, A_NULL);
	class_addmethod(classPtr, reinterpret_cast<t_method>(&spoutSend::info),
					gensym("info"), A_NULL);
}
void spoutSend :: info (void* data)
{
	 GetMyClass(data)->infoMess();//post("spoutSend v.1 by ArNO Courcelle, 01/2014 n/");
}
void spoutSend :: setMessCallback(void *data, t_symbol*indexed)
{
	GetMyClass(data)->setMess(indexed);
}

void spoutSend :: heightMessCallback(void *data, t_floatarg Tsize, t_floatarg Theight,  t_floatarg Twidth, t_floatarg Tnum, t_floatarg Tmode)
{
    GetMyClass(data)->heightMess((Tsize),static_cast<int>(Theight),static_cast<int>(Twidth),static_cast<int>(Tnum),static_cast<int>(Tmode));
}