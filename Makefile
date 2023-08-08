default: valgrind

build:
	mkdir build

build/app: $(wildcard *.cpp *.hpp) build
	g++ *.cpp -O7 -Wall -Wextra -o build/app

run: build/app
	./build/app performance

valgrind: build/app
	valgrind ./build/app memory

