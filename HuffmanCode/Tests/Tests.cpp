#include "FixedTests/FixedTests.hpp"
#include "RandomTests/RandomTests.hpp"
#include "Tests.hpp"
#include <iostream>

using namespace std;

auto Tests::run_tests() -> void
{
	cout << "Running `random tests`: " << (Random::run_tests() ? "Success" : "Failure") << "!\n";
	cout << "Running `read from file test`: " << (Fixed::run_read_from_file_test() ? "Success" : "Failure") << "!\n";
	cout << "Running `encode text with single letter test`: " << (Fixed::run_encode_text_with_single_letter_test() ? "Success" : "Failure") << "!\n";
}
