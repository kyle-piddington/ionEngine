
#pragma once

#include "ionConfig.h"
#include "ionTypes.h"
#include "ionComparison.h"

#include <iostream>


//! Portable version of system("PAUSE")
static void WaitForUser() // LCOV_EXCL_LINE
{
	std::cout << "Press [Enter] to continue . . ."; // LCOV_EXCL_LINE
	std::cin.get(); // LCOV_EXCL_LINE
} // LCOV_EXCL_LINE

#define ION_ARRAYSIZE(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

//! Count the number of digits (including a - for negative numbers) in a decimal integer
static u32 DigitCount(s32 n)
{
	u32 count = 1;
	if (n < 0)
	{
		n *= -1;
		++ count;
	}

	while (n >= 10)
	{
		++ count;
		n /= 10;
	}

	return count;
}

template <typename T>
static T const Clamp(T const & v, T const & min, T const & max)
{
	return ((v > max) ? max : ((v < min) ? min : v));
}

template <typename T>
static T const Sq(T const & a)
{
	return a * a;
}

template <typename T>
static T const Average(T const & a, T const & b)
{
	return (a + b) / 2;
}

template <typename T>
static T const Average(T const & a, T const & b, T const & c)
{
	return (a + b + c) / 3;
}

template <typename T>
static T const Average(T const & a, T const & b, T const & c, T const & d)
{
	return (a + b + c + d) / 4;
}

template <typename T>
static T const MakeEven(T const i)
{
	return (i % 2) ? (i - 1) : (i);
}

template <typename T>
s32 Sign(T const & val)
{
	return (T(0) < val) - (val < T(0));
}

template <typename T>
T ToggleBool(T & Condition)
{
	return Condition = ! Condition;
}
