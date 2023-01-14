CC = gcc
CFLAGS = -Wall
LDFLAGS = -lcurses
OBJFILES = main.o
TARGET = main

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) *~