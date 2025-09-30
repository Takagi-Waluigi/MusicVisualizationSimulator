#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	setupGui();

	if (!player.loadSound("tele.mp3")) {
		cout << "[ERROR] Music load is failed";
		return;
	}
	player.play();
	player.setLoop(true);
	

	ofBackground(0);
}

void ofApp::setupGui() {
	//Setup each paramters
	showStandardSpectrum.set("show std spectrum", true);
	soundVolume.set("sound volume", 0.2, 0.0, 1.0);
	//fft variables
	fftAdjustVariables.setName("fft adjust variables");
	minValue.set("min value", 0, 0, fftSize);
	maxValue.set("max value", fftSize, 0, fftSize);
	fftAdjustVariables.add(minValue);
	fftAdjustVariables.add(maxValue);
	//preset 4colors
	colors.setName("preset colors");
	colorPresets[0].set("color 1", ofColor(255, 0, 0));
	colorPresets[1].set("color 1", ofColor(0, 255, 0));
	colorPresets[2].set("color 1", ofColor(0, 0, 255));
	colorPresets[3].set("color 1", ofColor(255, 255, 0));
	colorChangeInterval.set("interval", 1.0, 0.0001, 10.0); //min value cannot be Zero.
	for (int i = 0; i < colorPresets.size(); i++) colors.add(colorPresets[i]);
	colors.add(colorChangeInterval);
	//visualization variables
	visualizationVariables.setName("visualization variables");
	offsetValue.set("offset", 25, 0, 255);
	boostValue.set("boost", 128, 0, 500);
	visualizationVariables.add(boostValue);
	visualizationVariables.add(offsetValue);

	//Add each parameters to gui
	gui.setup();
	gui.add(showStandardSpectrum);
	gui.add(soundVolume);
	gui.add(fftAdjustVariables);
	gui.add(colors);
	gui.add(visualizationVariables);
}

//--------------------------------------------------------------
void ofApp::update(){
	//Player settings
	player.setPaused(isPlayingMusic);
	player.setVolume(soundVolume);
}

//--------------------------------------------------------------
void ofApp::draw(){
	float* fftValues = ofSoundGetSpectrum(fftSize);

	if(showStandardSpectrum)  drawStandardSpectrum(fftValues, fftSize);

	drawSyncAmbientColor(fftValues, fftSize);

	gui.draw();
}

void ofApp::drawSyncAmbientColor(float* fftValues, int fftSize) {
	float maxValueFromFft = 0;
	for (int i = minValue; i < maxValue; i++) {
		if (maxValueFromFft < fftValues[i]) maxValueFromFft = fftValues[i];
	}

	if(ofGetFrameNum() % 30 == 0) cout << "{INFO] value of max value of fft is " << maxValueFromFft << endl;

	int rectH = 10;
	//Draw Blacked Background
	ofSetColor(0);
	ofDrawRectangle(0, ofGetHeight() / 2 - rectH * 5.0, ofGetWidth(), rectH * 2.0 * 5.0);
	//Set Ambient Color
	ofSetColor( ofColor::fromHsb(calculateColor().getHue(), 255, offsetValue + boostValue * maxValueFromFft));
	ofDrawRectangle(0, ofGetHeight() / 2 - rectH / 2, ofGetWidth(), rectH);
}

ofColor ofApp::calculateColor() {
	float duration = ofGetElapsedTimef() - lastColorChangeTime;

	if (duration > colorChangeInterval) {
		currentColorID++;
		currentColorID = currentColorID % colorPattern;
		lastColorChangeTime = ofGetElapsedTimef();
		cout << "[INFO] color change" << endl;
	}

	ofColor currentColor = colorPresets[currentColorID];

	int nextColorID = (currentColorID + 1) % colorPattern;
	ofColor nextColor = colorPresets[nextColorID];

	return  ofColor(
		ofLerp(currentColor.r, nextColor.r, duration / colorChangeInterval * 0.75),
		ofLerp(currentColor.g, nextColor.g, duration / colorChangeInterval * 0.75),
		ofLerp(currentColor.b, nextColor.b, duration / colorChangeInterval * 0.75)
	);
}

void  ofApp::drawStandardSpectrum(float* fftValues, int fftSize) {
	ofSetColor(128, 128);
	ofDrawRectangle(0, 0, ofGetWidth() * minValue / fftSize, ofGetHeight());
	ofDrawRectangle(ofGetWidth() * maxValue / fftSize, 0, ofGetWidth() * (1 - maxValue / fftSize), ofGetHeight());

	for (int i = minValue; i < maxValue; i++) {
		float x = ofMap(i, 0, fftSize - 1, 0, ofGetWidth());
		float y = ofMap(fftValues[i], 0.0, 1.5, ofGetHeight(), 0.0);

		float width = float(ofGetWidth()) / float(fftSize) + 1;
		ofSetColor(255);
		ofDrawRectangle(x, y, width, ofGetHeight() - y);
	}

	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ')
	{
		cout << "[INFO] playing status has been changed" << endl;
		isPlayingMusic = !isPlayingMusic;
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
