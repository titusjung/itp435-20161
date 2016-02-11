#pragma once
#include <string>
#include <vector>
std::string getHexSHA1(const std::string  input);
std::string bruteForce(const std::string input,  std::string& output, int limit);
std::string bruteForce(const std::string input,  std::string& output, std::vector<unsigned int> start, std::vector<unsigned int> end);

std::vector<unsigned int> getNextVecB35(std::vector<unsigned int> input);
std::string getStringfromVec(std::vector<unsigned int> input);
std::vector<unsigned int> getNextVecB35SameSize(std::vector<unsigned int> input); 
void getNextVecB35SameSizeRef(std::vector<unsigned int>& input);
