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
///	std::cout << std::endl << "compressing  " <<std::endl;

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
		//puts sig into file
		mHeader.fileName = source; 
		mHeader.fileNameLength = static_cast<unsigned char > (source.length());

		mData.Compress(memblock, static_cast<int>(size));
		mHeader.fileSize = static_cast<int>(size);

		delete[] memblock; 
	}
//	std::cout << std::endl<< "making file " << source << ".rl1" << std::endl;
	std::ofstream arc(source + ".rl1",std::ios::out|std::ios::binary|std::ios::trunc);
	if (arc.is_open())
	{
		arc.write(mHeader.sig, 4);
		arc.write(reinterpret_cast<char*>(&(mHeader.fileSize)), 4);
		arc.write((char*)(&mHeader.fileNameLength), 1);
		int size2 = static_cast<int>(mHeader.fileNameLength);
		arc.write(mHeader.fileName.c_str(), size2);

		arc.write(mData.mData, mData.mSize);

		arc.close();
	}
	std::cout << std::endl << "compressed size " << mData.mSize << " original size " << size << std::endl;
	double percent = (static_cast<int>(size) - mData.mSize) /(double) size*100;
	std::cout << "percentage compressed " << percent<<"%" << std::endl; 


}

void RleFile::ExtractArchive(const std::string& source)
{
	// TODO

	std::ifstream::pos_type size;
	char* memblock;
 
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
			std::cout << "signature is " << std::hex << memblock[0] << memblock[1] << memblock[2] << memblock[3] << std::endl;

			delete[] memblock;
			return;
		}


		mHeader.fileSize = *(reinterpret_cast<int*>(&memblock[4]));
		mHeader.fileNameLength = (memblock[8]);
		mHeader.fileName = "";
		for (unsigned char i = 0; i < mHeader.fileNameLength; i++)
		{
			mHeader.fileName += memblock[9 + i];
		}
		//copying array so to remove the header
		//tried to use array arithmetic early but caused crashes for some reason
		char* arr = new char[static_cast<int>(size)];

		for (int i = 0;i < size;i++)
		{
			arr[i] = memblock[mHeader.fileNameLength + 9 + i];
		}

		mData.Decompress(arr, static_cast<size_t>(size) - 1, mHeader.fileSize);
		delete[] memblock;
		delete[] arr; 
	}
	std::ofstream arc(mHeader.fileName, std::ios::out | std::ios::binary | std::ios::trunc);

	if (arc.is_open())
	{
		arc.write(mData.mData, mData.mSize);

		arc.close();
	}
}