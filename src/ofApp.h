#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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

		void setupGui();
		void drawStandardSpectrum(float* fftValues,  int fftSize);
		void drawSyncAmbientColor(float* fftValues, int fftSize);
		ofColor calculateColorTimeTransition(bool enableContinuousTranstion);
		ofColor calculateColorBy2D(float* fftValues);
		
		ofSoundPlayer player;
		bool isPlayingMusic = false;

		int fftSize = 512;

		int currentColorID = 0;
	    int colorPattern = 4;
		float lastColorChangeTime = 0;

		ofxPanel gui;
		ofParameter<bool> showStandardSpectrum;
		ofParameter<float> soundVolume;
		ofParameterGroup fftAdjustVariables;
		ofParameter<int> minValue;
		ofParameter<int> maxValue;
		ofParameterGroup colors;
		std::array<ofParameter<ofColor>, 4> colorPresets;
		ofParameter<int> colorTransitionPattern;
		ofParameter<float> colorChangeInterval;
		ofParameterGroup visualizationVariables;
		ofParameter<float> offsetValue;
		ofParameter<float> boostValue;
		ofParameter<int> visualizationChannel;

};
