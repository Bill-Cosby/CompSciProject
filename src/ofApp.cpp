
#include "ofApp.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

//--------------------------------------------------------------
void ofApp::setup(){
callPerlin();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
for(int x=0; x<1000; x++)
{
    for(int y=0; y<1000; y++)
    {   ofSetColor(PerlinNoise.perlin_noise_sum[x][y]+400,PerlinNoise.perlin_noise_sum[x][y]+400,150*PerlinNoise.perlin_noise_sum[x][y]+400);
        ofCircle(x,y,1);
    }
}
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



