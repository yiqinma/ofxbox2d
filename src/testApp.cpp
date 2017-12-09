//
//  testApp.cpp
//  minifinal
//
//  Created by MaYiqin on 6/12/17.
//
//

#include "testApp.hpp"

//--------------------------------------------------------------
void testApp::setup() {
    //image.loadImage("mountain.png");
    
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    bMouseForce = false;

    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createGround();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    edgeLine.addVertex(ofGetWidth()-ofGetWidth()/64,ofGetHeight());
    edgeLine.addVertex(ofGetWidth()-ofGetWidth()/32,3.8*ofGetHeight()/4);
    edgeLine.addVertex(ofGetWidth()-ofGetWidth()/16,ofGetHeight());
    edgeLine.addVertex(ofGetWidth()-ofGetWidth()/8,3.5*ofGetHeight()/4);
    edgeLine.addVertex(3*ofGetWidth()/4,ofGetHeight());
    edgeLine.addVertex(ofGetWidth()/2,3*ofGetHeight()/4);
    edgeLine.addVertex(ofGetWidth()/4,ofGetHeight());
    edgeLine.addVertex(ofGetWidth()/8,3.5*ofGetHeight()/4);
    edgeLine.addVertex(ofGetWidth()/16,ofGetHeight());
    edgeLine.addVertex(ofGetWidth()/32,3.8*ofGetHeight()/4);
    edgeLine.addVertex(ofGetWidth()/64,ofGetHeight());
    
    edgeLine.setPhysics(0.0, 0.5, 0.5);
    edgeLine.create(box2d.getWorld());
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    serial.setup(0, 9600);
    data = 0;
}

//--------------------------------------------------------------
void testApp::update() {
    
    box2d.update();
    
    // remove shapes offscreen
    ofRemove(boxes, ofxBox2dBaseShape::shouldRemoveOffScreen);
    ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
    if(data == 49){
        int t = int(ofRandom(500))%3;
        if(t == 0){
            float r = ofRandom(4, 20);        // a random radius 4px - 20px
            circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
            circles.back().get()->setPhysics(3.0, 0.53, 0.1);
            circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
        }else if(t == 1){
            float w = ofRandom(4, 20);
            float h = ofRandom(4, 20);
            boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
            boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
            boxes.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
        }
    }
    //int t = int(serial.readByte());
    if(serial.available()){
        data = serial.readByte();
    }
    printf("%d \n",data);
}


//--------------------------------------------------------------
void testApp::draw() {
    
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(0x90d4e3);
        circles[i].get()->draw();
    }
    
    for(int i=0; i<boxes.size(); i++) {
        ofFill();
        ofSetHexColor(0xe63b8b);
        boxes[i].get()->draw();
    }
    
    ofNoFill();
    ofSetHexColor(0x444342);
    if(drawing.size()==0) {
        edgeLine.updateShape();
        edgeLine.draw();
    }
    else drawing.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    
    if(key == 'f') bMouseForce = !bMouseForce;
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button ) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}



