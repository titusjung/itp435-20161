#include "RLEFile.h"
#include "RleData.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "FileSystem.h"

void RleFile::CreateArchive(const std::string& source)
{
	// TODO
	std::ifstream::pos_type size;
	char* memblock;
	std::cout << std::endl << "compressing  " <<std::endl;

	std::ifstream file(source, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char[static_cast<int>(size)];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();

		mHeader.sig[0] = 'R';
		mHeader.sig[1] = 'L';
		mHeader.sig[2] = 'E';
		mHeader.sig[3] = '\x01';

		mHeader.fileSize = static_cast<int>(size);
		mHeader.fileName = source; 
		mHeader.fileNameLength = static_cast<unsigned char > (source.length());

		mData.Compress(memblock, static_cast<int>(size));
		delete[] memblock; 
	}
	std::cout << std::endl<< "making file " << source << ".rl1" << std::endl;
	std::ofstream arc(source + ".rl1");
	arc.write(mHeader.sig, 4);
	arc.write(reinterpret_cast<char*>(&(mHeader.fileSize)), 4);
	arc.write(reinterpret_cast<char*>(&mHeader.fileNameLength), 1);
	arc.write(mHeader.fileName.c_str(), mHeader.fileNameLength);

	arc.write(mData.mData, mData.mSize); 

	arc.close(); 
	std::cout << std::endl << "compressed size " << mData.mSize << " original size " << size << std::endl;
	double percent = (static_cast<int>(size) - mData.mSize) /(double) size*100;
	std::cout << "percentage compressed " << percent<<"%" << std::endl; 

}

void RleFile::ExtractArchive(const std::string& source)
{
	// TODO

	std::ifstream::pos_type size;
	char* memblock;
	std::cout << std::endl << "decompressing  " << std::endl;
	char* compressedData; 
	std::ifstream file(source, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char[static_cast<int>(size)];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();

		if (
			memblock[0] != 'R' ||
			memblock[1] != 'L' ||
			memblock[2] != 'E' ||
			memblock[3] != '\x01')
		{
			std::cerr << std::endl <<
				"incorrect signature! aborting " << std::endl;
			std::cout << "signature is " << memblock[0] << memblock[1] << memblock[2] << memblock[3] << std::endl;
			
			delete[] memblock;
			return;
		}


		mHeader.fileSize = *(reinterpret_cast<int*>(&memblock[4]));
		mHeader.fileNameLength = ( memblock[8]);
		mHeader.fileName = "";
		for (unsigned char i = 0; i < mHeader.fileNameLength; i++)
		{
			mHeader.fileName += memblock[9 + i];
		}
		std::cout << std::endl << " file name length " << mHeader.fileNameLength << std::endl;

		std::cout << std::endl << "making file " << mHeader.fileName << std::endl;

		compressedData = memblock+ mHeader.fileNameLength+9;
		std::cout << "file size is " << mHeader.fileSize << std::endl;

		mData.Decompress(compressedData, static_cast<size_t>(mHeader.fileSize)-1, mHeader.fileSize);
		delete[] memblock;
	}
	std::cout << std::endl << "making file " << mHeader.fileName << std::endl;
	std::ofstream arc(mHeader.fileName);


	arc.write(mData.mData, mData.mSize);

	arc.close();
}
