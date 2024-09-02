#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "../Node/Node.hpp"
#include "../Algorithm.hpp"
#include <span>
#include <unordered_map>
#include <vector>

namespace Debug
{
	auto print_frequency_map(const Algorithm::frequency_map_t& frequency_map) -> void;
	auto print_tree(const Node* root) -> void;
	auto print_letters_encodings(const std::unordered_map<char, std::vector<bool>>& letters_encodings) -> void;
	auto print_encoded_bits(const std::vector<bool>& encoded_bits) -> void;
	auto print_encoded_characters(std::span<const char> encoded_characters) -> void;
}

#endif // DEBUG_HPP