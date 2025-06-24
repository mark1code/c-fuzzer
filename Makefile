# Compiler 
CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -Iinclude

# Source files
SRC = src/fuzzer.c src/mutation.c src/linked_queue.c
TARGET = fuzz

# Test files
TEST_SRC = test/test.c
TEST_TARGET = test_fuzz
TEST_FILES = src/mutation.c src/linked_queue.c Unity/src/unity.c
TEST_INCLUDES = -Iinclude -IUnity/src

# Build
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Test
test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(TEST_FILES)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -o $@ $^
	./$(TEST_TARGET) 

clean:
	rm -f $(TARGET) $(TEST_TARGET)
