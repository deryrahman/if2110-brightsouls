CC=gcc
INCLUDE_DIR=include
SOURCE_DIR=src
CFLAGS=-I$(INCLUDE_DIR) -Wall -g

bin/%.o: src/%.c include/*.h
	mkdir -p bin/graphics
	$(CC) $(CFLAGS) -c -o $@ $<

build: bin/main.o bin/graphics/terminal.o bin/graphics/pixel.o bin/graphics/ui.o
	$(CC) -o bin/brightsouls $^ $(CFLAGS)
