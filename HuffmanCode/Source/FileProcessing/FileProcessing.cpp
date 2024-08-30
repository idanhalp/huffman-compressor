#include "FileProcessing.hpp"
#include <fstream>
#include <stdexcept>

using namespace std;

auto Processing::read_file(string input_file_path) -> string
{
	ifstream input_file(input_file_path);

	if (!input_file.is_open())
	{
		throw runtime_error("Cannot open " + input_file_path + "!\n");
	}

	string line;
	string result;

	while (getline(input_file, line))
	{
		result += line;
	}

	return result;
}