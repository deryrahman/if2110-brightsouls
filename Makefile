CC=gcc
INCLUDE_DIR=include
SOURCE_DIR=src
CFLAGS=-I$(INCLUDE_DIR) -Wall -g

bin/%.o: src/%.c include/*.h
	mkdir -p bin/graphics
	mkdir -p bin/menus
	$(CC) $(CFLAGS) -c -o $@ $<

testbin/%.o: tests/%.c include/*.h
	mkdir -p testbinbin
	$(CC) $(CFLAGS) -c -o $@ $<

built_test: bin/xstring.o bin/graphics/terminal.o bin/graphics/pixel.o bin/graphics/ui.o bin/graphics/image.o bin/menus/splashscreen.o bin/menus/mainmenu.o bin/map.o bin/point.o testbin/map_test.o
	$(CC) -o testbin/map_test $^ $(CFLAGS)

build: bin/xstring.o bin/graphics/terminal.o bin/graphics/pixel.o bin/graphics/ui.o bin/graphics/image.o bin/menus/splashscreen.o bin/menus/mainmenu.o bin/map.o bin/point.o bin/main.o
	$(CC) -o bin/brightsouls $^ $(CFLAGS)
