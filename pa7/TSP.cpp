#include "TSP.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <iostream>

std::vector<std::shared_ptr<Location>> GetLocation(const std::string& filname)
{
	std::ifstream inputFile(filname, std::ios::in);

	std::vector<std::shared_ptr<Location>> locationVec;
	//std::vector<Location> locationVec;

	std::string fileLine;
	std::string nameBuffer;
	//int latBuffer, lonBuffer; 
	int i = 0;
	while (std::getline(inputFile, fileLine))
	{
		std::shared_ptr<Location>locationBuffer = std::make_shared<Location>();
		//locationVec.push_back(Location()); 
		int nameIndex = fileLine.find(',');
		locationBuffer->mName = fileLine.substr(0, nameIndex);
		int latIndex = fileLine.find(',', nameIndex + 1);
		locationBuffer->mLatitude = std::stod(fileLine.substr(nameIndex + 1, latIndex - nameIndex - 1))*0.0174533;
		locationBuffer->mLongitude = std::stod(fileLine.substr(latIndex + 1, fileLine.size() - latIndex - 1))*0.0174533;
		//locationVec[i].mLatitude = std::stof(fileLine.substr(nameIndex, latIndex));
		//locationVec[i].mLongitude = std::stof(fileLine.substr(latIndex+1, fileLine.size()));

		locationVec.push_back(locationBuffer);
		fileLine.clear();
	}

	return locationVec; 
}
std::vector<int> GetSequential(int size)
{
	std::vector<int> result(size); 
	int i = 0;
	std::generate(result.begin(), result.end(), [&i] {return i++; });
	return result; 
}
Population GetPopulation(std::mt19937& random, const int popSize, const int numCities)
{
	Population pop; 
	pop.mMembers.resize(popSize); 

	std::generate(pop.mMembers.begin(), pop.mMembers.end(), [&numCities,&random]()
	{
		auto member = GetSequential(numCities); 
		std::shuffle(member.begin() + 1, member.end(),random); 
		return member; 
	});
	return pop; 
}
double GetDifference(double lat1, double lon1, double lat2, double lon2)
{
	double dlon = lon2 - lon1;
	double dlat = lat2 - lat1;

	double a1 = pow(sin(dlat / 2.0), 2.0) + cos(lat1)*cos(lat2)*pow(sin(dlon / 2.0), 2.0);
	double c = 2.0*atan2(sqrt(a1), sqrt(1.0 - a1));
	return 3961.0 * c;
}
double GetDifference(const std::shared_ptr<Location>& loc1, const std::shared_ptr<Location>& loc2)
{
	double lon1 = loc1->mLongitude;
	double lat1 = loc1->mLatitude;

	double lon2 = loc2->mLongitude;
	double lat2 = loc2->mLatitude;

	double dlon = lon2 - lon1;
	double dlat = lat2 - lat1;

	double a1 = pow(sin(dlat / 2.0), 2.0) + cos(lat1)*cos(lat2)*pow(sin(dlon / 2.0), 2.0);
	double c = 2.0*atan2(sqrt(a1), sqrt(1.0 - a1));
	return 3961.0 * c;
}
/*
std::pair<int, double> GetFitPair()
{

}*/
std::vector<std::pair<int, double>> GetFitness(const Population& pop, const std::vector<std::shared_ptr<Location>>& locVec)
{
	std::vector<std::pair<int, double>> fitVec;
	int i = 0; 
	std::for_each(pop.mMembers.begin(), pop.mMembers.end(), [&i, &locVec,&fitVec](const std::vector<int>& member)
	{
		std::vector<double> differences; 
		std::adjacent_difference(member.begin(), member.end(), std::back_inserter( differences), [&locVec](const int& a, const int& b)->double
		{
			return GetDifference(locVec[a]->mLatitude, locVec[a]->mLongitude, locVec[b]->mLatitude, locVec[b]->mLongitude);
		});
		double fitness = std::accumulate(differences.begin(), differences.end(),0.0);
		fitness += GetDifference(locVec[member.back()], locVec[member.front()]); 
		fitVec.push_back(std::pair<int, double>(i++, fitness)); 
	});
	return fitVec; 
}
std::vector<std::pair<int, double>> SortFitness(const std::vector<std::pair<int, double>> fitVec)
{
	std::vector<std::pair<int, double>> result = fitVec; 
	std::sort(result.begin(), result.end(), [](std::pair<int, double> a, std::pair<int, double> b)
	{
		return a.second < b.second; 
	}
	);
	return result; 
}
std::vector<double> GetUniformProbVec(const int size)
{
	std::vector<double> result(size);
	std::generate(result.begin(), result.end(), [&size]() {return 1.0/size; });
	return result;
}
std::vector<double> GetProbVec(const int size, const std::vector<std::pair<int, double>>& sortedVec)
{
	auto result = GetUniformProbVec(size); 
	/*
	result[sortedVec[0].first] = result[sortedVec[0].first] * 6.0;
	result[sortedVec[1].first] = result[sortedVec[1].first] * 6.0;
	for (unsigned int i = 2; i < sortedVec.size() / 2; i++)
	{
		result[sortedVec[i].first] = result[sortedVec[i].first] * 3.0;
	}
	*/
	
	result[0]*= 6.0;
	result[1] *= 6.0;
	std::transform(result.begin() + 2, result.begin() + result.size() / 2, result.begin()+2,
		[](const double x)
		{
			return x*3.0; 
		}
	);
	double sum = std::accumulate(result.begin(), result.end(), 0.0);
	std::transform(result.begin(), result.end(), result.begin(),
		[&sum](const double x)
	{
		return x/sum;
	}
	);
	return result; 
	/*
	for (unsigned int i = 2; i < result.size()/2; i++)
	{
		result[i] = result[i] * 3.0; 
	}*/
}

std::vector<double> GetProbVec2(const int size, const std::vector<std::pair<int, double>>& sortedVec)
{
	auto result = GetUniformProbVec(size);
	
	result[sortedVec[0].first] = result[sortedVec[0].first] * 6.0;
	result[sortedVec[1].first] = result[sortedVec[1].first] * 6.0;
	for (unsigned int i = 2; i < sortedVec.size() / 2; i++)
	{
	result[sortedVec[i].first] = result[sortedVec[i].first] * 3.0;
	}
	
	/*
	result[0] *= 6.0;
	result[1] *= 6.0;
	std::transform(result.begin() + 2, result.begin() + result.size() / 2, result.begin() + 2,
		[](const double x)
	{
		return x*3.0;
	}
	);*/
	double sum = std::accumulate(result.begin(), result.end(), 0.0);
	std::transform(result.begin(), result.end(), result.begin(),
		[&sum](const double x)
	{
		return x / sum;
	}
	);
	return result;
	/*
	for (unsigned int i = 2; i < result.size()/2; i++)
	{
	result[i] = result[i] * 3.0;
	}*/
}

int GetSelectedIndex(const std::vector<double>& probVec, const double rand)
{
	double runningSum = 0.0; 
	unsigned int i; 
	for ( i = 0; i < probVec.size(); i++)
	{
		runningSum += probVec[i];
		if (runningSum>=rand)
			return i; 
	}
	return i; 
}


std::vector<std::pair<int, int>> GetSelectedPairs(const std::vector<std::pair<int,double>>& sortedVec, const std::vector<std::pair<int, double>>& fitVec, const int popSize, std::mt19937 rand)
{
	std::vector<std::pair<int, int>> pairVec(popSize);
	std::vector<double> probVec = GetProbVec2(popSize,sortedVec);
	std::cout << "Prob vec" << std::endl; 
	for (unsigned int i = 0; i < probVec.size();i++)
	{
		std::cout << probVec[i] << std::endl;
	}

	std::generate(pairVec.begin(), pairVec.end(), [&probVec, &fitVec, &rand] ()
		{ 
			std::pair<int, int> x;
			std::uniform_real_distribution<double> urd(0.0, 1.0);

			x.first = fitVec[GetSelectedIndex(probVec, urd(rand))].first;
			x.second= fitVec[GetSelectedIndex(probVec, urd(rand))].first;
			return x; 
		}
	);
	return pairVec; 
}

Population CrossOverPopulation(const std::vector<std::pair<int, int>>& selectedPairs, const Population& pop, std::mt19937& rand, double mutationChance)
{
	Population nPop;
	//nPop.mMembers.resize(selectedPairs.size());
	/*
	std::for_each(selectedPairs.begin(), selectedPairs.end(), [&nPop,&pop,&mutationChance,&rand] (const std::pair<int,int> pear)
		{
			std::vector<int> next = GetCrossover(pop.mMembers[pear.first], pop.mMembers[pear.second], rand, mutationChance);
			nPop.mMembers.push_back(next); 
		}
	); */
	
	for (unsigned int i = 0; i < selectedPairs.size(); i++)
	{
		std::vector<int> next = GetCrossover(pop.mMembers[selectedPairs[i].first], pop.mMembers[selectedPairs[i].second], rand, mutationChance);
		nPop.mMembers.push_back(next);
	}

	return nPop; 
}
std::vector<int> GetCXHelper(const std::vector<int>& v1, const std::vector<int>& v2, int cxi)
{
	std::vector<int> result;
	
	std::copy_n(v1.begin(), cxi, std::back_inserter(result));
	
	std::copy_if(v2.begin(), v2.end(), std::back_inserter(result), [&result](const int a)
	{
		return std::find(result.begin(), result.end(), a) == result.end();
		//return true; 
	});

	return result; 
}

std::vector<int> GetCrossover(const std::vector<int>& v1, const std::vector<int>& v2, std::mt19937& rand, double mutChance)
{
	std::vector<int> result; 
	std::uniform_int_distribution<int> uid(1, v1.size() - 2);
	int cxi = uid(rand);
	std::uniform_int_distribution<int> coin(0, 1);
	int flip = coin(rand);
	if (flip)
	{
		result = GetCXHelper(v1, v2, cxi); 
	}
	else
	{
		result = GetCXHelper(v2, v1, cxi);
	}
	std::uniform_real_distribution<double> urd(0.0, 1.0);
	double mutant = urd(rand);
	if (mutant <= mutChance)
	{
		std::uniform_int_distribution<int> uid(1, result.size() - 1);
		int first = uid(rand);
		int second = uid(rand);
		int save = result[first];
		result[first] = result[second];
		result[second] = save;
	}
	return result; 
}