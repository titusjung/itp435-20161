#include "RleData.h"

void RleData::Compress(const char* input, size_t inSize)
{
	// TODO
	char*  temp = new char[inSize];

	int charPos=1;
	
	int numberOfChars=0;
	char currChar; 
	char prevChar = input[0];
	for (unsigned int i = 1; i < inSize; i++)
	{
		currChar = input[i]; 
		if (currChar == prevChar)
		{
			numberOfChars++; 
		}
		else
		{
			temp[i - 1] = numberOfChars;
			temp[i] = prevChar; 
			prevChar = currChar;
			numberOfChars = 0; 
		}
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