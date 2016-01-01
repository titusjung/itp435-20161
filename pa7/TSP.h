#pragma once
#include <string>
#include <vector>
#include <random>

struct Location
{
	std::string mName;
	double mLatitude;
	double mLongitude;
};

struct Population
{
	std::vector<std::vector<int>> mMembers;
};
