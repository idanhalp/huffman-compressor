#include "Source/Algorithm/Algorithm.hpp"
#include "Source/FileProcessing/FileProcessing.hpp"
#include "Tests/Tests.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <ranges>

using namespace std;

auto main(const int argument_count, const char* arguments[]) -> int
{
	const bool has_arguments = argument_count > 1;

	if (!has_arguments)
	{
		cout << "No arguments received!\n";

		return EXIT_SUCCESS;
	}

	const string TEST_COMMAND = "test";
	const string ENCODE_COMMAND = "encode";
	const string DECODE_COMMAND = "decode";
	const vector<string> COMMANDS = {TEST_COMMAND, ENCODE_COMMAND, DECODE_COMMAND};

	const string command = arguments[1];
	const bool is_legal_command = ranges::contains(COMMANDS, command);

	if (!is_legal_command)
	{
		cout << "Illegal command!\n";

		return EXIT_SUCCESS;
	}

	const int expected_num_of_arguments = (command == TEST_COMMAND ? 2 : 4);
	const bool number_of_arguments_is_correct = argument_count == expected_num_of_arguments;

	if (!number_of_arguments_is_correct)
	{
		cout << "Incorrect number of arguments!\n";
	
		return EXIT_SUCCESS;
	}

	if (command == TEST_COMMAND)
	{
		Tests::run_tests();

		return EXIT_SUCCESS;
	}

	const string source_file = arguments[2];
	const string destination_file = arguments[3];

	if (command == ENCODE_COMMAND)
	{
		const string content = Processing::read_from_file(source_file);
		const Algorithm::EncodingInfo encoding_info = Algorithm::encode(content);
		Processing::encode_into_file(destination_file, encoding_info);

		const double compression_ratio = 1.0 * filesystem::file_size(destination_file) / filesystem::file_size(source_file);
		const double data_rate_saving = 1.0 - compression_ratio;

		cout << "Data rate saving is " << data_rate_saving << '\n';
	}
	else if (command == DECODE_COMMAND)
	{
		const Algorithm::EncodingInfo encoding_info = Processing::decode_from_file(source_file);		
		const string content = Algorithm::decode(encoding_info);
		Processing::write_into_file(destination_file, content);
	}
	
	return EXIT_SUCCESS;
}
