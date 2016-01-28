// Main.cpp : Defines the entry point for the console application.
//

#include "RleTests.h"
#include "RleData.h"
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include "RLEFile.h"

void Part1Tests()
{
	TestFixtureFactory::theInstance().runTests();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		// Just the tests
		Part1Tests();
	}
	else
	{
		RleFile rFile;
		std::string target= argv[1];
		/*
		//tried to get file names with spaces to work but ran out of time
		for (int i = 1; i < argc; i++)
		{
			target += argv[i];
		}*/


		if (target.substr(target.size() - 3, target.size())=="rl1")
		{
			rFile.ExtractArchive(target);
		}
		else
		{
			rFile.CreateArchive(target);
		}

		// TODO: Get the file name from argv[1] and either compress/decompress
	}
	return 0;
}

