#include "RleData.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
void RleData::Compress(const char* input, size_t inSize)
{
	// TODO
	std::string debugString = ""; 

	std::vector<char> charStor;
	std::vector<char> uniqueStor; 
	bool searchUniques = true;
	
	char prevChar = input[0];
	char currChar;
	uniqueStor.push_back(prevChar);

	int numberOfRepeats = 0;
	int numberOfUniques = 0; 
	for (size_t i = 1; i < inSize; i++)
	{
		currChar = input[i];

		if (searchUniques)
		{

			if (currChar == prevChar)
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
				
				}
				numberOfUniques = 0;
				numberOfRepeats = 2; 
				uniqueStor.clear(); 
			}
			else
			{
				numberOfUniques++;
				uniqueStor.push_back(currChar); 
			}

		}

		else
		{
			if (currChar == prevChar)
			{
				numberOfRepeats++; 
				uniqueStor.clear(); 
			}
			else
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
			}
		}

		if (i == inSize-1 && searchUniques)
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
		else if (i == inSize-1 && (!searchUniques))
		{
			charStor.push_back(numberOfRepeats);
			charStor.push_back(prevChar);

			debugString.append(std::to_string(numberOfRepeats));
			debugString += prevChar;
		}
		prevChar = currChar; 
	}

	mData = new char[charStor.size()];

	for (unsigned int i = 0; i < charStor.size(); i++)
	{
		mData[i] = charStor[i]; 
	}
	std::cout << std::endl << "compressed String is " << debugString << std::endl;

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