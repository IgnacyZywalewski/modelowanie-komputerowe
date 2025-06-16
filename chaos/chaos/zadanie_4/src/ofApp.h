#pragma once
#include "ofMain.h"

struct Pendulum {
    float l1, l2;
    float m1, m2;
    float a1, a2;
    float a1_v, a2_v;
    float a1_a, a2_a;
    ofColor color;
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void exit();

    std::vector<Pendulum> pendulums;
    int num_pendulums = 100;

    ofPoint origin;
    float dt = 0.1;

    std::vector<std::pair<float, float>> data_1;
    std::vector<std::pair<float, float>> data_2;
};
