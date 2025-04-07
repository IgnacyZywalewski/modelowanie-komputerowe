#include "ofApp.h"

void ofApp::setup() 
{
	ofSetFrameRate(60);

	for (int s = 0; s < NUM_SYSTEMS; s++) 
	{
		vector<Body> bodies;
		vector<ofVec2f> prev_pos;

		bodies.emplace_back(400, ofVec2f(ofGetWidth() / 2.0, (ofGetHeight() / 2.0) + 30.0), ofVec2f(0, 2), ofColor(0, 0, 255));
		bodies.emplace_back(400, ofVec2f((ofGetWidth() / 2.0) - 30.0, (ofGetHeight() / 2.0) - 30.0), ofVec2f(-2, -1), ofColor(0, 255, 0));
		bodies.emplace_back(400, ofVec2f((ofGetWidth() / 2.0) + 30.0, (ofGetHeight() / 2.0) - 30.0), ofVec2f(1, 0), ofColor(255, 0, 0));

		for (auto& b : bodies) 
		{
			ofVec2f pos = b.get_position();
			ofVec2f vel = b.get_velocity();
			b.set_prev_position(pos - vel * dt);
		}

		systems.push_back(bodies);
		prev_positions.push_back({});
		avg_distances.push_back({});
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

float ofApp::compute_average_distance(const vector<Body>& bodies) 
{
	float total = 0;
	int count = 0;
	for (int i = 0; i < bodies.size(); ++i) 
	{
		for (int j = i + 1; j < bodies.size(); ++j) 
		{
			total += (bodies[i].get_position() - bodies[j].get_position()).length();
			count++;
		}
	}
	return total / count;
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

		avg_distances[s].push_back(compute_average_distance(bodies));
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
