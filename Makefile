# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -Iinclude

# Source files
SRC = src/fuzzer.c src/mutation.c src/linked_queue.c
TARGET = fuzz

# Default build
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Clean up
clean:
	rm -f $(TARGET)
