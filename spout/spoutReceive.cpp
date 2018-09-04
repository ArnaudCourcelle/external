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

#include "spoutReceive.h"

CPPEXTERN_NEW_WITH_ONE_ARG(spoutReceive, t_symbol*,A_DEFSYM);
/////////////////////////////////////////////////////////
//
// GEMglViewport
//
/////////////////////////////////////////////////////////
// Constructor
//
spoutReceive :: spoutReceive	(t_symbol* s)
{
	w=512;
	h=512;
	texture=false;
	bInitialized	= false;
	spoutreceiver = GetSpout();        // Create a Spout receiver object

	bMemoryMode = false;
	if (strlen(s->s_name)!=0){s2=s;texture=true;}
	m_outTexInfo = outlet_new(this->x_obj, 0);

}
/////////////////////////////////////////////////////////
// Destructor
//
spoutReceive :: ~spoutReceive () {
	if(num != 0) glDeleteTextures(1, &num);
	spoutreceiver->ReleaseReceiver(); 
	delete spoutreceiver;
	spoutreceiver = NULL;

}

/////////////////////////////////////////////////////////
// Render
//
void spoutReceive :: render(GemState *state) {
	
	unsigned int width=500, height=500;
	if(!bInitialized) {
			sym[0]=NULL;
		if(spoutreceiver->CreateReceiver(sym, width, height, false)) {
			//bMemoryMode = spoutreceiver->GetMemoryShareMode();
			w=width;
			h=height;
			//initTexture();

			bInitialized = true;
			if (texture)setMess(s2);
			return; 
		} 
		else {
		}
	}

	if(bInitialized) {
	//initTexture();
		spoutreceiver->DrawSharedTexture();	
		
	}
}
			
void spoutReceive::initTexture()
{
if(num != 0) {
		glDeleteTextures(1, &num);
		num = 0;
	}

	glGenTextures(1, &num);
	glBindTexture(GL_TEXTURE_RECTANGLE, num);
	glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if(bMemoryMode)
		glTexImage2D(GL_TEXTURE_RECTANGLE, 0,  GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	else
		glTexImage2D(GL_TEXTURE_RECTANGLE, 0,  GL_RGBA,w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_RECTANGLE, 0);


}

/////////////////////////////////////////////////////////
// Variables
//

void spoutReceive :: setMess(t_symbol*indexed) {
 int index, nSenders;
 char* SenderName;
 int MaxSize = 64;
 unsigned int width, height;
 HANDLE hShareHandle;
 DWORD dwFormat;
 //nSenders = spoutreceiver->GetSenderCount();
 SenderName=indexed->s_name;
		spoutreceiver->GetSenderInfo(SenderName,
										width, height,
										hShareHandle, dwFormat);
		strcpy(sym,SenderName);
		//spoutreceiver->SetActiveSender(sym);
		spoutreceiver->ReleaseReceiver();
		spoutreceiver->CreateReceiver(sym, width, height, false);
		//bMemoryMode = spoutreceiver->GetMemoryShareMode();
			w=width;
			h=height;
			//initTexture();
			bInitialized = true;
}
void spoutReceive :: infoMess()
{
	post("spoutReceive v.1 by ArNO Courcelle, 01/2015 \n enjoy!");
}
/////////////////////////////////////////////////////////
// static member functions
//

void spoutReceive :: obj_setupCallback(t_class *classPtr) {
		class_addmethod(classPtr, reinterpret_cast<t_method>(&spoutReceive::setMessCallback),
					gensym("set"), A_SYMBOL, A_NULL);
		class_addmethod(classPtr, reinterpret_cast<t_method>(&spoutReceive::info),
					gensym("info"), A_NULL);
}

void spoutReceive :: setMessCallback(void *data, t_symbol*indexed)
{
	GetMyClass(data)->setMess(indexed);
}
void spoutReceive :: info (void* data)
{
	 GetMyClass(data)->infoMess();//post("spoutReceive v.1 by ArNO Courcelle, 01/2014 n/");
}
