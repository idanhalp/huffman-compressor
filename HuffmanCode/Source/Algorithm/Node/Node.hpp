#ifndef NODE_HPP
#define NODE_HPP

#include <optional>

struct Node
{
	Node* left;
	Node* right;
	int frequency;
	std::optional<char> character; // Only leaf nodes represent a character.

	Node(const int frequency, const char character) : frequency(frequency), character(character) 
	{
	}

	Node(Node* left, Node* right) : left(left), right(right), frequency(left->frequency + right->frequency), character(std::nullopt)
	{
	}

	~Node()
	{
		if (is_leaf())
		{
			return;
		}
		
		for (Node* child : {left, right})
		{
			delete child;
			child = nullptr;
		}
	}

	auto operator>(const Node& other) const -> bool { return frequency > other.frequency; }

	auto is_leaf() const -> bool { return character.has_value(); }
};

#endif // NODE_HPP