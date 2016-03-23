#include "NWAlgo.h"
#include <fstream>
#include <algorithm>
void NWAlgo::Load(const std::string & filename, const  std::string & filename2)
{
	mFileA.LoadFile(filename);
	mFileB.LoadFile(filename2); 
	
	//mBodyA = mFileA.GetBody();
	//mBodyB = mFileB.GetBody();
}

void NWAlgo::Process()
{
	mResultA.clear();
	mResultB.clear(); 
	int width = mFileA.Size() + 1;
	int height = mFileB.Size() + 1;

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
			char a = mFileA.At(j - 1);
			char b = mFileB.At(i - 1);
			if (a == b)
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

			if (scoreAboveLeft >= scoreLeft && scoreAboveLeft >= scoreUp)
			{
				scoreGrid[i][j] = scoreAboveLeft; 
				directionGrid[i][j] = UPLEFT; 
			}
			else if (scoreLeft >= scoreUp)
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
	while (i != 0 || j != 0)
	{
		switch (directionGrid[i][j])
		{
		case UPLEFT:
		//	if (mBodyA[j] != '\0')
			{
				mResultA += mFileA.At(j-1);

			}
			//if (mBodyB[i] != '\0')
			{
				//mResultB += mBodyB[i-1];
				mResultB += mFileB.At( i- 1);

			}
			i--;
			j--; 
			break;
		case LEFT:
		//	if (mBodyA[j] != '\0')
			{
				//mResultA += mBodyA[j-1];
				mResultA += mFileA.At(j - 1);

			}
			mResultB += "_";
			j--;
			break;
		case UP:
			mResultA += "_";
		//	if (mBodyB[i] != '\0')
			{
				//mResultB += mBodyB[i-1];
				mResultB += mFileB.At(i - 1);

			}	
			i--;
			break; 
		}
	}
	std::reverse(mResultA.begin(), mResultA.end());
	std::reverse(mResultB.begin(), mResultB.end());
	/*
	std::ofstream output("test.txt", std::fstream::out, std::fstream::trunc);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width;j++)
		{
			switch (directionGrid[i][j])
			{
			case UPLEFT:
				output << "UL ";
				break;
			case LEFT:
				output << "LE ";
				break;
			case UP:
				output << "UP ";
				break;
			}
		}
		output << std::endl; 

	}
	output.close(); */
	/*
	for (std::string::reverse_iterator rit = resultA.rbegin(); rit != resultA.rend();++rit)
	{
		mResultA += *rit; 
	}
	mResultB = "";
	for (std::string::reverse_iterator rit = resultB.rbegin(); rit != resultB.rend();++rit)
	{
		mResultB += *rit;
	}*/


}

void NWAlgo::Print(const std::string & filename)
{
	std::ofstream output(filename, std::fstream::out, std::fstream::trunc);
	if (!output.is_open())
	{
		return; 
	}
	output <<"A: "<< mFileA.GetHeader() << std::endl;
	output <<"B: "<<  mFileB.GetHeader() << std::endl; 
	output << "Score: " << mScore << std::endl; 
	output << std::endl; 
	output.flush(); 
	
	unsigned int range = std::max(mResultA.size(), mResultB.size());
	std::string stringA = "";
	std::string stringB = "";
	std::string connectString = ""; 
	for (unsigned int i = 0; i < range; i++)
	{

		if (i < mResultA.size())
		{
			if (mResultA[i] != '\0')
			{
				stringA.push_back(mResultA.at(i));
			}
		}
		if (i < mResultB.size())
		{
			if (mResultB[i] != '\0')
			{
				stringB.push_back(mResultB.at(i));
			}
		}
		if (i < mResultA.size() && i < mResultB.size() && mResultA.at(i) == mResultB.at(i))
		{
			if (mResultA[i] != '\0')
			{
				connectString.push_back('|');
			}
		}
		else
		{
			connectString.push_back(' ');
		}
		if (connectString.size()%70==0 && i!=0)
		{

			std::string printString = stringA + "\n" + connectString + "\n" + stringB+"\n \n";
			output << printString; 
			/*
			output << stringA << std::endl;
			output << connectString << std::endl; 
			output << stringB << std::endl;
			output << std::endl;
			output.flush();
			*/
			stringA.clear(); 
			stringB.clear();
			connectString.clear(); 

		}
	}
	
	std::string printString = stringA + "\n" + connectString + "\n" + stringB+"\n \n";
	output << printString; 
	//output << stringA << std::endl;
	//output << connectString << std::endl;
	//output << stringB << std::endl;
	//output << std::endl;
	//std::string hello = "helloworld";
	//output << hello << "\n";
	output.flush(); 

	output.close(); 
}
