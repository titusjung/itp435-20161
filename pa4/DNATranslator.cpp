#include "DNATranslator.h"

DNATranslator::DNATranslator() :mTotalCount(0)
{
	Clear(); 
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
			break; 
		case 'G':
			letter = 3; 
			break;
		default:
			return; 
		}
		state = mStates[state][letter];
		if (state >= 40)
		{
			mAminoCountArray[state - 40]++;
			state = 3; 
			mTotalCount++;
		}
	}
}
void DNATranslator::Clear()
{
	for (int i = 0; i < 20; i++)
	{
		mAminoCountArray[i] = 0;
	}
	mTotalCount = 0;
}
/*
void DNATranslator::Load(const FastaReader& fastareader)
{
	int state = 0; 
	for (unsigned int i = 0; i < fastareader.mBody.size(); i++)
	{
		int letter; 
		switch (fastareader.mBody.at(i))
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
			mAminoCountArray[state - 40]++;
			state = 3; 
		}
	}
}
*/