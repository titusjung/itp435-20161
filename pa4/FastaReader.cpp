#include "FastaReader.h"
#include <iostream>
#include <fstream>
//#include <FileNotFoundException>
//#include <IOException>
#include "Exceptions.h"
#include <sstream>
FastaReader::FastaReader()
{
	mHeaderString = "";
	mBody = ""; 
}
FastaReader::FastaReader(const std::string& filename)
{
	//std::ifstream fastaFile;
	mHeaderString = "";
	mBody = ""; 
	LoadFile(filename); 
}

void FastaReader::LoadFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::in | std::ios::ate);
	std::ofstream test("test.txt"); 
	if (!file.is_open())
	{
		throw FileLoadExcept();
		return;
	}
	std::ifstream::pos_type size;
	size = file.tellg();
	file.seekg(0, std::ios::beg);
	std::getline(file, mHeaderString);
	if (mHeaderString.at(0) != '>')
	{
		throw FileLoadExcept();
		return; 
	}
	mHeaderString = mHeaderString.substr(1, mHeaderString.size());
	test <<mHeaderString; 
	std::string line;
	mBody.reserve(static_cast<unsigned int>(size)); 
	while (std::getline(file, line))
	{
		for (unsigned int i = 0; i < line.size(); i++)
		{
			char c = line.at(i); 
			if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
			{
				continue; 
			}
			else
			{
				mBody += c; 
			}
		}
	}
	test <<"\n"<< mBody; 
	test.close(); 
	file.close(); 
	
	//std::cout << "My Header " << mHeaderString << std::endl;
}

void FastaReader::Clear()
{
	mHeaderString.clear();
	mBody.clear(); 
}
