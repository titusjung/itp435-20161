#pragma once
#include <string>
#include "DNATranslator.h"
class FastaReader
{
public:
	FastaReader();
	FastaReader(const std::string& filename);
	void LoadFile(const std::string& file);
	std::string GetBody() const { return mBody;  }
	std::string GetHeader() const { return mHeaderString;  }
	void Clear(); 
	char At(int i); 
	int Size() const { return mBody.size();  }
	//friend class DNATranslator; 
private:
	std::string mHeaderString;
	std::string mBody; 
	int mSize; 
};