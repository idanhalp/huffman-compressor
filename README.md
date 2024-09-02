# Coding Challenges
My solutions for challenges from https://codingchallenges.fyi.

## [Huffman Code](https://github.com/idanhalp/coding-challenges-fyi/tree/master/HuffmanCode)
Solution for [this](https://codingchallenges.fyi/challenges/challenge-huffman) challenge.

### What does it do?
Encodes files into smaller files and decodes them back to their original state.
Currently supports 3 modes:
* Encoding a file.
* Decoding an encoded file.
* Running tests.

### How to run it?
Compile using the `make` command, then run according to the desired mode:
* **Encoding:** `./Huffman.exe encode <file_to_encode> <file_to_encode_into>`
* **Decoding:** `./Huffman.exe decode <file_to_decode> <file_to_decode_into>`
* **Testing:** `./Huffman.exe test`
