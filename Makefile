CC=gcc
CFLAGS=-Wall -Wextra -std=c11
LIBS=-lncurses

# Targets
all: game_of_life


# Compilation rule

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)


# Static analysis using cppcheck
cppcheck:
	cppcheck --enable=all --inconclusive .


# Code formatting  using clang-format
format:
	clang-format -i *.c*


# Clean compiled files
clean:
	rm -f game_of_life