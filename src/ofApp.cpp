#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    buttonState = "digital pin:";
    
    // replace the string below with the serial port for your Arduino board
    // you can get this from the Arduino application or via command line
    // for OSX, in your terminal type "ls /dev/tty.*" to get a list of serial devices
    ard.connect("/dev/tty.usbmodem1411", 57600);
    
    // listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
    
    //message setup
    courier.load("ufonts.com_courier.ttf", 16);
    courier.setLineHeight(16 * 1.4);
    shuffleIndex = 0;
    letterIndex = 0;
    //10 seconds
    messageTimeoutAmt = 5000;
    
    //attach a listener for the timer
    ofAddListener(messageTimeout.TIMER_REACHED, this, &ofApp::timerFinished);
    
    //video setup
    fortuneVideo.load("movies/sg_animation.mov");
    fortuneVideo.setLoopState(OF_LOOP_NONE);
    opacity = 0;
    
    state = WAITING;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(ard.isInitialized()){
        ard.update();
    }
    if(fortuneVideo.isLoaded() && fortuneVideo.isInitialized()){
        fortuneVideo.update();
    }
    if(fortuneVideo.getIsMovieDone() && state != DELIVERY){
        fortuneVideo.setPaused(true);
        state = DELIVERY;
        messageTimeout.setup(messageTimeoutAmt, false);
    }
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    // set pin D2 to digital input
    ard.sendDigitalPinMode(2, ARD_INPUT);
    
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    if(state == WAITING){
        courier.drawString("Touch the screen and\n reveal your future", ofGetWidth()/2-100, ofGetHeight()/2 - 10);
    }
    if(state == POSTULATING && fortuneVideo.isLoaded() && fortuneVideo.getTexture().isAllocated()){
        fortuneVideo.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    if(state == DELIVERY){
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, opacity);
//        ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
        fortuneVideo.draw(0, 0, ofGetWidth(), ofGetHeight());
                ofSetColor(255, 255, 255, 255.0);
        courier.drawString(fortuneText, ofGetWidth()/2 - 175, ofGetHeight()/2 - 10);

        if(opacity > 0){
            opacity -= 5;
        }
    }
}

// digital pin event handler, called whenever a digital pin value has changed
// note: if an analog pin has been set as a digital pin, it will be handled
// by the digitalPinChanged function rather than the analogPinChanged function.

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pinNum) {
    // do something with the digital input. here we're simply going to print the pin number and
    // value to the screen each time it changes
//    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
    if(ard.getDigital(pinNum) == 1){
        fortuneVideo.play();
        cout << "Button Depressed" << endl;
    }
}

bool ofApp::isVowel(const char &c){
    return(c == 'a' || c == 'e' || c == 'i' || c == 'o' || 'c' == 'u' || c == 'y');
}

std::string ofApp::getFortune(){
    auto noun = vocabulary::nouns[rand() % vocabulary::nouns.size()];
    auto verb = vocabulary::verbs[rand() % vocabulary::verbs.size()];
    auto adjective = vocabulary::adjectives[rand() % vocabulary::adjectives.size()];
    auto luckyNum = rand() % 255;
    
    // the stars have spoken
    // you will <verb> an <adjective> <noun>
    stringstream ss;
    ss << "The stars have spoken." << endl;
    ss << "You will " << verb << (isVowel(adjective[0])? " an " : " a ") << adjective << " " << noun << "." << endl;
    ss << "Your lucky number is " << luckyNum << ".";
    
    return ss.str();
}

void ofApp::initiateSequence(){
    messageTimeout.pauseTimer();
    opacity = 255;
    state = POSTULATING;
    if(!fortuneVideo.isPlaying()){
        //        fortuneVideo.setPosition(0.0);
        fortuneVideo.play();
    }
    fortuneText = getFortune();
}

void ofApp::timerFinished(ofEventArgs &args){
    cout << "finished" << endl;
    state = WAITING;
    fortuneVideo.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    initiateSequence();
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
    initiateSequence();
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
