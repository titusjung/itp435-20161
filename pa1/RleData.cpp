#include "RleData.h"
#include <iostream>
void RleData::Compress(const char* input, size_t inSize)
{
	// TODO
	char*  temp = new char[MaxRunSize()];

	int charPos=1;
	
	int numberOfChars=1;
	char currChar; 
	char prevChar = input[0];
	int sizeCompressed = 0; 
	for (size_t i = 1; i <= inSize; i++)
	{
		currChar = input[i]; 
		if (currChar == prevChar)
		{
			numberOfChars++; 
		}
		else
		{
			temp[charPos - 1] = numberOfChars;
			temp[charPos] = prevChar;
			//std::cout << "at index "<< charPos -1<<" inserting " << numberOfChars << prevChar << std::endl;
			charPos+=2; 
			prevChar = currChar;
			numberOfChars = 1; 
			sizeCompressed += 2; 
		}
	}
	mSize = sizeCompressed; 
	mData = new char[sizeCompressed];
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