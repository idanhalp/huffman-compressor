#ifndef FILE_PROCESSING_HPP
#define FILE_PROCESSING_HPP

#include <string>
#include <string_view>

namespace Processing
{
	auto read_file(std::string input_file_path) -> std::string;
	auto write_file(std::string_view content, std::string output_file_path) -> void;
}

#endif // FILE_PROCESSING_HPP