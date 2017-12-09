#include "ofMain.h"
#include "testApp.hpp"

int main() {
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new testApp());
}
