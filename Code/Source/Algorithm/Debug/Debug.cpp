#include "Debug.hpp"
#include <iostream>
#include <print>
#include <vector>

using namespace std;

auto Debug::print_frequency_map(const Algorithm::frequency_map_t& frequency_map) -> void
{
	for (const auto [character, frequency] : frequency_map)
	{
		println("{0} (ASCII == {1}): {2}", character, static_cast<int>(character), frequency);
	}
}

auto Debug::print_tree(const Node* root) -> void
{
	const auto print_node = [] (const Node* node)
	{
		if (node->is_leaf())
		{
			print("({0}, {1}) ", node->frequency, node->character.value());
		}
		else
		{
			print("({0})", node->frequency);
		}
	};

	vector<const Node*> current_level = {root};

	for (int level = 0; !current_level.empty(); ++level)
	{
		print("Level {}: ", level);

		vector<const Node*> next_level;

		for (const Node* node : current_level)
		{
			print_node(node);

			if (!node->is_leaf())
			{
				next_level.push_back(node->left);
				next_level.push_back(node->right);
			}			
		}

		current_level = move(next_level);

		cout << '\n';
	}
}

// The following functions could use `std::print`.
// However until printing formatted ranges is supported, I will stick to `std::cout`.

auto Debug::print_letters_encodings(const unordered_map<char, vector<bool>>& letters_encodings) -> void
{
	for (const auto& [character, encoding] : letters_encodings)
	{
		cout << character << ": ";
		print_encoded_bits(letters_encodings.at(character));
	}
}

auto Debug::print_encoded_bits(const std::vector<bool>& encoded_bits) -> void
{
	for (const auto bit : encoded_bits)
	{
		cout << bit;
	}

	cout << '\n';
}

auto Debug::print_encoded_characters(span<const char> encoded_characters) -> void
{
	for (const char character : encoded_characters)
	{
		cout << static_cast<int>(character) << ' ';
	}

	cout << '\n';
}
