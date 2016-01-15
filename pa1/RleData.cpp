#include "RleData.h"

void RleData::Compress(const char* input, size_t inSize)
{
	// TODO
	char*  temp = new char[inSize];

	int charPos=1;
	int numPos=0; 
	char currChar; 
	char prevChar = input[numPos];
	for (int i = 1; i < inSize; i++)
	{
		currChar = input[i]; 
		if (currChar == prevChar)
		{

		}
		else
		{

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