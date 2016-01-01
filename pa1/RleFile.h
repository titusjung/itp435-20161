#pragma once
#include "RleData.h"
#include <string>
#include <list>

class RleFile
{
	struct header
	{
		char sig[4];
		int fileSize;
		unsigned char fileNameLength;
		std::string fileName;
	} mHeader;

	RleData mData;

public:
	void CreateArchive(const std::string& source);

	void ExtractArchive(const std::string& source);
};
