#pragma once
# include "DictionaryAttack.h"
# include <string>
# include <unordered_map>
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
	static void getHexSHA1(const void* input, unsigned char* hash, char* hex);
	passContainer* getPassContainer(const std::string input);
	DictionaryAttack();
	void loadDictionary(const std::string filename);
	void loadPasswordsAndPrintResults(std::string inputs, std::string output);
	~DictionaryAttack();


private:
	std::string dictFile, passFile; 
	std::unordered_map<std::string, passContainer*> wordMap; 
};
std::string getHexSHA1(const std::string  input);
std::string bruteForce(std::string input, int limit); 
std::vector<unsigned int> getNextVecB35(std::vector<unsigned int> input);
std::string getStringfromVec(std::vector<unsigned int> input);
