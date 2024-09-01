#ifndef FILE_PROCESSING_HPP
#define FILE_PROCESSING_HPP

#include "../Algorithm/Algorithm.hpp"
#include <string>

namespace Processing
{
	auto encode_into_file(std::string output_file_path, const Algorithm::EncodingInfo& encoding_info) -> void;
	auto decode_from_file(std::string input_file_path) -> Algorithm::EncodingInfo;
}

#endif // FILE_PROCESSING_HPP