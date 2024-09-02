#include "FileProcessing.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace Processing::Auxiliary
{
	auto write_total_bits_to_output_file(ofstream& output_stream, size_t total_bits) -> void;
	auto write_frequency_map_to_output_file(ofstream& output_stream, const Algorithm::frequency_map_t& frequency_map) -> void;
	auto write_characters_to_output_file(ofstream& output_stream, const vector<char> characters) -> void;
	auto read_total_bits_from_input_file(ifstream& input_stream) -> size_t;
	auto read_frequency_map_from_input_file(ifstream& input_stream) -> Algorithm::frequency_map_t;
	auto read_characters_from_input_file(ifstream& input_stream) -> vector<char>;
}

auto Processing::encode_into_file(std::string output_file_path, const Algorithm::EncodingInfo& encoding_info) -> void
{
	ofstream output_stream(output_file_path);

	if (!output_stream.is_open())
	{
		throw runtime_error("Cannot write to " + output_file_path + "!\n");
	}

	Auxiliary::write_total_bits_to_output_file(output_stream, encoding_info.total_bits);
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
	encoding_info.total_bits = Auxiliary::read_total_bits_from_input_file(input_stream);
	encoding_info.frequency_map = Auxiliary::read_frequency_map_from_input_file(input_stream);
	encoding_info.encoded_characters = Auxiliary::read_characters_from_input_file(input_stream);

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

auto Processing::Auxiliary::write_total_bits_to_output_file(ofstream& output_stream, const size_t total_bits) -> void
{
	output_stream << total_bits << '\n';
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

auto Processing::Auxiliary::read_total_bits_from_input_file(ifstream& input_stream) -> size_t
{
	string s;
	getline(input_stream, s);

	return stoi(s);
}

auto Processing::Auxiliary::read_frequency_map_from_input_file(ifstream& input_stream) -> Algorithm::frequency_map_t
{
	const int frequency_map_length = [&] { string s; getline(input_stream, s); return stoi(s); }();
	Algorithm::frequency_map_t frequency_map;

	for (int i = 0; i < frequency_map_length; ++i)
	{
		char character;
		int frequency;

		input_stream.get(character); // Use get because character can be a whitespace.
		input_stream >> frequency;

		frequency_map[character] = frequency;
		
		input_stream.get(character); // Read the newline.
	}

	return frequency_map;
}

auto Processing::Auxiliary::read_characters_from_input_file(ifstream& input_stream) -> vector<char>
{
	const int num_of_characters = [&] { string s; getline(input_stream, s); return stoi(s); }();
	vector<char> encoded_characters;

	for (int i = 0; i < num_of_characters; ++i)
	{
		char character;
		input_stream.get(character);
		encoded_characters.push_back(character);
	}

	return encoded_characters;
}
