#include <list>

namespace FileSystem
{

// Given the path to a directory and a list to populate, it fills the list with
// the names of the files in the directory
void getFilesInDirectory(const std::string& directory, std::list<std::string>& files);

// Creates the specified directory, if it doesn't already exist
void createDirectory(const std::string& directory);

} // namespace
