#include "FixedTests/FixedTests.hpp"
#include "RandomTests/RandomTests.hpp"
#include "Tests.hpp"
#include <print>

using namespace std;

auto Tests::run_tests() -> void
{
	println("Running `random tests`: {}", (Random::run_tests() ? "Success" : "Failure"));
	println("Running `read from file test`: {}", (Fixed::run_read_from_file_test() ? "Success" : "Failure"));
	println("Running `encode text with single letter test`: {}", (Fixed::run_encode_text_with_single_letter_test() ? "Success" : "Failure"));
}
