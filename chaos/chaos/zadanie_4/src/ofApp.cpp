#include "ofApp.h"

void ofApp::setup() {
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);

    origin.set(ofGetWidth() / 2, 150);

    for (int i = 0; i < num_pendulums; i++) {
        Pendulum p;
        p.l1 = 200;
        p.l2 = 200;
        p.m1 = 10;
        p.m2 = 10;
        p.a1 = PI / 2 + ofRandom(-0.001, 0.001);
        p.a2 = PI / 2 + ofRandom(-0.001, 0.001);
        p.a1_v = p.a2_v = 0;

        p.color = ofColor::fromHsb(ofMap(i, 0, num_pendulums, 0, 255), 200, 255);

        pendulums.push_back(p);
    }
}

void ofApp::update() {
    for (auto& p : pendulums) {
        float g = 9.81;

        float num1 = -g * (2 * p.m1 + p.m2) * sin(p.a1);
        float num2 = -p.m2 * g * sin(p.a1 - 2 * p.a2);
        float num3 = -2 * sin(p.a1 - p.a2) * p.m2;
        float num4 = p.a2_v * p.a2_v * p.l2 + p.a1_v * p.a1_v * p.l1 * cos(p.a1 - p.a2);
        float den = p.l1 * (2 * p.m1 + p.m2 - p.m2 * cos(2 * p.a1 - 2 * p.a2));
        p.a1_a = (num1 + num2 + num3 * num4) / den;

        num1 = 2 * sin(p.a1 - p.a2);
        num2 = (p.a1_v * p.a1_v * p.l1 * (p.m1 + p.m2));
        num3 = g * (p.m1 + p.m2) * cos(p.a1);
        num4 = p.a2_v * p.a2_v * p.l2 * p.m2 * cos(p.a1 - p.a2);
        den = p.l2 * (2 * p.m1 + p.m2 - p.m2 * cos(2 * p.a1 - 2 * p.a2));
        p.a2_a = (num1 * (num2 + num3 + num4)) / den;

        p.a1_v += p.a1_a * dt;
        p.a2_v += p.a2_a * dt;
        p.a1 += p.a1_v * dt;
        p.a2 += p.a2_v * dt;


        float x1 = origin.x + p.l1 * sin(p.a1);
        float y1 = origin.y + p.l1 * cos(p.a1);
        float x2 = x1 + p.l2 * sin(p.a2);
        float y2 = y1 + p.l2 * cos(p.a2);


        if (&p == &pendulums[0]) {
            data_1.push_back({ p.a2, p.a2_v });
        }
        else if (&p == &pendulums[1]) {
            data_2.push_back({ p.a2, p.a2_v });
        }
    }
}

void ofApp::draw() {
    for (const auto& p : pendulums) {
        float x1 = origin.x + p.l1 * sin(p.a1);
        float y1 = origin.y + p.l1 * cos(p.a1);
        float x2 = x1 + p.l2 * sin(p.a2);
        float y2 = y1 + p.l2 * cos(p.a2);

        ofSetLineWidth(2);
        ofSetColor(p.color);
        ofDrawLine(origin.x, origin.y, x1, y1);
        ofDrawLine(x1, y1, x2, y2);
        ofDrawCircle(x1, y1, 5);
        ofDrawCircle(x2, y2, 5);
    }
}

void ofApp::exit() {
    std::filesystem::create_directories("../../data/zadanie_4/");

    ofstream file1("../../data/zadanie_4/zadanie_4_1.csv");
    file1 << "a2,a2_v\n";
    for (auto& [a, v] : data_1)
    {
        file1 << a << "," << v << "\n";
    }
    file1.close();

    ofstream file2("../../data/zadanie_4/zadanie_4_2.csv");
    file2 << "a2,a2_v\n";
    for (auto& [a, v] : data_2)
    {
        file2 << a << "," << v << "\n";
    }
    file2.close();
}