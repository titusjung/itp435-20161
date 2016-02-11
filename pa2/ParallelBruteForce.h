#pragma once
#include <string>
#include <vector>
#include <unordered_map>
class ParallelBruteForce
{
public:
	const static int EXPECTED_SIZE = 1544760;
	ParallelBruteForce() : crackedPass("?"), solved(false) {
		alreadyCheckedMap.rehash(EXPECTED_SIZE);
	}
	void parallelBruteForce(std::string input); 
	std::string bruteForce(const std::string input, int limit);
	std::string bruteForce(const std::string input, std::vector<unsigned int> start, std::vector<unsigned int> end);
	void clear() { crackedPass = "?"; solved = false;  }
	std::string getPass() {return crackedPass;}
	bool isSolved(){return solved; }
private:
	std::string crackedPass;
	bool solved; 
	std::unordered_map<std::string, std::string> alreadyCheckedMap; 
};