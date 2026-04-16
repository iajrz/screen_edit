CFLAGS = -std=c11 -Wall -g -Wextra -Werror -pedantic-errors
LIBS = -lncurses
TARGET = screenedit
all: $(TARGET)

$(TARGET): main.c
	cc $(CFLAGS) main.c -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)