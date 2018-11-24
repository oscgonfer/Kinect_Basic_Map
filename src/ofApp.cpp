#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);

	// enable depth->video image calibration
    kinect.setRegistration(true);
    
    kinect.init();
    //kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();        // opens first available kinect
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    
    nearThreshold = 185;
    farThreshold = 55;
    
    bThreshWithOpenCV = true;
    
    ofSetFrameRate(60);

    // zero the KINECT - tilt on startup
    angle = 0;
    kinect.setCameraTiltAngle(angle);

    colorR = 255;
    colorG = 255;
    colorB = 255;
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(100, 100, 100);
    
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(kinect.getDepthPixels());
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold,false);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        } else {
            
            // or we do it ourselves - show people how they can work with the pixels
            ofPixels & pix = grayImage.getPixels();
            int numPixels = pix.size();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
        }
        
        // update the cv images
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/2 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayImage, minArea, (kinect.width*kinect.height)/2, 20, false);
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(colorR, colorG, colorB);
    
    // draw from the live kinect
    // depth IR
    drawingAreaX = 350;
    drawingAreaY = 250;
    drawingPositionX = 420;
    drawingPositionY = 270;
    
    
    // RGB
    drawingAreaX = ofGetWidth();
    drawingAreaY = ofGetHeight();
    drawingPositionX = 0;
    drawingPositionY = 0;
    kinect.drawDepth(drawingPositionX, drawingPositionY, drawingAreaX, drawingAreaY);
    
    // kinect.draw(drawingPositionX, 10, drawingAreaX, drawingAreaY);
    // contourFinder.draw(drawingPositionX, 10, drawingAreaX, drawingAreaY);
    // depth contour
    // grayImage.draw(10, drawingPositionY, drawingAreaX, drawingAreaY);
    // contourFinder.draw(10, drawingPositionY, drawingAreaX, drawingAreaY);
    
    // ofColor backC(150, 150, 150);
    // ofRectangle backR(drawingPositionX,drawingPositionY, drawingAreaX, drawingAreaY);
    // ofSetColor(backC);
    // ofDrawRectangle(backR);
}

void ofApp::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;

        case 'r':
        	colorR++;
        	if (colorR > 255) colorR = 255;
        	break;

        case 't':
        	colorR--;
        	if (colorR < 0) colorR = 0;
        	break;

        case 'g':
        	colorG++;
        	if (colorG > 255) colorG = 255;
        	break;

        case 'h':
        	colorG--;
        	if (colorG < 0) colorG = 0;
        	break;

        case 'b':
        	colorB++;
        	if (colorB > 255) colorB = 255;
        	break;

        case 'n':
        	colorB--;
        	if (colorB < 0) colorB = 0;
        	break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
