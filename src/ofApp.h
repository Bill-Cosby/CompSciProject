#pragma once

#include "ofMain.h"

class button{
public:
 int position[2];
 ofImage imageName;


};

class ofApp : public ofBaseApp{
    ofImage menu;
    button button;
    int x=100,y=300;

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

};
