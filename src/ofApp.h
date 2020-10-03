#pragma once

#include "ofMain.h"
#include "ofLog.h"
#include "ofImage.h"
#include "ofxGui.h"
//#include "ofxGui/src/ofxBaseGui.h"
#include "algoComputation.h"



class ofApp : public ofBaseApp{

	//Images
	ofImage image;
	ofPixels imageTab;

	//Gui
	//ofxPanel gui;
	//ofParameter<int> cluster;
	//ofxIntSlider clusterSlider;

	public:
		void setup();
		void loadImage();
		void update();
		void draw();

		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
