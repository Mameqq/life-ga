CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lncurses
TARGET = game_of_life
SRCS = game_of_life.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean