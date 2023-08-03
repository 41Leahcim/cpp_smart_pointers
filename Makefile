default: valgrind

build:
	mkdir build

build/app: $(wildcard *.cpp *.hpp) build
	g++ *.cpp -Os -Wall -Wextra -o build/app

run: build/app
	./app

valgrind: build/app
	valgrind ./build/app
