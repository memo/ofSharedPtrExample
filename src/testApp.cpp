#include "testApp.h"


//--------------------------------------------------------------
// an arbitrary class to hold some data and have some functionality
class MyObject {
public:
	MyObject(int _a, int _b, int _c, int _d) {
		a = _a; b = _b; c = _c; d = _d;
		printf("*** MyObject CREATED ***\n");
	}
    
    ~MyObject() {
		printf("*** MyObject DELETED ***\n");
	}
    
    void draw(int x, int y) {
        ofPushMatrix();
        ofTranslate(x, y);
        ofSetColor(0, 0, 0);
        ofRect(0, 0, 100, 100);
        ofSetColor(255, 0, 0);
        ofDrawBitmapString(ofToString(a, 2) + "\n" + ofToString(b, 2) + "\n" + ofToString(c, 2) + "\n"  + ofToString(d, 2) + "\n", 15, 30);
        ofPopMatrix();
    }
    
	// some arbitrary data
	int a, b, c, d;
};
//--------------------------------------------------------------


// since this is so ugly syntax, typedef it
typedef std::tr1::shared_ptr<MyObject> MyObjectSharedPtr;


// this will contain smart pointers
vector<MyObjectSharedPtr> smartPointers;

// this will contain normal pointers
vector<MyObject*> normalPointers;


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(255, 255, 255);
	
    // create a temporary object (with some random numbers) for the smart pointers
	MyObjectSharedPtr tempObject1(new MyObject(ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100)));

    // create a temporary object (with some random numbers) for the normal pointers
	MyObject* tempObject2(new MyObject(ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100)));
	
	for(int i=0; i < 5; i++) {
        // add the same smart pointer multiple times to the smart pointers array
        smartPointers.push_back(tempObject1);
        
        // add the same normal pointer multiple times to teh normal pointers array
        normalPointers.push_back(tempObject2);
	}
}


//--------------------------------------------------------------
void testApp::draw(){
	glColor4f(0, 0, 0, 1);
	
	ofDrawBitmapString("Press keys 1, 2, 3, 4, 5 to destroy the smart pointers pointing to the same object.\nEven though they point to the same object, the object remains in memory until all pointers have been destroyed.\nCheck the console to see when the object is actually deleted.", 20, 30);

	ofDrawBitmapString("Press keys q, w, e, r, t to destroy the normal pointers pointing to the same object.\nSince they point to the same object, as soon as you delete one, the others will go bonkers (and will probably crash).\nCheck the console to see when the object is actually deleted.", 20, 230);
	
	for(int i=0; i<smartPointers.size(); i++) {
        if(smartPointers[i]) smartPointers[i]->draw(i * 150 + 30, 70);
        if(normalPointers[i]) normalPointers[i]->draw(i * 150 + 30, 270);
	}
}


//--------------------------------------------------------------
void testApp::keyPressed (int key){
    switch(key) {
            // smart pointers
        case '1': smartPointers[0].reset(); break;
        case '2': smartPointers[1].reset(); break;
        case '3': smartPointers[2].reset(); break;
        case '4': smartPointers[3].reset(); break;
        case '5': smartPointers[4].reset(); break;
            
        case 'q': delete normalPointers[0]; break;
        case 'w': delete normalPointers[1]; break;
        case 'e': delete normalPointers[2]; break;
        case 'r': delete normalPointers[3]; break;
        case 't': delete normalPointers[4]; break;
    
    }
}

