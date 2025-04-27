#include "ofApp.h"

void ofApp::setup() 
{
	ofSetFrameRate(60);

	for (int s = 0; s < NUM_SYSTEMS; s++) 
	{
		vector<Body> bodies;
		vector<ofVec2f> prev_pos;

		/*
		bodies.emplace_back(400, ofVec2f(ofGetWidth() / 2.0, (ofGetHeight() / 2.0) + 30.0), ofVec2f(0, 2), ofColor(0, 0, 255));
		bodies.emplace_back(400, ofVec2f((ofGetWidth() / 2.0) - 30.0, (ofGetHeight() / 2.0) - 30.0), ofVec2f(-2, -1), ofColor(0, 255, 0));
		bodies.emplace_back(400, ofVec2f((ofGetWidth() / 2.0) + 30.0, (ofGetHeight() / 2.0) - 30.0), ofVec2f(1, 0), ofColor(255, 0, 0));
		*/

		float scale = 200.0;
		float mass_scale = scale * scale;
		float velocity_scale = sqrt(scale);

		bodies.emplace_back(
			1 * mass_scale,
			ofVec2f(ofGetWidth() / 2.0 + 0.97000436 * scale, ofGetHeight() / 2.0 - 0.24308753 * scale),
			ofVec2f(0.93240737 / 2.0 * velocity_scale, 0.86473146 / 2.0 * velocity_scale),
			ofColor(0, 0, 255)
		);

		bodies.emplace_back(
			1 * mass_scale,
			ofVec2f(ofGetWidth() / 2.0 - 0.97000436 * scale, ofGetHeight() / 2.0 + 0.24308753 * scale),
			ofVec2f(0.93240737 / 2.0 * velocity_scale, 0.86473146 / 2.0 * velocity_scale),
			ofColor(255, 0, 0)
		);

		bodies.emplace_back(
			1 * mass_scale,
			ofVec2f(ofGetWidth() / 2.0, ofGetHeight() / 2.0),
			ofVec2f(-0.93240737 * velocity_scale, -0.86473146 * velocity_scale),
			ofColor(0, 255, 0)
		);


		for (auto& b : bodies) 
		{
			ofVec2f pos = b.get_position();
			ofVec2f vel = b.get_velocity();
			b.set_prev_position(pos - vel * dt);
		}

		systems.push_back(bodies);
		prev_positions.push_back({});
	}
}

void ofApp::compute_forces(vector<Body>& bodies) 
{
	for (auto& b : bodies) b.set_acceleration({ 0.0, 0.0 });

	for (int i = 0; i < bodies.size(); i++) 
	{
		for (int j = i + 1; j < bodies.size(); ++j) 
		{
			ofVec2f dir = bodies[j].get_position() - bodies[i].get_position();
			float dist_sq = dir.lengthSquared() + 1e-5f;
			float force_mag = G * bodies[i].get_mass() * bodies[j].get_mass() / dist_sq;
			ofVec2f force = dir.getNormalized() * force_mag;

			bodies[i].apply_force(force);
			bodies[j].apply_force(-force);
		}
	}
}

void ofApp::update() 
{
	if (current_step >= num_steps) return;

	for (int s = 0; s < NUM_SYSTEMS; ++s) 
	{
		auto& bodies = systems[s];

		compute_forces(bodies);

		for (auto& body : bodies) 
		{
			body.verlet_update(dt, body.get_prev_position());
		}
	}

	current_step++;
}

void ofApp::draw() 
{
	ofBackground(0);

	for (int s = 0; s < NUM_SYSTEMS; s++) 
	{
		for (auto& b : systems[s]) 
		{
			ofSetColor(b.get_color());
			ofDrawCircle(b.get_position(), 15);
		}
	}
}
