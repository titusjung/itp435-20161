// Main.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "Sha1.h"
#include "DictionaryAttack.h"

const std::string outputfile = "pass_solved.txt"; 
const std::string testCode = "d0c27450d749f527f7898b435d85189e9180e906"; 

int main(int argc, char* argv[])
{
	DictionaryAttack da;
	if (argc == 2)
	{
		std::string input = argv[1];
		std::string hex_str = getHexSHA1(input); 
		/*
		unsigned char hash[20];
		std::string input = argv[1];
		sha1::calc(&input, input.length(), hash);
		char hex_str[41];
		sha1::toHexString(hash, hex_str);*/
		std::cout << hex_str << std::endl;
	}
	else if (argc == 3)
	{
		std::string dict = argv[1]; 
		std::string pass = argv[2]; 
		da.loadDictionary(dict); 
		da.loadPasswordsAndPrintResults(pass, outputfile);
	}
	else
	{
		//testing code
		std::cout << "testing basic brute force code" << std::endl; 
		std::cout << bruteForce(testCode, 4) << std::endl; 
	}
	return 0;
}

