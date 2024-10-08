COMPILER = g++ 

COMPILER_FLAGS = -Wall -Wextra -pedantic -Werror -O3 -std=c++23

SOURCE_FILES = \
		Main.cpp\
		Source/Algorithm/Algorithm.cpp\
		Source/Algorithm/Debug/Debug.cpp\
		Source/FileProcessing/FileProcessing.cpp\
		Tests/FixedTests/FixedTests.cpp\
		Tests/RandomTests/RandomTests.cpp\
		Tests/Tests.cpp

OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

# Output executable
TARGET = Huffman.exe

# Build rule
all: $(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $^

# Compilation rule for object files
%.o: %.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c -o $@ $<

VALGRIND = valgrind

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

valgrind: $(TARGET)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(TARGET)

clean:
	rm -f $(OBJECT_FILES) $(TARGET)

.PHONY: all clean valgrind