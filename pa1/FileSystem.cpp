#include "FileSystem.h"
#include <string>

#ifdef _WIN32
// Windows
#include <windows.h>
#else
// Mac
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#endif

namespace FileSystem
{

#ifdef _WIN32
// Windows
void getFilesInDirectory(const std::string& directory, std::list<std::string>& files)
{
	files.clear();

	// Find the first file in the directory.
	WIN32_FIND_DATA ffd;
	std::string path = directory + "\\*.*";
	HANDLE hFind = FindFirstFile(path.c_str(), &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		// No files found, display error message and return!
		return;
	}

	// Add all files in this directory to a list of strings
	do
	{
		std::string temp = ffd.cFileName;
		if (temp != "." && temp != ".." &&
			!(ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			files.push_back(temp);
		}
	} while (FindNextFile(hFind, &ffd) != 0);
}

void createDirectory(const std::string& directory)
{
	CreateDirectory(directory.c_str(), NULL);
}
#else
// Mac
void getFilesInDirectory(const std::string& directory, std::list<std::string>& files)
{
	// Thanks http://www.lemoda.net/c/list-directory/
	DIR* d;
	const char* dir_name = directory.c_str();
	
	// Open
	d = opendir(dir_name);
	
	if (d)
	{
		while (1)
		{
			dirent* entry;
			
			entry = readdir(d);
			if (!entry)
			{
				break;
			}
			
			std::string fileName(entry->d_name);
			
			// Ignore hidden stuff
			if (fileName[0] != '.')
			{
				files.push_back(fileName);
			}
		}
		
		// Close
		closedir(d);
	}
}
	
void createDirectory(const std::string& directory)
{
	mkdir(directory.c_str(), 0700);
}
#endif

} // namespace