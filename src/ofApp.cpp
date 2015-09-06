#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetColor(ofColor(0,0,255));
    for (int i=0;i<test.dungeon_grid.size();i++)
    {
        for (int j=0;j<test.dungeon_grid[0].size();i++)
        {
            if (test.dungeon_grid[i][j]==true)
            {
                tiles.push_back(ofRectangle(i*10,j*10,10,10));
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i=0;i<tiles.size();i++)
    {
        tiles[i];
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
