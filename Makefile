SHELL := /bin/bash
RM    := rm -rf
MKDIR := mkdir -p

.PHONY: all clean build test format codeblocks

all: build test

clean:
	rm -rf build

format:
	sh script/format.sh

build/Makefile:
	mkdir build
	cd build && cmake ..

build: build/Makefile
	cd build && cmake --build .

test: build
	cd build && cmake --build . --target test

codeblocks:
	$(MKDIR) codeblocks
	cd codeblocks && cmake -DCMAKE_BUILD_TYPE=Debug -G 'CodeBlocks - Unix Makefiles' ..
