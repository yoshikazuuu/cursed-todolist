CC = gcc
CFLAGS = -std=c11 -Wall
LFLAGS = -lncurses
TARGET = tdl
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

$(TARGET): $(OBJ_FILES)
	echo Linking...
	$(CC) $(LFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(shell mkdir $(BUILD_DIR))
	echo Building...
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean

