#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxKinect kinect;

		ofxCvColorImage colorImg;
    
	    ofxCvGrayscaleImage grayImage; // grayscale depth image
	    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	    
	    ofxCvContourFinder contourFinder;
	    
	    bool bThreshWithOpenCV;
	    
	    int nearThreshold;
	    int farThreshold;

	    int drawingAreaX;
	    int drawingAreaY;
	    int drawingPositionX;
	    int drawingPositionY;

        int minArea = 300;
    	int angle;
    	int colorR;
    	int colorG;
    	int colorB;

};
