#pragma once

#include "ofMain.h"
#include "body.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	vector<vector<Body>> systems;
	vector<vector<float>> distances;

	const int systems_num = 3;
	float G = 0.5;
	const float dt = 0.5f;

	const int num_steps = 3000;
	int current_step = 0;

	void gravity_force(vector<Body>& bodies);
};
