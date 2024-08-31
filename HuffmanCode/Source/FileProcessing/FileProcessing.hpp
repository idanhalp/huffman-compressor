#ifndef FILE_PROCESSING_HPP
#define FILE_PROCESSING_HPP

#include "../Algorithm/Algorithm.hpp"
#include <string>

namespace Processing
{
	auto read_file(std::string input_file_path) -> Algorithm::EncodingInfo;
	auto write_file(std::string output_file_path, const Algorithm::EncodingInfo& encoding_info) -> void;
}

#endif // FILE_PROCESSING_HPP