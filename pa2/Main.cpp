// Main.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "Sha1.h"
#include "DictionaryAttack.h"
#include "util.h"
#include "ParallelBruteForce.h"
#include "Timer.h"
const std::string outputfile = "pass_solved.txt"; 
const std::string testCode = "70b6234f544af0132629aa6ec4be926dab59bb0b"; 

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
		da.loadPasswordsandSolve(pass);
		da.parallelBruteForceLoadedPasswords();
		da.print(outputfile); 
		
	}
	else
	{
		//testing code
		std::cout << "testing basic brute force code" << std::endl; 
		Timer timer;
		timer.start();
		ParallelBruteForce pbf; 
		pbf.parallelBruteForce(testCode);
		std::cout << pbf.getPass() << std::endl; 
		std::cout << "parallel brute force took " << timer.getElapsed() << " seconds" << std::endl;

	}
	return 0;
}

