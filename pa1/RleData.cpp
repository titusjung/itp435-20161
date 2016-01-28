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

	//vectors were used to store the char's instead of arrays
	std::vector<char> charStor;
	std::vector<char> uniqueStor; 
	bool searchUniques = true;
	
	char prevChar = input[0];
	char currChar;
	uniqueStor.push_back(prevChar);

	int numberOfRepeats = 0;
	bool checkPrev = true; 
	// the program has two states: look for unique pattersn and look for repeating chars
	//main loop 
	for (size_t i = 1; i < inSize; i++)
	{

		prevChar = input[i - 1]; 
		currChar = input[i];
		//when i reached 127 i want to reset the loop and ignore the previous char
		// this puts the machine like it just start over
		if (!checkPrev)
		{
			checkPrev = true;
			uniqueStor.clear();

			uniqueStor.push_back(currChar);
			searchUniques = true;
			continue;
		}
		//looks for unique patterns; 
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


				}
				numberOfRepeats = 2; 
				uniqueStor.clear(); 
			}
			else if (checkPrev)
			{
				uniqueStor.push_back(currChar); 
			}

		}
		//looks for repeating patterns; 

		else
		{
			if (currChar == prevChar && (checkPrev))
			{
				numberOfRepeats++; 
			}
			else if(checkPrev)
			{
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
		// when i reach 127 repeats
		if (((size_t)numberOfRepeats) == MaxRunSize())
		{
			charStor.push_back(numberOfRepeats);
			charStor.push_back(prevChar);

			debugString.append(std::to_string(numberOfRepeats));
			debugString += prevChar;

			numberOfRepeats = 0;

			if (!(i == inSize - 1))
			{
				searchUniques = true;
				checkPrev = false; 
			}
			uniqueStor.clear();
		}
		//when the program reaches 127 run
		if (((size_t)uniqueStor.size()) == MaxRunSize())
		{
			int size = -static_cast<int>(uniqueStor.size());
			charStor.push_back(size);
			charStor.insert(charStor.end(), uniqueStor.begin(), uniqueStor.end());

			debugString.append(std::to_string(size));
			for (unsigned int j = 0; j < uniqueStor.size(); j++)
			{
				debugString += uniqueStor.at(j);
			}
			uniqueStor.clear();
			if (!(i == inSize - 1))
			{

				searchUniques = true;
				checkPrev = false;
			}
		}

	}
	/*
	last 2 if statements deal with the end of the array
	//if the program is still in a nonempty run at the end of the array, this publishes the run

	*/
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

	//copy vectory to char array: causes time issues and should find a better way
	mData = new char[charStor.size()];
	mSize = charStor.size(); 
	for (unsigned int i = 0; i < charStor.size(); i++)
	{
		mData[i] = charStor[i]; 
	}
	//std::cout << std::endl << "compressed String is " << debugString << std::endl;

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
		//		debugString.push_back(input[i + 1 + j]);
			}
			i += compressedNo+1;
		}
		else
		{
			char repeatedChar = input[i + 1]; 
			for (int j = 0; j < compressedNo; j++)
			{
				charStor.push_back(repeatedChar);
		//		debugString.push_back(repeatedChar);
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