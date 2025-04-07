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
	vector<vector<float>> avg_distances;

	const int NUM_SYSTEMS = 3;
	const float G = 1.0f;
	const float dt = 0.1f;
	const int num_steps = 10000;
	int current_step = 0;

	void compute_forces(vector<Body>& bodies);
	float compute_average_distance(const vector<Body>& bodies);

};
