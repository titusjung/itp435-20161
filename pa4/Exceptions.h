//
//  Exceptions.h
//  DNAwx
//
//  Created by Sanjay Madhav on 12/29/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <exception>

class DNAExcept : public std::exception
{
	
};

class FileLoadExcept : public DNAExcept
{
public:
	const char* what() const noexcept override { return "FASTA file load exception"; }
};
