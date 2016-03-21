#include "DNATranslator.h"

DNATranslator::DNATranslator()
{
	for (int i = 0; i < 20; i++)
	{
		mAmminoCountArray[i] = 0; 
	}
}

void DNATranslator::Load(const std::string & dnaString)
{
	int state = 0; 
	for (unsigned int i = 0; i < dnaString.size(); i++)
	{
		int letter; 
		switch (dnaString.at(i))
		{
		case 'T':
			letter = 0; 
			break;
		case 'C':
			letter = 1;
			break;
		case 'A':
			letter = 2;
		case 'G':
			letter = 3; 
			break;
		default:
			return; 
		}
		state = mStates[state][letter];
		if (state >= 40)
		{
			mAmminoCountArray[state - 40]++;
			state = 3; 
		}
	}
}
