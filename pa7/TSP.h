#pragma once
#include <string>
#include <vector>
#include <random>
#include <memory>
struct Location
{
	Location() { }
	std::string mName;
	double mLatitude;
	double mLongitude;
	~Location() { }
};

struct Population
{
	std::vector<std::vector<int>> mMembers;
};
std::vector<std::shared_ptr<Location>> GetLocation(const std::string& filname); 
Population GetPopulation(std::mt19937& random, const int popSize, const int numCities);
std::vector<std::pair<int, double>> GetFitness(const Population& pop, const std::vector<std::shared_ptr<Location>>& locVec);
double GetDifference(double lat1, double lon1, double lat2, double lon2);
std::vector<std::pair<int, double>> SortFitness(const std::vector<std::pair<int, double>> fitVec);
std::vector<double> GetProbVec(const int size, const std::vector<std::pair<int, double>>& sortedVec);
std::vector<double> GetProbVec2(const int size, const std::vector<std::pair<int, double>>& sortedVec);

std::vector<std::pair<int, int>> GetSelectedPairs(const std::vector<std::pair<int, double>>& sortedVec, const std::vector<std::pair<int, double>>& fitVec, const int popSize, std::mt19937 rand);

std::vector<std::pair<int, int>> GetSelectedPairs(const std::vector<std::pair<int, double>>& sortedVec, const std::vector<std::pair<int, double>>& fitVec, const int popSize, std::mt19937 rand)
;
std::vector<int> GetCrossover(const std::vector<int>& v1, const std::vector<int>& v2, std::mt19937& rand, double mutChance); 
Population CrossOverPopulation(const std::vector<std::pair<int, int>>& selectedPairs, const Population& pop, std::mt19937& rand, double mutationChance); 