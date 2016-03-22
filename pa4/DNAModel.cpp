#include "DNAModel.h"

DNAModel::DNAModel() :mLoaded(false)
{
		mDNATranslator = std::make_shared<DNATranslator>(); 
		mFastaReader = std::make_shared<FastaReader>(); 
}

void DNAModel::Load(std::string filename)
{
	mFastaReader->LoadFile(filename);
	mDNATranslator->Load(mFastaReader->GetBody());
	Loaded(true); 
}

void DNAModel::Loaded(bool isloaded)
{
	mLoaded = isloaded;
}

void DNAModel::Clear()
{
	mDNATranslator->Clear();
	mFastaReader->Clear(); 
}


