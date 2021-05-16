#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int span = 15;
	int draw_param = ofRandom(1000);
	vector<glm::vec2> location_list = { glm::vec2(-220, -220), glm::vec2(0, -220), glm::vec2(220, -220),
	glm::vec2(-220, 0), glm::vec2(220, 0) ,
	glm::vec2(-220, 220), glm::vec2(0, 220), glm::vec2(220, 220) };
	vector<float> rotate_list = { 180, 180, 270, 90, 270, 90, 0, 0 };

	for (int i = 0; i < location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(location_list[i]);
		ofRotateZ(rotate_list[i]);

		for (auto x = -90; x <= 90; x += span) {

			for (int y = -90; y <= 90; y += span) {

				auto draw = ofNoise(draw_param, location_list[i].x + x * 0.0035 + ofGetFrameNum() * 0.01, location_list[i].y + y * 0.0035);
				if (draw < 0.45) continue;
				
				ofPushMatrix();
				ofTranslate(x, y, 0);

				auto noise_value = ofNoise(location_list[i].x + x * 0.005 + ofGetFrameNum() * 0.01, location_list[i].y + y * 0.005);
				auto start_param = noise_value < 0.5 ? 0 : 25;

				auto start = this->make_point(span, start_param);
				auto end = this->make_point(span, start_param + 50);

				ofDrawLine(start, end);
				ofDrawCircle(start, 4);
				ofDrawCircle(end, 4);

				ofPopMatrix();
			}
		}

		ofNoFill();
		ofDrawRectangle(glm::vec2(), 180 + 15, 180 + 15);
		ofFill();
		
		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}