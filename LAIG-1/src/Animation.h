#pragma once

#include <vector>
#include <array>
#include <ctime>

using namespace std;

class Animation
{
protected:
	unsigned long startTime;
public:
	string nodeID;
	Animation(string nodeID);
	void init(float timestamp = clock());
};

class LinearAnimation : public Animation
{
	vector<array<float, 3>> controlPoints;
	unsigned int currentControlPoint;
	array<float, 3> currentPos;
	float span, lastTimestamp;
public:
	LinearAnimation(string nodeID, float span);
	void addControlPoint(array<float, 3>);
	void init(float timestamp = clock());
	void update(float timestamp = clock());
	void draw();
};