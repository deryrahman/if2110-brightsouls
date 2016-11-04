CC=gcc
INCLUDE_DIR=include
SOURCE_DIR=src
CFLAGS=-I$(INCLUDE_DIR) -Wall -g

bin/%.o: src/%.c include/*.h
	mkdir -p bin/graphics
	mkdir -p bin/menus
	$(CC) $(CFLAGS) -c -o $@ $<

build: bin/main.o bin/graphics/terminal.o bin/graphics/pixel.o bin/graphics/ui.o bin/xstring.o bin/graphics/image.o bin/menus/splashscreen.o
	$(CC) -o bin/brightsouls $^ $(CFLAGS)
