#pragma once
#include <string>

class DNATranslator
{
public:
	DNATranslator();
	void Load(const std::string& dnaString);
	int* getResults() const { return &mAmminoCountArray;  }
private:
	 const int mStates[24][4] = {
		//St| T | C | A | G|
		//----------
		//0	
/* 0 to 23 represent states
  40 to 59 represent amino acides
  40: F 
  41: L
  42: I
  43: M
  44 V
  45 S
  46 P
  47 A
  49 Y
  50 H
  51 Q
  52 N
  53 K
  54 D
  55 E
  56 C
  57 W
  58 R
  59 G
		 */
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
	int mAmminoCountArray[20]; 
};