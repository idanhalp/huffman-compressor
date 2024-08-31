#include "Algorithm.hpp"
#include "Node/Node.hpp"
#include <limits>
#include <memory>
#include <queue>
#include <ranges>
#include <span>
#include <string>
#include <vector>

using namespace std;

namespace Algorithm::Auxiliary
{
	auto create_frequency_map(string_view text) -> frequency_map_t;
	auto create_tree(const frequency_map_t& frequency_map) -> Node*;
	auto find_letters_encodings(const frequency_map_t& frequency_map) -> unordered_map<char, vector<bool>>;
	auto encode_to_bits(string_view original_text, const unordered_map<char, vector<bool>>& letters_encoding) -> vector<bool>;
	auto encode_bits_as_characters(const vector<bool>& encoded_bits) -> vector<char>;
	auto decode_bits_from_characters(span<const char> encoded_characters, size_t total_bits) -> vector<bool>;
	auto decode_text_from_bits(const vector<bool>& encoded_bits, const Node* root) -> string;
}

auto Algorithm::encode(string_view original_text) -> EncodingInfo
{
	const frequency_map_t frequency_map = Auxiliary::create_frequency_map(original_text);
	const unordered_map<char, vector<bool>> letters_encodings = Auxiliary::find_letters_encodings(frequency_map);
	const vector<bool> encoded_bits = Auxiliary::encode_to_bits(original_text, letters_encodings);	
	const vector<char> encoded_characters = Auxiliary::encode_bits_as_characters(encoded_bits);

	return {encoded_characters, frequency_map, encoded_bits.size()};
}

auto Algorithm::decode(const EncodingInfo& encoding_info) -> string
{
	const vector<bool> encoded_bits = Auxiliary::decode_bits_from_characters(encoding_info.encoded_characters, encoding_info.total_bits);
	const unique_ptr<Node> root(Auxiliary::create_tree(encoding_info.frequency_map));
	const string original_text = Auxiliary::decode_text_from_bits(encoded_bits, root.get());

	return original_text;
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

auto Algorithm::Auxiliary::find_letters_encodings(const frequency_map_t& frequency_map) -> unordered_map<char, vector<bool>>
{
	unordered_map<char, vector<bool>> letters_encodings;
	vector<bool> encoding;
	unique_ptr<Node> root(create_tree(frequency_map));

	find_letters_encodings(root.get(), letters_encodings, encoding);

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

auto Algorithm::Auxiliary::decode_bits_from_characters(span<const char> encoded_characters, size_t total_bits) -> vector<bool>
{
	vector<bool> encoded_bits;

	const size_t bits_in_char = numeric_limits<char>::digits + 1;
	encoded_bits.reserve(bits_in_char * encoded_characters.size());

	for (const char character : encoded_characters)
	{
		const size_t msb_position = numeric_limits<char>::digits;

		for (size_t bit_index = msb_position; bit_index != SIZE_MAX; --bit_index)
		{
			const bool bit_is_set = (character & (1 << bit_index));
			encoded_bits.push_back(bit_is_set);
		}
	}

	encoded_bits.resize(total_bits);

	return encoded_bits;
}

auto Algorithm::Auxiliary::decode_text_from_bits(const vector<bool>& encoded_bits, const Node* root) -> string
{
	string result;

	for (const Node* current = root; const bool bit : encoded_bits)
	{
		if (bit)
		{
			current = current->right;
		}
		else
		{
			current = current->left;
		}

		if (current->is_leaf())
		{
			result += current->character.value();
			current = root;
		}
	}

	return result;
}
