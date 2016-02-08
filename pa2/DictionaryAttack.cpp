#include "DictionaryAttack.h"
#include "Sha1.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Timer.h"
#include <vector>

std::string bruteForce(std::string input, int limit)
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
		if (vec.size() == limit+1)
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

std::string getStringfromVec(std::vector<unsigned int> input)
{
	std::string result =""; 
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
			int insert = ele - 25; 
			
			result+= std::to_string(insert);
		}
		else
		{
			std::cerr << " overflow problem at get string from Vec" << std::endl;
			return "";
		}
	}
	return result; 
}

std::vector<unsigned int> getNextVecB35(std::vector<unsigned int> input)
{
	int i = 0;
	input[i]++;
	while (input[i] >= 35)
	{
		input[i] = 0;
		if (i + 1 < (signed) input.size())
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
void DictionaryAttack::getHexSHA1(const void * input, unsigned char * hash, char * hex)
{
	 sha1::calc(input, sizeof(input), hash);
	sha1::toHexString(hash, hex);
}



struct passContainer* DictionaryAttack::getPassContainer(const std::string input)
{

	struct passContainer* pc = new passContainer;
	unsigned char hash[20];
	sha1::calc(&input, input.length(), hash);
	char hex_str[41];
	sha1::toHexString(hash, hex_str);

	pc->hex_str = hex_str;
	pc->word = input;
	for (int i = 0; i < 20; i++)
	{
		pc->hash[i] = hash[i]; 
	}

	return pc; 
}

DictionaryAttack::DictionaryAttack()
{
	wordMap.rehash(EXPECTED_SIZE);
}

void DictionaryAttack::loadDictionary(std::string filename)
{
	dictFile = filename;
	std::ifstream infile(filename);

	if (!infile.is_open()) {
		std::cerr << "could not open file " << filename << std::endl; 
		infile.close(); 
		return;
	}
	std::string line; 
	Timer timer;
	timer.start(); 
	while (std::getline(infile, line))
	{
		//std::cout << "placing line in " << line << std::endl;
		struct passContainer* pc = getPassContainer(line);
		wordMap.emplace(pc->hex_str, pc); 
	}
	infile.close(); 
	std::cout << "finished loading dictionary at " <<timer.getElapsed()<<" seconds"<< std::endl; 

}
/*
std::vector<std::string> DictionaryAttack::loadPasswords(std::string input)
{
	std::vector<std::string> stringVec;
	
}*/
void DictionaryAttack::loadPasswordsAndPrintResults(std::string input, std::string output)
{
	std::ifstream infile(input);
	std::ofstream ofile(output);

	if (infile.is_open() && ofile.is_open())
	{
		std::string line;
		Timer timer;
		timer.start();
		while (std::getline(infile, line))
		{
			std::unordered_map<std::string,passContainer*>::iterator it; 
			it = wordMap.find(line);
			if ( it != wordMap.end())
			{
				std::string solved =it->second->word; 
				ofile << line << "," << solved << std::endl; 
			}
			else
			{
				ofile << line << ",??" << std::endl;
			}
		}
		ofile.flush(); 
		std::cout << "finished loading passwords and printing output at " << timer.getElapsed() << " seconds" << std::endl;

	}
	else std::cerr << "could not open files for password check and output " << std::endl;


	infile.close();
	ofile.close();
}
DictionaryAttack::~DictionaryAttack()
{
	for each (std::pair<std::string, passContainer*> temp in wordMap)
	{
		delete temp.second; 
	}
}
