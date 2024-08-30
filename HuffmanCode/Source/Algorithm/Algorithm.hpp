#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <string_view>
#include <unordered_map>

namespace Algorithm
{
	typedef std::unordered_map<char, int> frequency_map_t;

	auto encode(std::string_view original_text) -> std::pair<std::string, frequency_map_t>;
	auto decode(std::string_view encoded_text, const frequency_map_t& frequency_map) -> std::string;
}

#endif // ALGORITHM_HPP