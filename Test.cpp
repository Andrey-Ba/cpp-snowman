#include <iostream>

/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: <Andrey Bakhrakh>
 * 
 * Date: 2021-02
 */

#include "doctest.h"
#include "snowman.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}


TEST_CASE("Good snowman code") {
    CHECK(nospaces(snowman(11114411)) == nospaces("_===_\n(.,.)\n( : )\n( : )"));
    /* Add more checks here */
}

TEST_CASE("Bad snowman code") {
    CHECK_THROWS(snowman(555));
    /* Add more checks here */
}


/* Add more test cases here */

// Error is thrown if any of the digits are 0 or over 4
TEST_CASE("Check digits")
{
	CHECK_THROWS(snowman(44444445));
	CHECK_THROWS(snowman(44444454));
	CHECK_THROWS(snowman(44444544));
	CHECK_THROWS(snowman(44445444));
	CHECK_THROWS(snowman(44454444));
	CHECK_THROWS(snowman(44544444));
	CHECK_THROWS(snowman(45444444));
	CHECK_THROWS(snowman(54444444));
	CHECK_THROWS(snowman(44444440));
	CHECK_THROWS(snowman(44444404));
	CHECK_THROWS(snowman(44444044));
	CHECK_THROWS(snowman(44440444));
	CHECK_THROWS(snowman(44404444));
	CHECK_THROWS(snowman(44044444));
	CHECK_THROWS(snowman(40444444));
	CHECK_THROWS(snowman(04444444));
}

// Error is thrown if the number has less than 8 digits
TEST_CASE("Num of digits")
{
	CHECK_THROWS(snowman(1));
	CHECK_THROWS(snowman(11));
	CHECK_THROWS(snowman(111));
	CHECK_THROWS(snowman(1111));
	CHECK_THROWS(snowman(11111));
	CHECK_THROWS(snowman(111111));
	CHECK_THROWS(snowman(1111111));
	CHECK_THROWS(snowman(111111111));
	CHECK_THROWS(snowman(1111111111));
}

// Check few specific outcomes
TEST_CASE("Random snowmans check")
{
	CHECK(nospaces(snowman(12341234))==nospaces("_===_\n (O.-)/\n<(> <) \n(   )"));
	CHECK(nospaces(snowman(44132213))==nospaces(" ___ \n(_*_)\n\\(. O)/\n ( : ) \n (___)"));
	CHECK(nospaces(snowman(31243412))==nospaces("   _ \n  /_\\\n(o,-) \n /( : ) \n (\" \") "));
	CHECK(nospaces(snowman(44444444))==nospaces(" ___ \n(_*_)\n (- -) \n (   ) \n (   ) "));
}

void int_to_array(int *arr, int n)
{
	int i = 7;
	while(n > 0)
	{
		arr[i] = n%10;
		n /= 10;
		i--;
	}
}

/* 
	L = length of string
	H = 1 -> L += 5, H = 2,4 -> L += 8, H = 3 -> L += 4
	N = 1,2,3 -> L += 1, N = 4 -> L += 0
	L,R -> L += 1
	X,Y = 1,2,3 -> L += 1
	L += 2 For the head's brackets
	T = 1 -> L += 3, H = 2,3 -> L += 4, H = 4 -> L += 2
	B = 1 -> L += 3, B = 2 -> L += 4, B = 3 -> L += 5, B = 4 -> L += 2
*/
int calc_length(int n)
{
	int arr[8] = {0};
	int_to_array(arr, n);
	int length = 0;
		 if(arr[0] == 1) length += 5;
		 else if(arr[0] == 2 || arr[0] == 4) length +=8;
		 else length += 4;
		 if(arr[1] != 4) length++;
		 length += 2; // L, R
		 if(arr[4] != 4) length++;
		 if(arr[5] != 4) length++;
		 length += 2; // For the head's brackets
		 if(arr[6] == 1) length += 3;
		 else if(arr[6] == 4) length += 2;
		 else length +=4;
		 if(arr[7] == 1) length +=3;
		 else if(arr[7] == 2) length +=4;
		 else if(arr[7] == 3) length +=5;
		 else length += 2;
	return length;
}

// Check length of returned string after removing spaces
TEST_CASE("Check length of string")
{
	for(int i = 11111111; i <= 44444444; i++)
	{
		int r = 1; // Which digit of i I'm checking now.
		while(r < 10000000)
		{
			int j = i / r; // Get the current digit we check.
			int temp = j % 10; // Temp now holds the digit.
			if(temp == 5) // Check if it reached 5.
			{
				i -= 4*r; // For example if i = 11111151, then r = 10 and after the line i = 11111111
				i += r*10; // Now we add to the digit after 1, so we get i = 11111211
			}
			r *= 10; // Go to the next digit.
			// Note: Even if the next digit is 5, it will end up to be 1 in the next run and so on.
		}
		CHECK(nospaces(snowman(i)).length() == calc_length(i)); // Left to check if the valid integer we got have the right length.
	}
}

// Check for negative numbers
TEST_CASE("Type test")
{
	CHECK_THROWS(snowman(-11111111));
}