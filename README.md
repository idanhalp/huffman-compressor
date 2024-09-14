# Huffman Compressor
A compression tool that uses Huffman code.

## What does it do?
Encodes text files into smaller files and decodes them back to their original state.

Currently 3 modes are supported:
* Encoding a file.
* Decoding an encoded file.
* Running tests.

## How to run?
From the `Code` directory, compile using the `make` command, then run according to the desired mode:
* **Encoding:**
```
./Huffman.exe encode <file_to_encode> <file_to_encode_into>
```
* **Decoding:**
```
./Huffman.exe decode <file_to_decode> <file_to_decode_into>
```
* **Testing:**
```
./Huffman.exe test
```
