#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <string_view>
#include <unordered_map>
#include <vector>

namespace Algorithm
{
	typedef std::unordered_map<char, int> frequency_map_t;
	
	struct EncodingInfo
	{
		std::vector<char> encoded_characters;
		frequency_map_t frequency_map;
		size_t total_bits;
	};

	auto encode(std::string_view original_text) -> EncodingInfo;
	auto decode(const EncodingInfo& encoding_info) -> std::string;
}

#endif // ALGORITHM_HPP