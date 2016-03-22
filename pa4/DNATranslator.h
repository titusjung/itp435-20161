#pragma once
#include <string>
#include "FastaReader.h"
/*
static enum AminoAcids
{
	Phenylalanine,
	Leucine,
	Isoleucine,
	Methionine,
	Valine,
	Serine,
	Proline,
	Threonine,
	Alanine,
	Tyrosine,
	Histidine,
	Glutamine,
	Asparagine,
	Lysine,
	Aspartic_acid,
	Glutamic_acid,
	Cysteine,
	Tryptophan,
	Arginine,
	Glycine
};*/
class DNATranslator
{
public:
	DNATranslator();
	void Load(const std::string& dnaString);
	void Clear(); 
//	void Load(const FastaReader& fastareader);

	//int* getResults() const { return mAminoCountArray;  }
	int GetPhenylalanine() const {return mAminoCountArray[0];}
	int GetLeucine() const {return mAminoCountArray[1];}
	int GetIsoleucine() const {return mAminoCountArray[2];}
	int GetMethionine() const {return mAminoCountArray[3];}
	int GetValine() const {return mAminoCountArray[4];}
	int GetSerine() const {return mAminoCountArray[5];}
	int GetProline() const {return mAminoCountArray[6];}
	int GetThreonine() const {return mAminoCountArray[7];}
	int GetAlanine() const {return mAminoCountArray[8];}
	int GetTyrosine() const {return mAminoCountArray[9];}
	int GetHistidine() const {return mAminoCountArray[10];}
	int GetGlutamine() const {return mAminoCountArray[11];}
	int GetAsparagine() const {return mAminoCountArray[12];}
	int GetLysine() const {return mAminoCountArray[13];}
	int GetAspartic_Acid() const {return mAminoCountArray[14];}
	int GetGlutamic_Acid() const {return mAminoCountArray[15];}
	int GetCysteine() const {return mAminoCountArray[16];}
	int GetTryptophan() const {return mAminoCountArray[17];}
	int GetArginine() const {return mAminoCountArray[18];}
	int GetGlycine() const {return mAminoCountArray[19];}
	int GetTotal() const { return mTotalCount; }
private:
	 const int mStates[24][4] = {
		//St| T | C | A | G|
		//----------
		//0	
/* 0 to 23 represent states
  40 to 59 represent amino acides
  40: F Phenylalanine
  41: L Leucine
  42: I  Isoleucine
  43: M Methionine
  44 V Valine
  45 S Serine
  46 P Proline
  47 T Threonine
  48 A Alanine
  49 Y Tyrosine
  50 H Histidine
  51 Q Glutamine
  52 N Asparagine
  53 K  Lysine
  54 D  Aspartic acid 	
  55 E Glutamic acid
  56 C Cysteine
  57 W Tryptophan    
  58 R  Arginine
  59 G  Glycine
		 */
	//St| T | C | A | G|
		{ 0, 0 , 1 ,  0 },
		//1 | 2 | 0 | 0 | 0 |
		{ 2 , 0 , 1 , 0 },
		// 2 |0 | 0 | 0 | 0 |	 
		{ 0 , 0 , 1, 43 },

		//3	
		{ 4, 9, 14, 19 },

		//4   
		{ 5, 6, 7 ,  8 },
		//5   
		{ 40, 40, 41, 41 },
		//6  
		{ 45, 45, 45, 45 },
		//7  
		{ 49, 49, 0 , 0 },
		//8  
		{ 56, 56, 0 , 57 },

		//9  
		{ 10 , 11, 12 , 13 },
		//10 
		{ 41, 41, 41, 41 },
		//11 
		{ 46, 46, 46, 46 },
		//12 
		{ 50, 50, 51, 51 },
		//13 
		{ 58, 58, 58, 58 },

		//14
		{ 15 , 16, 17 , 18 },
		//15
		{ 42, 42, 42, 43 },
		//16
		{ 47, 47, 47, 47 },
		//17 
		{ 52, 52, 53, 53 },
		//18 
		{ 45, 45, 58, 58 },

		//19
		{ 20 , 21, 22, 23 },
		//20 
		{ 44, 44, 44, 44 },
		//21
		{ 48, 48, 48 ,48 },
		//22
		{ 54, 54, 55 ,55 },
		//23
		{ 59, 59, 59 , 59 }
	}; 
	int mAminoCountArray[20];
	int mTotalCount; 
};