CC = gcc
CFLAGS = -Wall
LDFLAGS = -lncurses
OBJFILES = main.o
TARGET = main

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -rf $(OBJFILES) ~*
