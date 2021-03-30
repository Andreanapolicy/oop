#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef std::vector<int> SpeedInterval;
typedef std::map<int, SpeedInterval> SpeedIntervalForGears;

enum class Direction {
	FORWARD,
	BACKWARD,
	ON_THE_SPOT,
};