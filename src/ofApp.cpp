#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
z.callPerlin();
/*screenPosition=testDungeon.mazeBegin;
playerPosition=screenPosition;*/
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  /*  ofSetColor(ofColor(0,0,0));
   for (int i=0;i<testDungeon.dungeon_grid.size();i++)
    {
        for (int j=0;j<testDungeon.dungeon_grid[0].size();j++)
       {
            if (testDungeon.dungeon_grid[i][j]==true)
            {
                ofRect(i*10-screenPosition.x,j*10-screenPosition.y,10,10);
            }
        }
    }
    ofSetColor(ofColor(255,0,0));
    ofCircle(400,300,5);*/
for(int x=0; x<1000; x++)
{
    for(int y=0; y<1000; y++)
    {
        ofSetColor(z.perlin_noise_sum[x][y]+150,z.perlin_noise_sum[x][y]+150,z.perlin_noise_sum[x][y]+150);
        ofCircle(x,y,1);
    }
}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   /* if (key== OF_KEY_LEFT)
    {
        screenPosition.x-=10;
    }
    else if (key== OF_KEY_RIGHT)
    {
        screenPosition.x+=10;
    }
    else if (key== OF_KEY_UP)
    {
        screenPosition.y-=10;
    }
    else if (key== OF_KEY_DOWN)
    {
        screenPosition.y+=10;
    }*/
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



