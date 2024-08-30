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
		for (Node* child : {left, right})
		{
			const bool child_exists = child != nullptr;

			if (child_exists)
			{
				delete child;
				child = nullptr;
			}
		}
	}

	auto operator>(const Node& other) const -> bool { return frequency > other.frequency; }
};

#endif // NODE_HPP