#include <iostream>
#include <random>
#include "TSP.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
int main(int argc, const char* argv[])
{
	if (argc < 6)
	{
		printf("wrong number of arguments");
		return -1;
	}
	std::string inputName = argv[1];
	int popSize = atoi(argv[2]);
	int generations = atoi(argv[3]);
	int mutationChance = atoi(argv[4]);
	int seed = atoi(argv[5]);
	//std::cout << "reading in arguments " << inputName << " " << popSize << " " << generations << " " << mutationChance << " " << seed << std::endl;

	auto locationVec = GetLocation(inputName);
	std::mt19937 random(seed);
	std::ofstream ofile("log.txt");
	Population pop = GetPopulation(random, popSize, locationVec.size());
	/*
	for (unsigned int i = 0; i < locationVec.size(); i++)
	{
		std::cout << locationVec[i]->mName << " " <<locationVec[i]->mLatitude<<" "<<locationVec[i]->mLongitude<<std::endl;
	}*/
	for (int k = 0; k < generations; k++)
	{
		ofile << "INITIAL POPULATION:" << std::endl; 
		for (unsigned int i = 0; i < pop.mMembers.size(); i++)
		{
			for (unsigned int j = 0; j < pop.mMembers[i].size(); j++)
			{
				ofile << pop.mMembers[i][j] << ",";
			}
			ofile << std::endl;
		}
		auto fitVec = GetFitness(pop, locationVec);
		ofile << "FITNESS:" << std::endl;
		for (std::pair<int, double> i : fitVec)
		{
			ofile << i.first << ":" << i.second << std::endl;
		}
		auto sortedVec = SortFitness(fitVec);
		/*
		std::cout << "sorted" << std::endl << std::endl;
		for (std::pair<int, double> i : sortedVec)
		{
			std::cout << i.first << " " << i.second << std::endl;
		}*/

		auto selectedVec = GetSelectedPairs(sortedVec, fitVec, sortedVec.size(), random);
		ofile << "SELECTED PAIRS" << std::endl;
		for (std::pair<int, int> i : selectedVec)
		{
			//int a = fitVec[i.first].first;
			//int b = fitVec[i.second].first;
			int a = i.first;
			int b = i.second;
			//int a = sortedVec[i.first].first;
			//int b = sortedVec[i.second].first;
			//std::cout << i.first << " " << i.second << std::endl;
			ofile <<"("<< a << "," << b <<")"<< std::endl;

		}
		Population npop = CrossOverPopulation(selectedVec, pop, random, mutationChance);
		pop = npop; 
	}
	return 0;
}


