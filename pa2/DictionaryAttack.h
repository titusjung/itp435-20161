#pragma once
# include "DictionaryAttack.h"
# include <string>
# include <unordered_map>
#include <map>
#include <vector>
struct passContainer
{
	std::string word;
	unsigned char hash[20];
	std::string  hex_str;
};

class DictionaryAttack
{
public:
	static const int EXPECTED_SIZE = 100000; 
	passContainer* getPassContainer(const std::string input );
	DictionaryAttack();
	void loadDictionary(const std::string filename);
	void loadPasswordsAndPrintResults(std::string inputs, std::string output);
	void loadPasswordsandSolve(std::string input);
	void parallelBruteForceLoadedPasswords();
	void parallelBruteForceHelper( std::vector<unsigned int> start, std::vector<unsigned int> end);
	void print(std::string outputfile); 
	~DictionaryAttack();


private:
	std::string dictFile, passFile; 
	std::unordered_map<std::string, passContainer*> wordMap; 
	std::map<int, passContainer*> solvedMap;
	std::map<int, passContainer*> unSolvedMap;
	std::unordered_map<std::string, passContainer*> unsolvedWMap;

	std::vector<passContainer*> pcPointers;
	bool loadedPasswords; 
};

