#pragma once
#include "MiniCppUnit.hpp"
#include "RleData.h"
#include <iostream>
#include <iomanip>

// Helper functions
bool buffersAreSame(const char* expected, const char* actual, size_t size);
void runCompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);
void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);

// IMPORTANT NOTE --
// The tests all use "sizeof" to find the size of the input
// buffer. However, remember that this only works because the
// character arrays are statically allocated.
// If you just have a pointer to a C-style string, "sizeof"
// will return the size of the pointer type (either 4 or 8).
class CompressionTests : public TestFixture<CompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(CompressionTests, "Testing Compression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive runs test");
		// TODO: Add more Compression test cases
		TEST_CASE_DESCRIBE(testMixedLetterRuns, "Basic mixed letters");


		TEST_CASE_DESCRIBE(testUniqueLettersRuns, "Basic unique letters");

		TEST_CASE_DESCRIBE(testUniqueBegining, "Test if 1 unique letter at beginning");


		//TEST_CASE_DESCRIBE(testUniqueAndRepeatedRuns, "Basic unique letters");

		TEST_CASE_DESCRIBE(testLongPosRun, "basic positive long run");

		TEST_CASE_DESCRIBE(testLongNegRun, "basic positive long run");

		TEST_CASE_DESCRIBE(testBasicRun, "basic  run");

		TEST_CASE_DESCRIBE(testSimpleRun, "basic  run");

		//	TEST_CASE_DESCRIBE(testLongNegRun, "Basic unique letters");

	//	TEST_CASE_DESCRIBE(testAlternatingRun, "Basic unique letters");

		//TEST_CASE_DESCRIBE(testBeyondMax, "Basic unique letters");



	}
	void testSimpleRun()
	{
		char test[] = "a";
		char expected[] = "\xff""a";
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
	void testBasicRun()
	{
		char test[] = "aaa";
		char expected[] = "\x03""a";
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

	}
	void testLongNegRun()
	{
		char test[128];
		char expected[129];
		expected[0] = '\x81'; 
		for (int i = 0; i < 127; i+=2)
		{
			test[i] = 'f';
			test[i + 1] = 'g';
		}
		for (int i = 1; i < 128 ; i += 2)
		{
			expected[i] = 'f';
			expected[i + 1] = 'g';
		}


		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

	}

	void testLongPosRun()
	{
		char test[128];
		for (int i = 0; i < 128; i++)
		{
			test[i] = 'f';
		}
		char expected[] = "\x07f";//"a""\x07f" "a";
		std::cout << "size of array is " << test[126] << std::endl;
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

	}
	void testUniqueBegining()
	{
		char test[] = "z" "aaaaaa";
		char expected[] = "\xff" "z" "\x06" "a";
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}

	void testMixedLetterRuns()
	{
		char test[] = "aaaaaa""bb""cc""ddddd""a";
		char expected[] = "\x06" "a" "\x02" "b" "\x02" "c" "\x05" "d" "\xff" "a"; 
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

	}
	void testUniqueLettersRuns()
	{
		char test[] = "abcdefg";
		char expected[] = "\xf9" "abcdefg";
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
	void testBasicPositiveRuns()
	{
		char test[] = "aaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbc"
			"ccdddaaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbcccddd";
		char expected[] = "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d";
		
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	
	}
};

class DecompressionTests : public TestFixture<DecompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(DecompressionTests, "Testing Decompression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic Decompression positive run test");

		TEST_CASE_DESCRIBE(testBasicNegativeRuns, "Basic Decompression negative run test");

		TEST_CASE_DESCRIBE(testBasicMixedeRuns, "Basic Decompression mixed run test");

		TEST_CASE_DESCRIBE(testBasicNegativeRuns2, "Basic Decompression negative run test");


		//TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic Decompression positive run test");

		// TODO: Add more Decompression test  cases
	}

	void testBasicNegativeRuns2()
	{
		char test[] = "\x28"  "x" "\xf9" "abcdefg" "\x28"  "x";
		char expected[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx""abcdefg""xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
	void testBasicMixedeRuns()
	{
		char test[] = "\xf9" "abcdefg""\x28"  "x" "\xf9" "abcdefg";
		char expected[] = "abcdefg""xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx""abcdefg";
		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

	}

	void testBasicNegativeRuns()
	{
		char test[] = "\xf9" "abcdefg";
		char expected[] = "abcdefg";

		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
	void testBasicPositiveRuns()
	{
		char test[] = "\x28"  "x";
		char expected[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		
		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
};

REGISTER_FIXTURE(CompressionTests);
REGISTER_FIXTURE(DecompressionTests);

bool buffersAreSame(const char* expected, const char* actual, size_t size)
{
	if (actual == nullptr)
	{
		std::cerr << std::endl << "Actual data is null." << std::endl;
		return false;
	}

	bool retVal = true;

	for (size_t i = 0; i < size; i++)
	{
		if (expected[i] != actual[i])
		{
			retVal = false;
			std::cerr << std::endl
				<< "Expected 0x" << std::hex << static_cast<unsigned>(expected[i])
				<< " at index " << std::dec << i << " but saw 0x"
				<< std::hex << static_cast<unsigned>(actual[i]) << std::endl;
			break;
		}
	}

	return retVal;
}

void runCompressionTest(char* test, size_t testSize, 
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Compress(test, testSize);
	//std::cout <<std::endl<< "compression string is " << r << std::endl;
	//std::cout << "compressed size is " << r.mSize << " expected size is " << expectedSize << std::endl; 
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");

}

void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Decompress(test, testSize, expectedSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}
