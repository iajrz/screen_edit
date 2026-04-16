CFLAGS = -Wall -g
LIBS = -lncurses
TARGET = screenedit
all: $(TARGET)

$(TARGET): main.c
	gcc $(CFLAGS) main.c -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)