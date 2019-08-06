all: draft

draft:
	g++ -std=c++11 -I . main.cpp

test: obj/test/main.o
	g++ -std=c++17 -I . -c test/tests.cpp -o obj/test/tests.o
	g++ obj/test/main.o obj/test/tests.o -o bin/tests

obj/test/main.o:
	# TODO: Move `mkdir` command to separate rule
	mkdir -p bin obj obj/test
	g++ -std=c++17 -I . -c test/main.cpp -o $@

clean:
	rm -rf bin obj

# Treat `test` and `clean` as keywords and not as files/directories.
# This allows commands such as `make test` to use the `test` target
# instead of treating `test` as a file target.
.PHONY: test clean
