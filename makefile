CC = gcc
CFLAGS = -Wall -D_DARWIN_C_SOURCE -DNCURSES_WIDECHAR -I/opt/homebrew/Cellar/ncurses/6.4/include/ncursesw -I/opt/homebrew/Cellar/ncurses/6.4/include
LDFLAGS = -lncursesw -L/opt/homebrew/Cellar/ncurses/6.4/lib -Wl 
OBJFILES = main.o
TARGET = main

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -rf $(OBJFILES) ~*
