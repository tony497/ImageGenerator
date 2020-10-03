#include "ofMain.h"
#include "ofApp.h"


//========================================================================
int main( ){

	/*
	TO DO:
		CHECK - log with openframework 
		- button with openframe work 
			- nombre of class modifiables 
			- choisir l image avec un system genre parcourir
		-Differents types d images 

	*/


	ofSetupOpenGL(800,600, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
