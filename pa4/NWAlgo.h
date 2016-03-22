#pragma once
#include <vector>
#include <string>
#include "FastaReader.h"
enum Direction : char
{
	UPLEFT,
	LEFT,
	UP
}; 
class NWAlgo
{
public:
	void Load(const std::string& filename,const  std::string& filename2);
	void Process(); 
	void Print(const std::string& filename);
private:
	//std::vector<std::vector<short>> mScoreGrid;
	//std::vector<std::vector<Direction>> mDirectionGrid;
	FastaReader mFileA, mFileB; 
	std::string mBodyA, mBodyB; 
	std::string mResultA, mResultB; 
	const short mGap = -1; 
	int mScore; 
};