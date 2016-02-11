#include "DictionaryAttack.h"
#include "Sha1.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Timer.h"
#include <vector>
#include "ParallelBruteForce.h"
#include <tbb/parallel_invoke.h>
#include "util.h"




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
	loadedPasswords = false; 
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
		pcPointers.push_back(pc); 
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
	loadedPasswords = true; 
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
void DictionaryAttack::loadPasswordsandSolve(std::string input)
{
	loadedPasswords = true;
	std::ifstream infile(input);
	int i = 0; 
	if (infile.is_open() )
	{
		std::string line;
		Timer timer;
		timer.start();
		while (std::getline(infile, line))
		{

			std::unordered_map<std::string, passContainer*>::iterator it;
			it = wordMap.find(line);
			if (it != wordMap.end())
			{
				std::string solved = it->second->word;
				solvedMap.emplace(i, it->second);
			}
			else
			{
				struct passContainer* pc;
				auto it = unsolvedWMap.find(line);
				if (it == unsolvedWMap.end())
				{
					pc = new passContainer;
					pc->hex_str = line;
					pc->word = "?";
					unSolvedMap.emplace(i, pc);
					pcPointers.push_back(pc);
					unsolvedWMap.emplace(line, pc);
				}
				else
				{
					unSolvedMap.emplace(i, it->second);

				}
			}
			i++; 
		}
		std::cout << "finished loading passwords at " << timer.getElapsed() << " seconds" << std::endl;

	}
	else std::cerr << "could not open files for password check and output " << std::endl;


	infile.close();
}

void DictionaryAttack::parallelBruteForceLoadedPasswords()
{
	if (!loadedPasswords) return;
	Timer timer;
	timer.start();
	tbb::parallel_invoke(
		//[this,input] { bruteForce(input, 3); },

		[this] { parallelBruteForceHelper( { 0,0,0,0 }, { 35,35,35,3 }); },

		[this] { parallelBruteForceHelper( { 0,0,0,4 }, { 35,35,35,7 }); },

		[this] { parallelBruteForceHelper( { 0,0,0,8 }, { 35,35,35,11 }); },

		[this] { parallelBruteForceHelper( { 0,0,0,12 }, { 35,35,35,15 }); },

		[this] { parallelBruteForceHelper( { 0,0,0,16 }, { 35,35,35,19 }); },

		[this] { parallelBruteForceHelper( { 0,0,0,20 }, { 35,35,35,23 }); },

		[this] { parallelBruteForceHelper( { 0,0,0,24 }, { 35,35,35,27 }); },

		[this] { parallelBruteForceHelper( { 0,0,0,28 }, { 35,35,35,31 }); },

		[this] { parallelBruteForceHelper( { 0,0,0,32 }, { 35,35,35,35 }); }

	);
	std::cout << "finished parallel brute forcing passwords at " << timer.getElapsed() << " seconds" << std::endl;

}

void DictionaryAttack::parallelBruteForceHelper( std::vector<unsigned int> start, std::vector<unsigned int> end)
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
			if (vec.empty()) break;
		}
		getNextVecB35SameSizeRef(vec);

		std::string testString = getStringfromVec(vec);
		std::string potResult = getHexSHA1(testString);
		/*
		if (testString == "l33t")
		{
			std::cout << "testing string " << testString << std::endl;
			std::cout << "hex string " << potResult << std::endl;
			
		}*/
		auto it = unsolvedWMap.find(potResult);
		if (it != unsolvedWMap.end())
		{
			it->second->word = testString;
		}
		j++;
	}
}

void DictionaryAttack::print(std::string outputfile)
{
	std::ofstream ofile(outputfile);
	if (ofile.is_open())
	{
		solvedMap.insert(unSolvedMap.begin(), unSolvedMap.end());
		for each  (std::pair<int, passContainer*> temp in solvedMap)
		{
			ofile << temp.second->hex_str << "," << temp.second->word << std::endl;
		}
		ofile.flush(); 
	}
	else {
		std::cerr << "could not open files for password check and output " << std::endl;
		
	}
	ofile.close(); 
}

DictionaryAttack::~DictionaryAttack()
{
	for each (passContainer*  temp in pcPointers )
	{
		delete temp; 
	}
}
