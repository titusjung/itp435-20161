#include "RleData.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
void RleData::Compress(const char* input, size_t inSize)
{
	// TODO
	delete[] mData; 
	std::string debugString = ""; 

	std::vector<char> charStor;
	std::vector<char> uniqueStor; 
	bool searchUniques = true;
	
	char prevChar = input[0];
	char currChar;
	uniqueStor.push_back(prevChar);

	int numberOfRepeats = 0;
	int numberOfUniques = 1; 
	bool checkPrev = true; 
	for (size_t i = 1; i < inSize; i++)
	{
		prevChar = input[i - 1]; 
		currChar = input[i];

		if (searchUniques)
		{

			if (currChar == prevChar && (checkPrev))
			{
				searchUniques = false;
				if (uniqueStor.size()>1)
				{
					uniqueStor.pop_back();
					int size = -static_cast<int>(uniqueStor.size());
					charStor.push_back(size);
					charStor.insert(charStor.end(), uniqueStor.begin(), uniqueStor.end());
			
					debugString.append(std::to_string(size));
					for (unsigned int j = 0; j < uniqueStor.size(); j++)
					{
						debugString += uniqueStor.at(j);
					}


					//continue; 
				}
				numberOfUniques = 0;
				numberOfRepeats = 2; 
				uniqueStor.clear(); 
			}
			else if (checkPrev)
			{
				numberOfUniques++;
				uniqueStor.push_back(currChar); 
			}

		}

		else
		{
			if (currChar == prevChar && (checkPrev))
			{
				numberOfRepeats++; 
				uniqueStor.clear(); 
			}
			else if(checkPrev)
			{
				numberOfUniques = 1; 
				searchUniques = true; 
				charStor.push_back(numberOfRepeats); 
				charStor.push_back(prevChar); 

				debugString.append(std::to_string(numberOfRepeats));
				debugString += prevChar; 

				numberOfRepeats = 0; 
				uniqueStor.clear();

				uniqueStor.push_back(currChar);
			//	std::cout << std::endl << "different char detected " << std::endl; 
				//continue;
			}
		}
		if (!checkPrev)
		{
			uniqueStor.push_back(currChar);
			checkPrev = true;
		}
		if (((size_t)numberOfRepeats) == MaxRunSize())
		{


			numberOfUniques = 1;
		//	std::cout << std::endl << "max run reached  " << debugString << std::endl;

			charStor.push_back(numberOfRepeats);
			charStor.push_back(prevChar);

			debugString.append(std::to_string(numberOfRepeats));
			debugString += prevChar;
		//	std::cout << std::endl << "max run reached  " <<debugString<< std::endl;

			numberOfRepeats = 0;

			if (!(i == inSize - 1))
			{
				uniqueStor.clear();

				searchUniques = true;
				checkPrev = false; 
				//uniqueStor.push_back(currChar);
			}
			
		}
		if (((size_t)numberOfUniques) == MaxRunSize())
		{
			int size = -static_cast<int>(uniqueStor.size());
			charStor.push_back(size);
			charStor.insert(charStor.end(), uniqueStor.begin(), uniqueStor.end());

			debugString.append(std::to_string(size));
			for (unsigned int j = 0; j < uniqueStor.size(); j++)
			{
				debugString += uniqueStor.at(j);
			}
			numberOfUniques = 0;
			uniqueStor.clear();

		}
		if (i == inSize-1)
		{
		//	std::cout << std::endl << i<<"last char is " << currChar << std::endl;

		}
		prevChar = currChar; 
	}
	if (searchUniques)
	{
		if ((!uniqueStor.empty()))
		{
			int size = -static_cast<int>(uniqueStor.size());

			charStor.push_back(size);
			charStor.insert(charStor.end(), uniqueStor.begin(), uniqueStor.end());

			debugString.append(std::to_string(size));
			for (unsigned int j = 0; j < uniqueStor.size(); j++)
			{
				debugString += uniqueStor.at(j);
			}
		}
	}
	else if ((!searchUniques))
	{
		if (numberOfRepeats > 1) {
			charStor.push_back(numberOfRepeats);
			charStor.push_back(prevChar);

			debugString.append(std::to_string(numberOfRepeats));
			debugString += prevChar;
		}
	}
	mData = new char[charStor.size()];
	mSize = charStor.size(); 
	for (unsigned int i = 0; i < charStor.size(); i++)
	{
		mData[i] = charStor[i]; 
	}
	std::cout << std::endl << "compressed String is " << debugString << std::endl;

}

void RleData::Decompress(const char* input, size_t inSize, size_t outSize)
{
	// TODO
	delete[] mData; 
	std::vector<char> charStor;
	std::string debugString = "";

	size_t i = 0; 
	int compressedNo;
	while (i < inSize)
	{
		compressedNo = (int)input[i];
		if (compressedNo < 0)
		{
			compressedNo = -compressedNo;
			for (int j = 0; j < compressedNo; j++)
			{
				charStor.push_back(input[i + 1 + j]);
				debugString.push_back(input[i + 1 + j]);
			}
			i += compressedNo+1;
		}
		else
		{
			char repeatedChar = input[i + 1]; 
			for (int j = 0; j < compressedNo; j++)
			{
				charStor.push_back(repeatedChar);
				debugString.push_back(repeatedChar);
			}
			i += 2; 
		}
	}

	mData = new char[charStor.size()];
	mSize = charStor.size();
	for (unsigned int i = 0; i < charStor.size(); i++)
	{
		mData[i] = charStor[i];
	}

//	std::cout << std::endl << "decompressed String is " << debugString << std::endl;

}

std::ostream& operator<< (std::ostream& stream, const RleData& rhs)
{
	for (int i = 0; i < rhs.mSize; i++)
	{
		stream << rhs.mData[i];
	}
	return stream;
}