#pragma once

#include "ofMain.h"
#include "body.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	vector<vector<Body>> systems;
	vector<vector<ofVec2f>> prev_positions;

	const int NUM_SYSTEMS = 3;
	const float G = 1.0f;	
	const float dt = 1.0f;

	const int num_steps = 10000;
	int current_step = 0;

	void compute_forces(vector<Body>& bodies);
};
