CC = gcc

CFLAGS = -Wall -Wextra -pedantic -ansi -g
LDFLAGS = $(CFLAGS) -lm

BUILD_DIR = build
BIN = spirals.exe

all: clean $(BUILD_DIR) $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN): $(BUILD_DIR)/spirals.o $(BUILD_DIR)/matrix.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/spirals.o: src/spirals.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/matrix.o: src/matrix/matrix.c src/matrix/matrix.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR):
	mkdir $@

# on Windows use del /F /Q $(BUILD_DIR)
clean:
	rm -rf $(BUILD_DIR)
