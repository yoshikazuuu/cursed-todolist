CC = gcc
CFLAGS = -std=c11 -Wall
LFLAGS = -lncurses
TARGET = tdl
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	echo Linking...
	$(CC) $(LFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	echo Building...
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)
