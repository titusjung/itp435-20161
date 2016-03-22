#pragma once
#include "DNATranslator.h"
#include "FastaReader.h"
#include <memory>
class DNAModel
{
public:
	DNAModel();
	std::shared_ptr<class DNATranslator> GetTranslator() const { return mDNATranslator;  }
	std::shared_ptr<class FastaReader> GetReader() const { return mFastaReader;  }
	void Load(std::string filename); 
	void Loaded(bool isloaded); 
	bool IsLoaded() const { return mLoaded; }
	void Clear(); 
private:
	std::shared_ptr<class DNATranslator> mDNATranslator;
	std::shared_ptr<class FastaReader> mFastaReader; 
	bool mLoaded; 
};