#include "../../Source/Algorithm/Algorithm.hpp"
#include "RandomTests.hpp"
#include <limits>
#include <random>
#include <string>

using namespace std;

namespace Tests::Auxiliary
{
	auto generate_random_character() -> char;
	auto generate_random_string(size_t length) -> string;
}

auto Tests::Auxiliary::generate_random_character() -> char
{
	static random_device rnd;
	static mt19937 rng(rnd());
	static uniform_int_distribution<> distribution(1, numeric_limits<char>::max());

	return distribution(rng);
}

auto Tests::Auxiliary::generate_random_string(const size_t length) -> string
{
	string result;
	result.reserve(length);

	for (size_t i = 0; i < length; ++i)
	{
		result += generate_random_character();
	}

	return result;
}

auto Tests::Random::run_tests() -> bool
{
	const int num_of_tests = 10'000;
	const int string_length = 10'000;

	for (int i = 0; i < num_of_tests; ++i)
	{
		const string s = Auxiliary::generate_random_string(string_length);
		const bool decoding_is_successful = s == Algorithm::decode(Algorithm::encode(s));

		if (!decoding_is_successful)
		{
			return false;
		}
	}

	return true;
}