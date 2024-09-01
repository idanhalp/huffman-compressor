#include "../../Source/FileProcessing/FileProcessing.hpp"
#include "FixedTests.hpp"
#include <filesystem>
#include <string>

using namespace std;

auto Tests::Fixed::run_read_from_file_test() -> bool
{
	const string path_to_files = "./Tests/FixedTests/Files/";
	const string file_suffix = ".txt";
	const string file_name = "MobyDick";
	
	const string input_file_name = path_to_files + file_name + file_suffix;
	const string original_content = Processing::read_from_file(input_file_name);

	const string encoded_info_file_name = path_to_files + file_name + "Compressed" + file_suffix;
	Processing::encode_into_file(encoded_info_file_name, Algorithm::encode(original_content));
	
	const Algorithm::EncodingInfo restored_encoding_info = Processing::decode_from_file(encoded_info_file_name);
	const string restored_file_name = path_to_files + file_name + "Restored" + file_suffix;
	Processing::write_into_file(restored_file_name, Algorithm::decode(restored_encoding_info));

	const bool text_decoded_successfully = Processing::read_from_file(input_file_name) == Processing::read_from_file(restored_file_name);

	filesystem::remove(encoded_info_file_name);
	filesystem::remove(restored_file_name);

	return text_decoded_successfully;
}