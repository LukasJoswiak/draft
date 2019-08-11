# This Makefile provides targets to build the unit tests for draft. It also
# provides a target to create simple tests from a file main.cpp. If you are
# using draft in your project, you will not need this Makefile. Instead,
# include the draft header and you should be set.

CC = g++
CFLAGS = -Wall -g -std=c++11 -I .

all: draft

draft:
	$(CC) $(CFLAGS) main.cpp

test: obj/test/main.o
	$(CC) $(CFLAGS) -c test/tests.cpp -o obj/test/tests.o
	$(CC) $< obj/test/tests.o -o bin/tests

obj/test/main.o: | obj bin
	$(CC) $(CFLAGS) -c test/main.cpp -o $@

obj bin:
	mkdir -p bin obj obj/test

clean:
	rm -rf bin obj

# Treat `test` and `clean` as keywords and not as files/directories.
# This allows commands such as `make test` to use the `test` target
# instead of treating `test` as a file target.
.PHONY: test clean
