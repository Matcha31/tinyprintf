CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla
LDFLAGS=-fsanitize=address
LDLIBS=-lcriterion

all: src/tinyprintf.o

src/tinyprintf.o: src/tinyprintf.c
	$(CC) $(CFLAGS) -c -o src/tinyprintf.o src/tinyprintf.c

tests/test.o: tests/test.c
	$(CC) $(CFLAGS) -c -o tests/test.o tests/test.c

check: src/tinyprintf.o tests/test.o
	$(CC) -o test_suite tests/test.o src/tinyprintf.o $(LDFLAGS) $(LDLIBS)
	./test_suite

clean:
	rm -f src/tinyprintf.o
	rm -f tests/test.o
	rm -f test_suite
