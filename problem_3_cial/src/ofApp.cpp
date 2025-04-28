#include "ofApp.h"

void ofApp::setup() 
{
	ofSetFrameRate(60);

	vector<float> offsets = { 1.0, 1.5, 2.0 };

	for (int s = 0; s < systems_num; s++)
	{
		vector<Body> bodies;

		float offset = offsets[s];
		
		bodies.emplace_back(1000, ofVec2f((ofGetWidth() / 2.0) - offset - 100.0, (ofGetHeight() / 2.0) - 100.0), ofVec2f(0.0, 1.0), ofColor(0, 0, 255));
		bodies.emplace_back(1000, ofVec2f((ofGetWidth() / 2.0) + offset - 100.0, (ofGetHeight() / 2.0) + 100.0), ofVec2f(0.0, -1.0), ofColor(0, 255, 0));
		bodies.emplace_back(1000, ofVec2f((ofGetWidth() / 2.0) + 100.0, (ofGetHeight() / 2.0)), ofVec2f(-1.0, 0.0), ofColor(255, 0, 0));
		
		/*
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
		);*/

		for (auto& b : bodies) 
		{
			ofVec2f pos = b.get_position();
			ofVec2f vel = b.get_velocity();
			b.set_prev_position(pos - vel * dt);
		}

		systems.push_back(bodies);
		distances.push_back(vector<float>());
	}
}

void ofApp::gravity_force(vector<Body>& bodies) 
{
	for (auto& b : bodies) b.set_acceleration({ 0.0, 0.0 });

	for (int i = 0; i < bodies.size(); i++) 
	{
		for (int j = i + 1; j < bodies.size(); j++) 
		{
			ofVec2f r = bodies[j].get_position() - bodies[i].get_position();
			float dist_squared = r.lengthSquared() + 100;
			float force_mag = G * bodies[i].get_mass() * bodies[j].get_mass() / dist_squared;
			ofVec2f force = r.getNormalized() * force_mag;

			bodies[i].apply_force(force);
			bodies[j].apply_force(-force);
		}
	}
}

void ofApp::update() 
{
	if (current_step >= num_steps) return;

	for (int s = 0; s < systems_num; ++s)
	{
		auto& bodies = systems[s];

		gravity_force(bodies);

		for (auto& body : bodies) 
		{
			body.verlet_update(dt, body.get_prev_position());
		}


		float avg_distance = 0.0;
		int count = 0;

		for (int i = 0; i < bodies.size(); i++)
		{
			for (int j = i + 1; j < bodies.size(); j++)
			{
				avg_distance += (bodies[i].get_position() - bodies[j].get_position()).length();
				count++;
			}
		}
		avg_distance /= count;
		distances[s].push_back(avg_distance);
	}

	current_step++;
}

void ofApp::draw() 
{
	ofBackground(0);

	for (auto& b : systems[0])
	{
		ofSetColor(b.get_color());
		ofDrawCircle(b.get_position(), 20);
	}
}

void ofApp::exit()
{
	ofFile file("distances.csv", ofFile::WriteOnly);

	string header = "step";
	for (int s = 0; s < systems_num; s++)
	{
		header += ",system_" + ofToString(s + 1);
	}
	file << header << "\n";

	for (int step = 0; step < distances[0].size(); step++)
	{
		string line = ofToString(step);
		for (int s = 0; s < systems_num; s++)
		{
			line += "," + ofToString(distances[s][step]);
		}
		file << line << "\n";
	}

	file.close();
}
