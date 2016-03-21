#pragma once
#include <string>

class FastaReader
{
public:
	FastaReader();
	FastaReader(std::string& filename);
	void LoadFile(std::string& file); 

private:
	std::string mHeaderString;
	std::string mBody; 
	int mSize; 
};