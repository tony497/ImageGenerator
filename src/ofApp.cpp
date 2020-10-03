#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
	//Setup Log level
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofLogToConsole();

	//Gui
	//gui.setup();
	//cluster.set("cluster", 3);
	//gui.add(clusterSlider.setup(cluster,1,25));
	//gui.add(clusterSlider.setup("cluster", 3, 1, 30));

	ofLogNotice() << "Setup:";
	int positionWindowsX = 300, positionWindowsY = 300;
	ofSetWindowPosition(positionWindowsX, positionWindowsY);
	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
	loadImage();
	//ofSetWindowShape(image.getWidth(), image.getHeight());


	
	//Resize for debug 
		int debugHeight = 800, debugWidth = 800;
		image.resize(debugHeight, debugWidth);
		ofSetWindowShape(debugHeight, debugWidth);

		//Everything from here should go in a new function only activated once you pressed a button

		algoComputation c(image.getPixels(), debugWidth,debugHeight);
		
		ofPixels resultPixels = c.getImageTabResult();

		//Checking verification
		ofLogVerbose() << "width = " << resultPixels.getWidth();
		ofLogVerbose() << "height = " << resultPixels.getHeight();
		ofLogVerbose() << "nbrchannel = " << resultPixels.getNumChannels();


		ofImage resultImage;
		resultImage.setFromPixels(resultPixels.getData(), debugHeight, debugWidth,ofImageType::OF_IMAGE_COLOR, true);
		ofLogVerbose() << "finsih, just have to show now ... ";
		image = resultImage;
}

void ofApp::loadImage()
{
	image.load("images/antoine.jpg");

	if (image.bAllocated())
		ofLogNotice() << "Image is loaded succesfully";
	else
		ofLogError() << "Image isn't loaded succesfully";

	int imageInitialWidth = 0;
	int imageInitialHeight = 0;
	if (image.getHeight() > ofGetHeight())
	{
		ofLogNotice() << " image.getHeight() > ofGetHeight() ";

		double ratio = image.getWidth() / image.getHeight();
		int newHeight = ofGetHeight();
		double newWidth = newHeight * ratio;

		image.resize(newWidth, newHeight);
		ofLogVerbose() << "height = " << newHeight << " width " << newWidth;
		
	}
	if (image.getWidth() > ofGetWidth())
	{
		ofLogNotice() << " image.getWidth() > ofGetWidth() ";
		double ratio = image.getWidth() / image.getHeight();
		int newWidth = ofGetWidth();
		double newHeight = newWidth / ratio;

		image.resize(newWidth, static_cast<int>(newHeight));
		ofLogVerbose() << "height = " << newHeight << " width " << newWidth;

	}

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	image.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}