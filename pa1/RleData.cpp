#include "RleData.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
void RleData::Compress(const char* input, size_t inSize)
{
	// TODO
	char*  temp = new char[MaxRunSize()];
	

	std::string debugStor =""; 
	std::string uniqueBuff =""; 
	int charPos=1;
	int numberOfRepeats=1;
	char currChar; 
	char prevChar = input[0];
	int sizeCompressed = 0; 
	bool lookingForUnique = false; 
	int nUniqueLett = 0; 
	for (size_t i = 1; i <= inSize; i++)
	{
		currChar = input[i]; 
		if (currChar == prevChar)
		{
			numberOfRepeats++; 
			
			if (lookingForUnique)
			{
				temp[charPos - 1] = ~nUniqueLett + 1;
				debugStor.append(std::to_string(-nUniqueLett)); 
				std::cout << std::endl<< "Number of unique letters  is " << nUniqueLett << std::endl;
				for (unsigned int i = 0; i < uniqueBuff.size(); i++)
				{
					temp[charPos +i] = uniqueBuff.at(i);
				}
				debugStor.append(uniqueBuff); 
				charPos += uniqueBuff.size(); 
				nUniqueLett = 0;
				uniqueBuff = ""; 
			}
			lookingForUnique = false;
			
		}
		else
		{
			if (numberOfRepeats > 1)
			{
				temp[charPos - 1] = numberOfRepeats;
				temp[charPos] = prevChar;
				debugStor.append(std::to_string(numberOfRepeats));
				debugStor += prevChar; 
				charPos += 2;
				prevChar = currChar;
				numberOfRepeats = 1;
				sizeCompressed += 2;
				//lookingForUnique = true;

			}
			else if (!lookingForUnique)
			{
				uniqueBuff = uniqueBuff+prevChar + currChar;
				numberOfRepeats = 2;
				nUniqueLett = 2; 
				lookingForUnique = true;
			}
			else
			{
				uniqueBuff = uniqueBuff + currChar; 
				numberOfRepeats++;
				nUniqueLett++; 

				std::cout <<"unique buff is "<< uniqueBuff << std::endl; 
			}
			
		}
	}
	if (lookingForUnique)
	{
		temp[charPos - 1] = ~nUniqueLett+1;
		std::cout << std::endl << "Number of unique letters  is " << std::hex<< static_cast<unsigned>(temp[charPos - 1]) << std::dec<< std::endl;
		debugStor.append(std::to_string(-nUniqueLett));

		for (unsigned int i = 0; i < uniqueBuff.size(); i++)
		{
			temp[charPos + i] = uniqueBuff.at(i);
		}
		debugStor.append(uniqueBuff);

		charPos += uniqueBuff.size();
		nUniqueLett = 0;
		uniqueBuff = "";
	}

	mSize = sizeCompressed; 
	mData = new char[sizeCompressed];

	std::cout << "compressed string is " << debugStor << std::endl; 
	for ( int i = 0; i < sizeCompressed; i++)
	{
		mData[i] = temp[i]; 
		//if (i == 62) std::cout <<"at 62 "<< std::hex << mData[i] << std::endl; 
	}

	delete[] temp; 
}

void RleData::Decompress(const char* input, size_t inSize, size_t outSize)
{
	// TODO
}

std::ostream& operator<< (std::ostream& stream, const RleData& rhs)
{
	for (int i = 0; i < rhs.mSize; i++)
	{
		stream << rhs.mData[i];
	}
	return stream;
}