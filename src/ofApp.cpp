#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    menu.loadImage("menu420.png");
    button.loadImage("button420.png");
    button2.loadImage("button420.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    if (mouseX>100 and mouseX< 300 and mouseY>300 and mouseY<400)
    {
        if (x<=150)
        {
            x++;
        }
    }
    else
    {
        if (x>=100)
        {
            x--;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
menu.draw(0,0);
button.draw(x,y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
