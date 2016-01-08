#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "vocabulary.h"
#include "ofxTimer.h"

enum States {
    WAITING,
    POSTULATING,
    DELIVERY
};

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
        bool isVowel(const char& c);
    
        void setupArduino(const int & version);
        void digitalPinChanged(const int & pinNum);
    
        std::string getFortune();
        void initiateSequence();
    
        void timerFinished(ofEventArgs& arg);
    
    private:
        bool		bSetupArduino;
        ofArduino	ard;
        string buttonState;
        ofVideoPlayer fortuneVideo;
        ofTrueTypeFont courier;
        std::string fortuneText;
        std::string outputText;
        const int letterShuffleCount = 8;
        int shuffleIndex;
        int letterIndex;
        int     opacity;
        States state;
        ofxTimer messageTimeout;
        float messageTimeoutAmt;
};
