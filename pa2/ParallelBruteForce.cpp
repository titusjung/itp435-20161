#include "ParallelBruteForce.h"
#include "Sha1.h"
#include <tbb/parallel_invoke.h>
#include <iostream>
#include "util.h"

void ParallelBruteForce::parallelBruteForce(std::string input)
{
	solved = false; 
	auto it = alreadyCheckedMap.find(input); 
	if (it != alreadyCheckedMap.end())
	{
		crackedPass = it->second; 
		solved = true; 
		return;
	}
	tbb::parallel_invoke(
		//[this,input] { bruteForce(input, 3); },

		[this, input ] { bruteForce(input, { 0,0,0,0 }, { 35,35,35,3 }); },

		[this, input] { bruteForce(input, {0,0,0,4 }, { 35,35,35,7 }); },

		[this, input] { bruteForce(input,  { 0,0,0,8 }, { 35,35,35,11 }); },

		[this, input] { bruteForce(input, { 0,0,0,12 }, { 35,35,35,15 }); },

		[this, input] { bruteForce(input, { 0,0,0,16 }, { 35,35,35,19 }); },

		[this, input] { bruteForce(input,  { 0,0,0,20 }, { 35,35,35,23 }); },

		[this, input] { bruteForce(input, { 0,0,0,24 }, { 35,35,35,27 }); },

		[this, input] { bruteForce(input, { 0,0,0,28 }, { 35,35,35,31 }); },

		[this, input] { bruteForce(input,  { 0,0,0,32 }, { 35,35,35,35 }); }

		);
}

std::string ParallelBruteForce::bruteForce(const std::string input, int limit)
{
	std::vector<unsigned int> vec;// 5th array element detects overflow; 
								  /*
								  for (int i = 0; i < limit+1; i++)
								  {
								  vec.push_back(0);
								  }*/
	vec.push_back(0);

	int j = 0;
	while (true)
	{
		vec = getNextVecB35(vec);
		//overflow detection 
		if (vec.size() == limit + 1)
		{
			/*
			std::cout << "overflow at ";
			for (int i = 0; i < limit + 1; i++)
			{
				std::cout << vec[i] << " ";
			}*
			std::cout << std::endl;*/
			break;
		}
		std::string testString = getStringfromVec(vec);
		std::string potResult = getHexSHA1(testString);
		if (!(j % 13))
		{
			//std::cout << "testing string " << testString << std::endl;
		}
		if (input == potResult)
		{
			crackedPass = testString;
			solved = true; 
			return testString;
		}
		j++;
	}
	return "?";
}

std::string ParallelBruteForce::bruteForce(const std::string input, std::vector<unsigned int> start, std::vector<unsigned int> end)
{
	std::vector<unsigned int> vec = start;

	int j = 0;
	while (true)
	{
		//overflow detection 
		if (std::equal(vec.begin(), vec.end(), end.begin()))
		{
			start.pop_back();
			vec = start; 
			end.pop_back(); 
			if(vec.empty()) break;
		}
		getNextVecB35SameSizeRef(vec);

		std::string testString = getStringfromVec(vec);
		std::string potResult = getHexSHA1(testString);
		if ((j % 15000 ==0))
		{
			//std::cout << "testing string " << testString << std::endl;
		}
		if (input == potResult)
		{
			crackedPass = testString;
			solved = true;
			return testString;
		}
		if(alreadyCheckedMap.find(potResult)!=alreadyCheckedMap.end())
			alreadyCheckedMap.emplace(potResult, testString); 
		j++;
	}
	return "?";
}
