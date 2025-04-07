#pragma once
#include "ofMain.h"

class Body
{
public:
	Body(float m, ofVec2f pos, ofVec2f vel, ofColor col)
		: mass(m), position(pos), velocity(vel), acceleration(ofVec2f(0, 0)), color(col) {
	}

	float get_mass() { return mass; }
	ofVec2f get_position() const { return position; };
	ofVec2f get_prev_position() { return prev_position; }
	ofVec2f get_velocity() { return velocity; };
	ofVec2f get_acceleration() { return acceleration; }
	ofColor get_color() { return color; }

	void set_prev_position(ofVec2f pos) { prev_position = pos; }
	void set_acceleration(ofVec2f new_acc) { acceleration = new_acc; }

	void apply_force(ofVec2f force) {
		acceleration += force / mass;
	}

	void verlet_update(float dt, ofVec2f prev_pos) {
		ofVec2f new_pos = 2 * position - prev_pos + acceleration * dt * dt;
		velocity = (new_pos - prev_pos) / (2 * dt);
		prev_position = position;
		position = new_pos;
		acceleration.set(0);
	}

private:
	float mass;
	ofVec2f position;
	ofVec2f prev_position;
	ofVec2f velocity;
	ofVec2f acceleration;
	ofColor color;
};