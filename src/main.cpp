/***********************
 * Andy Wallace        *
 * copyright 2012      *
 ***********************/

#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 3000, 960, OF_WINDOW);
	ofRunApp(new testApp());
}
