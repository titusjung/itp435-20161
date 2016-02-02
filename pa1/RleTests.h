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



		TEST_CASE_DESCRIBE(testLongPosRun, "basic positive long run");

		TEST_CASE_DESCRIBE(testLongNegRun, "basic negative long run");

		TEST_CASE_DESCRIBE(testBasicRun, "basic 3 a run");

		TEST_CASE_DESCRIBE(testSimpleRun, "basic 1 a run");


		TEST_CASE_DESCRIBE(testMixedLongRuns, "basic long mixed run");
		
		TEST_CASE_DESCRIBE(testLongerPosRun, "basic multi  long run");
		TEST_CASE_DESCRIBE(testLongerPosNegRun, "basic multi Pos and Neg  long run");

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
	void testMixedLongRuns()
	{
		char test[394] = 
			"fgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"gfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg"
			"gggggggggggg"
			"fgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"gfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			;
		char expected[]
			= "\x81"
			"fgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"gfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"\x07f"
			"g"
			"\x0c"
			"g"
			"\x81"
			"fgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"gfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf";
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

	}
	void testLongNegRun()
	{
		char test[257] = "fgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfg";
		char expected[260] ="\x81"
			"fgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"gfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"\x81"
			"gfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfg"
			"fgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"gfgfgfgfgfgfgfgfgfgfgfgfgfg"
			"fgfgfgfgfgfgfgfgfgfgfg"
			"\xfe""fg"
			;

		std::cout << std::endl;


		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

	}
	void testLongerPosRun()
	{
		char test[] =
		"fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
"fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff""a"
"fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
		char expected[] = "\x7f" "f"
			"\x7f" "f"
			"\xff""a"
			"\x7f" "f";
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

	}
	void testLongerPosNegRun()
	{
		char test[] =
			"fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
			"fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
			"fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"

			"fgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"gfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
		char expected[] = "\x07f" "f"
			"\x07f" "f"			"\x07f" "f"

			"\x81"
			"fgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"
			"gfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgfgf"	
			"\x07f" "f";
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

	}
	void testLongPosRun()
	{
		char test[128];
		for (int i = 0; i < 128; i++)
		{
			test[i] = 'f';
		}
		char expected[] = "\x07f" "f";//"a""\x07f" "a";
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

		TEST_CASE_DESCRIBE(testBasicPositiveRuns2, "Basic Decompression positive  run test 2");


		// TODO: Add more Decompression test  cases
	}
	void testBasicPositiveRuns2()
	{
		char expected[] = "aaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbc"
			"ccdddaaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbcccddd";
		char test[] = "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d";

		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);

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
bool sizesAreSame(size_t actual , size_t expected)
{
	if (actual!=expected)
	{
		std::cerr << std::endl <<
			"size mismatch expected: " << expected <<
			" actual " << actual << std::endl;
		return false;
	}
	return true; 
}
void runCompressionTest(char* test, size_t testSize, 
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Compress(test, testSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
	ASSERT_TEST_MESSAGE(sizesAreSame(r.mSize, expectedSize),
		"sizes mismatch (see above for details)");
}

void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Decompress(test, testSize, expectedSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}
