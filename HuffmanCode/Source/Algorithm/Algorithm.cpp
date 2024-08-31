#include "Algorithm.hpp"
#include "Debug/Debug.hpp"
#include "Node/Node.hpp"
#include <limits>
#include <queue>
#include <ranges>
#include <stdexcept>
#include <utility>
#include <string>
#include <vector>

using namespace std;

namespace Algorithm::Auxiliary
{
	auto create_frequency_map(string_view text) -> frequency_map_t;
	auto create_tree(const frequency_map_t& frequency_map) -> Node*;
	auto find_letters_encodings(const Node* root) -> unordered_map<char, vector<bool>>;
	auto encode_to_bits(string_view original_text, const unordered_map<char, vector<bool>>& letters_encoding) -> vector<bool>;
	auto encode_bits_as_characters(const vector<bool>& encoded_bits) -> vector<char>;
}

auto Algorithm::encode(string_view original_text) -> EncodingInfo
{
	const frequency_map_t frequency_map = Auxiliary::create_frequency_map(original_text);
	Node* root = Auxiliary::create_tree(frequency_map); // ! Use a std::unique_ptr.
	const unordered_map<char, vector<bool>> letters_encodings = Auxiliary::find_letters_encodings(root);
	const vector<bool> encoded_bits = Auxiliary::encode_to_bits(original_text, letters_encodings);	
	const vector<char> encoded_characters = Auxiliary::encode_bits_as_characters(encoded_bits);

	Debug::print_encoded_bits(encoded_bits);
	Debug::print_encoded_characters(encoded_characters);

	delete root;

	return {encoded_characters, frequency_map, encoded_bits.size()};
}

auto Algorithm::decode([[maybe_unused]] const EncodingInfo& encoding_info) -> string
{
	std::runtime_error("`Algorithm::decode` is not implemented yet!\n");
	unreachable();
}

auto Algorithm::Auxiliary::create_frequency_map(string_view text) -> frequency_map_t
{
	frequency_map_t frequency_map;

	for (const char c : text)
	{
		++frequency_map[c];
	}

	return frequency_map;
}

auto Algorithm::Auxiliary::create_tree(const frequency_map_t& frequency_map) -> Node*
{
	auto compare_nodes = [] (const Node* node1, const Node* node2) -> bool {return *node1 > *node2; };
	priority_queue<Node*, vector<Node*>, decltype(compare_nodes)> heap(compare_nodes); // Min heap ordered by nodes' frequency.
	
	for (const auto [character, frequency] : frequency_map)
	{
		heap.push(new Node(frequency, character));
	}

	while (heap.size() > 1)
	{
		Node* node_with_lowest_frequency = heap.top();
		heap.pop();

		Node* node_with_second_lowest_frequency = heap.top();
		heap.pop();

		heap.push(new Node(node_with_lowest_frequency, node_with_second_lowest_frequency));
	}
	
	Node* root = heap.top();

	return root;
}

auto find_letters_encodings(const Node* root, unordered_map<char, vector<bool>>& letters_encoding, vector<bool> encoding) -> void
{
	const bool node_is_leaf = root->character.has_value();

	if (node_is_leaf)
	{
		letters_encoding[root->character.value()] = encoding;
		return;
	}

	encoding.push_back(false);
	find_letters_encodings(root->left, letters_encoding, encoding);
	encoding.pop_back();

	encoding.push_back(true);
	find_letters_encodings(root->right, letters_encoding, encoding);
	encoding.pop_back();
}

auto Algorithm::Auxiliary::find_letters_encodings(const Node* root) -> unordered_map<char, vector<bool>>
{
	unordered_map<char, vector<bool>> letters_encodings;
	vector<bool> encoding;

	find_letters_encodings(root, letters_encodings, encoding);

	return letters_encodings;
}

auto Algorithm::Auxiliary::encode_to_bits(string_view original_text, const unordered_map<char, vector<bool>>& letters_encoding) -> vector<bool>
{
	vector<bool> encoded_bits;

	for (const char character : original_text)
	{
		encoded_bits.insert(encoded_bits.end(), letters_encoding.at(character).begin(), letters_encoding.at(character).end());
	}

	return encoded_bits;
}

auto Algorithm::Auxiliary::encode_bits_as_characters(const vector<bool>& encoded_bits) -> vector<char>
{
	vector<char> encoded_characters;
	const size_t bits_in_char = numeric_limits<char>::digits + 1;

	for (const auto chunk : encoded_bits | views::chunk(bits_in_char))
	{
		char next_character_in_code = 0;

		for (const bool bit : chunk)
		{
			next_character_in_code <<= 1;
			next_character_in_code |= bit;
		}

		if (chunk.size() < bits_in_char) [[unlikely]]
		{
			next_character_in_code <<= (bits_in_char - chunk.size());
		}

		encoded_characters.push_back(next_character_in_code);
	}

	return encoded_characters;
}
