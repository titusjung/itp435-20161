#include "util.h"
#include <iostream>
#include "Sha1.h"
#include <tbb/parallel_invoke.h>

const int noThreads = 10; 

std::string parallelBruteForce(const std::string input)
{
	std::vector<std::vector<int>> starts; 
	std::vector<std::vector<int>> ends;
	/*
	starts.push_back( {0,0,0,0 }); 
	ends.push_back({ 3,35,35,35 });

	starts.push_back({ 4,0,0,0 });
	ends.push_back({ 7,35,35,35 });

	starts.push_back({8,0,0,0 });
	ends.push_back({ 11,35,35,35 });

	starts.push_back({ 12,0,0,0 });
	ends.push_back({15,35,35,35 });

	starts.push_back({ 16,0,0,0 });
	ends.push_back({ 19,35,35,35 });

	starts.push_back({ 20,0,0,0 });
	ends.push_back({ 23,35,35,35 });

	starts.push_back({ 24,0,0,0 });
	ends.push_back({ 27,35,35,35 });

	starts.push_back({ 28,0,0,0 });
	ends.push_back({ 31,35,35,35 });

	starts.push_back({ 32,0,0,0 });
	ends.push_back({ 35,35,35,35 });
	*/
	/*
	tbb::parallel_invoke(
		[input ] { bruteForce(input, 3); },
		[input ]{ bruteForce(input, {0,0,0,0} ,{ 3,35,35,35 }); },

		[input ] { bruteForce(input, { 4,0,0,0 }, { 7,35,35,35 }); },

		[input ] { bruteForce(input,  { 8,0,0,0 }, { 11,35,35,35 }); },

		[input ] { bruteForce(input,  { 12,0,0,0 }, { 15,35,35,35 }); },

		[input ] { bruteForce(input,  { 16,0,0,0 }, { 19,35,35,35 }); },


		[input ] { bruteForce(input,  { 20,0,0,0 }, { 23,35,35,35 }); },

		[input ] { bruteForce(input,  { 24,0,0,0 }, { 27,35,35,35 }); },

		[input ] { bruteForce(input,  { 28,0,0,0 }, { 31,35,35,35 }); },

		[input ] { bruteForce(input,  { 32,0,0,0 }, { 35,35,35,35 }); },



		);*/
}

std::string bruteForce(const std::string input, int limit)
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
			std::cout << "overflow at ";
			for (int i = 0; i < limit + 1; i++)
			{
				std::cout << vec[i] << " ";
			}
			std::cout << std::endl;
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
			return testString;
		}
		j++;
	} 
	return "?";

}
std::string bruteForce(const std::string input, std::vector<unsigned int> start, std::vector<unsigned int> end)
{
	std::vector<unsigned int> vec =start;// 5th array element detects overflow; 
								  /*
								  for (int i = 0; i < limit+1; i++)
								  {
								  vec.push_back(0);
								  }*/

	int j = 0;
	while (true)
	{
		vec = getNextVecB35(vec);
		//overflow detection 
		if (std::equal(vec.begin(),vec.end(), end.begin()))
		{

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
			return testString;
		}
		j++;
	}
	return "?";
}

std::string getStringfromVec(std::vector<unsigned int> input)
{
	std::string result = "";
	for (unsigned int i = 0; i < input.size(); i++)
	{
		int ele = input[i];
		if (ele < 26)
		{
			char insert = ele + 'a';
			result += insert;
		}
		else if (ele>25 && ele<36)
		{
			int insert = ele - 26;

			result += std::to_string(insert);
		}
		else
		{
			std::cerr << " overflow problem at get string from Vec" << std::endl;
			return "";
		}
	}
	return result;
}
std::vector<unsigned int> getNextVecB35SameSize(std::vector<unsigned int> input)
{
	int i = 0;
	input[i]++;
	while (input[i] > 35)
	{
		input[i] = 0;
		if (i + 1 < (signed)input.size())
		{
			input[i + 1]++;
			i++;
		}
		else break; 
	}
	return input;

}
void getNextVecB35SameSizeRef(std::vector<unsigned int>& input)
{
	int i = 0;
	input[i]++;
	while (input[i] > 35)
	{
		input[i] = 0;
		if (i + 1 < (signed)input.size())
		{
			input[i + 1]++;
			i++;
		}
		else break;
	}

}

std::vector<unsigned int> getNextVecB35(std::vector<unsigned int> input)
{
	int i = 0;
	input[i]++;
	while (input[i] >= 35)
	{
		input[i] = 0;
		if (i + 1 < (signed)input.size())
		{
			input[i + 1]++;
			i++;
		}
		else input.push_back(0);
	}
	return input;

}
std::string getHexSHA1(const std::string input)
{
	unsigned char hash[20];
	sha1::calc(&input, input.length(), hash);
	char hex_str[41];
	sha1::toHexString(hash, hex_str);
	std::string result = hex_str;
	return result;
}