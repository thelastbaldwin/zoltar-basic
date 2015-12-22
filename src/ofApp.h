#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "vocabulary.h"

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
    
        void setupArduino(const int & version);
        void digitalPinChanged(const int & pinNum);
    
        std::string getFortune();
private:
        bool		bSetupArduino;
        ofArduino	ard;
        string buttonState;
        ofVideoPlayer fortuneVideo;
};
