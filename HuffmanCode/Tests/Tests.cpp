#include "RandomTests/RandomTests.hpp"
#include "Tests.hpp"
#include <iostream>

using namespace std;

auto Tests::run_tests() -> void
{
	cout << "Running random tests: ";
	cout << (Random::run_tests() ? "Success!\n" : "Failure!\n");
}
