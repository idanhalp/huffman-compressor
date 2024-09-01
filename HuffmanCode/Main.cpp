#include "Source/Algorithm/Algorithm.hpp"
#include "Source/FileProcessing/FileProcessing.hpp"
#include <iostream>

using namespace std;

auto main(const int argument_count, const char* arguments[]) -> int
{
	const int expected_num_of_arguments = 4; // Program name, command, source file, destination file.
	const bool number_of_argument_is_correct = argument_count == expected_num_of_arguments;

	if (!number_of_argument_is_correct)
	{
		cout << "Incorrect number of arguments!\n";
	
		return EXIT_SUCCESS;
	}

	const string command = arguments[1];
	const string source_file = arguments[2];
	const string destination_file = arguments[3];

	if (command == "encode")
	{
		const string content = Processing::read_from_file(source_file);
		const Algorithm::EncodingInfo encoding_info = Algorithm::encode(content);
		Processing::encode_into_file(destination_file, encoding_info);
	}
	else if (command == "decode")
	{
		const Algorithm::EncodingInfo encoding_info = Processing::decode_from_file(source_file);		
		const string content = Algorithm::decode(encoding_info);
		Processing::write_into_file(destination_file, content);
	}
	else
	{
		cout << "Illegal command!\n";
	}
	
	return EXIT_SUCCESS;
}
