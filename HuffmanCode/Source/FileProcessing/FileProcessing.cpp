#include "FileProcessing.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace Processing::Auxiliary
{
	auto write_frequency_map_to_output_file(ofstream& output_stream, const Algorithm::frequency_map_t& frequency_map) -> void;
	auto write_characters_to_output_file(ofstream& output_stream, const vector<char> characters) -> void;
}

auto Processing::encode_into_file(std::string output_file_path, const Algorithm::EncodingInfo& encoding_info) -> void
{
	ofstream output_stream(output_file_path);

	if (!output_stream.is_open())
	{
		throw runtime_error("Cannot write to " + output_file_path + "!\n");
	}

	output_stream << encoding_info.total_bits << '\n';
	Auxiliary::write_frequency_map_to_output_file(output_stream, encoding_info.frequency_map);
	Auxiliary::write_characters_to_output_file(output_stream, encoding_info.encoded_characters);
}

auto Processing::decode_from_file(string input_file_path) -> Algorithm::EncodingInfo
{
	ifstream input_stream(input_file_path);

	if (!input_stream.is_open())
	{
		throw runtime_error("Cannot open " + input_file_path + "!\n");
	}

	Algorithm::EncodingInfo encoding_info;
	string s;

	getline(input_stream, s);
	encoding_info.total_bits = stoi(s);

	getline(input_stream, s);
	const int frequency_map_length = stoi(s);

	for (int i = 0; i < frequency_map_length; ++i)
	{
		char character;
		int frequency;

		input_stream.get(character); // Use get because character can be a whitespace.
		input_stream >> frequency;

		encoding_info.frequency_map[character] = frequency;
		
		input_stream.get(character); // Read the newline.
	}

	getline(input_stream, s);
	const int num_of_characters = stoi(s);

	for (int i = 0; i < num_of_characters; ++i)
	{
		char character;
		input_stream.get(character);
		encoding_info.encoded_characters.push_back(character);
	}

	return encoding_info;
}

auto Processing::write_into_file(string output_file_path, string_view content) -> void
{
	ofstream output_stream(output_file_path);

	if (!output_stream.is_open())
	{
		throw runtime_error("Cannot write to " + output_file_path + "!\n");
	}

	output_stream << content;
}

auto Processing::read_from_file(string input_file_path) -> string
{
	ifstream input_stream(input_file_path);

	if (!input_stream.is_open())
	{
		throw runtime_error("Cannot open " + input_file_path + "!\n");
	}
	
	stringstream string_buffer;
	string_buffer << input_stream.rdbuf();

	return string_buffer.str();
}

auto Processing::Auxiliary::write_frequency_map_to_output_file(ofstream& output_stream, const Algorithm::frequency_map_t& frequency_map) -> void
{
	output_stream << frequency_map.size() << '\n';
	
	for (const auto [character, frequency] : frequency_map)
	{
		output_stream << character << ' ' << frequency << '\n';
	}
}

auto Processing::Auxiliary::write_characters_to_output_file(ofstream& output_stream, const vector<char> characters) -> void
{
	output_stream << characters.size() << '\n';

	for (const char character : characters)
	{
		output_stream << character;
	}
}
