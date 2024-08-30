#include "Node/Node.hpp"
#include "Algorithm.hpp"
#include <string>
#include <vector>

using namespace std;

namespace Algorithm::Auxiliary
{
	auto create_frequency_map(string_view text) -> frequency_map_t;
	auto create_tree(const frequency_map_t& frequency_map) -> Node*;
	auto find_letters_encodings(const Node* root) -> unordered_map<char, vector<bool>>;
	auto encode_text(string_view original_text, const unordered_map<char, vector<bool>>& letters_encoding) -> string;
	auto decode_text(string_view encoded_text, const Node* root) -> string;
}

auto Algorithm::encode(string_view original_text) -> pair<string, frequency_map_t>
{
	const frequency_map_t frequency_map = Auxiliary::create_frequency_map(original_text);
	const Node* root = Auxiliary::create_tree(frequency_map); // ! Use a std::unique_ptr.
	const unordered_map<char, vector<bool>> letters_encodings = Auxiliary::find_letters_encodings(root);
	const string encoded_text = Auxiliary::encode_text(original_text, letters_encodings);

	delete root;

	return {encoded_text, frequency_map};
}

auto Algorithm::decode(string_view encoded_text, const frequency_map_t& frequency_map) -> string
{
	const Node* root = Auxiliary::create_tree(frequency_map); // ! Use a std::unique_ptr.
	const string decoded_text = Auxiliary::decode_text(encoded_text, root);	

	delete root;

	return decoded_text;
}