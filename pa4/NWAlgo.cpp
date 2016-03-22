#include "NWAlgo.h"
#include <fstream>
#include <algorithm>
void NWAlgo::Load(const std::string & filename, const  std::string & filename2)
{
	mFileA.LoadFile(filename);
	mFileB.LoadFile(filename2); 
	
	mBodyA = mFileA.GetBody();
	mBodyB = mFileB.GetBody();
}

void NWAlgo::Process()
{
	int width = mBodyA.size() + 1;
	int height = mBodyB.size() + 1;
	std::vector<std::vector<short>> scoreGrid(height, std::vector<short>(width));
	std::vector<std::vector<Direction>> directionGrid(height, std::vector<Direction>(width));

	for (int i = 0; i <width; i++)
	{
		scoreGrid[0][i] = -static_cast<short>(i); 
		directionGrid[0][i] = LEFT; 
	}
	for (int i = 0; i < height; i++)
	{
		scoreGrid[i][0] = -static_cast<short>(i);
		directionGrid[i][0] = UP; 
	}


	for (int i = 1; i < height; i++)
	{
		for (int j = 1; j < width;j++)
		{
			short match;
			if (mBodyA.at(j-1) == mBodyB.at(i-1))
			{
				match = 1;
			}
			else
			{
				match = -1; 
			}
			short scoreAboveLeft = scoreGrid[i - 1][j - 1]+match;
			short scoreLeft = scoreGrid[i][j - 1] + mGap;
			short scoreUp = scoreGrid[i-1][j] + mGap;

			if (scoreAboveLeft > scoreLeft && scoreAboveLeft > scoreUp)
			{
				scoreGrid[i][j] = scoreAboveLeft; 
				directionGrid[i][j] = UPLEFT; 
			}
			else if (scoreLeft > scoreUp)
			{
				scoreGrid[i][j] = scoreLeft;
				directionGrid[i][j] = LEFT;
			}
			else
			{
				scoreGrid[i][j] = scoreUp; 
				directionGrid[i][j] = UP;

			}
		}
	}
 
	std::string resultA = ""; 
	std::string resultB = ""; 
	int i = height - 1;
	int j = width - 1;
	mScore = scoreGrid[i][j]; 
	while (i != 0 && j != 0)
	{
		switch (scoreGrid[i][j])
		{
		case UPLEFT:
			resultA += mBodyA[i];
			resultB += mBodyB[j];
			i--;
			j--; 
			break;
		case LEFT:
			resultA += mBodyA[i];
			mResultB += "_";
			j--;
			break;
		case UP:
			resultA += "_";
			resultB += mBodyB[j];
			i--;
			break; 
		}
	}
	mResultA = "";
	for (std::string::reverse_iterator rit = resultA.rbegin(); rit != resultA.rend();++rit)
	{
		mResultA += *rit; 
	}
	mResultB = "";
	for (std::string::reverse_iterator rit = resultB.rbegin(); rit != resultB.rend();++rit)
	{
		mResultB += *rit;
	}


}

void NWAlgo::Print(const std::string & filename)
{
	std::ofstream output(filename);
	if (!output.is_open())
	{
		return; 
	}
	output <<"A: "<< mFileA.GetHeader() << std::endl;
	output <<"B: "<<  mFileB.GetHeader() << std::endl; 
	output << "Score: " << mScore << std::endl; 
	output << std::endl; 
	int i = 0;
	int j = 0;
	int i2 = 0;
	int j2 = 0;
	std::string subA = mResultA.substr(0, 70); 
	int range = std::max(mBodyA.size(), mBodyB.size())/70; 
	for (int i = 0; i < range; i++)
	{
		int i2 = i * 70;
	}
}
