#pragma once

#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<int> SpeedInterval;
typedef std::map<int, SpeedInterval> SpeedIntervalForGears;

enum class Direction
{
	FORWARD,
	BACKWARD,
	ON_THE_SPOT,
};
