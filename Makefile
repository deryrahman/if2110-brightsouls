CC=gcc
INCLUDE_DIR=include
SOURCE_DIR=src
SOURCE=bin/xstring.o \
	bin/skill.o \
	bin/stackt.o \
	bin/queue.o \
	bin/player.o \
	bin/tree.o \
	bin/gamestate.o \
	bin/listinteger.o \
	bin/liststring.o \
	bin/graphics/terminal.o \
	bin/graphics/pixel.o \
	bin/graphics/ui.o \
	bin/graphics/image.o \
	bin/menus/splashscreen.o \
	bin/menus/mainmenu.o \
	bin/menus/newgame.o \
	bin/menus/menu_battle.o \
	bin/menus/menu_skill.o \
	bin/menus/mapmenu.o \
	bin/menus/endgame.o \
	bin/map.o \
	bin/point.o \
	bin/main.o
CFLAGS=-I$(INCLUDE_DIR) -Wall -g -lm -std=c99

bin/%.o: src/%.c include/*.h
	mkdir -p bin/graphics
	mkdir -p bin/menus
	$(CC) $(CFLAGS) -c -o $@ $<

testbin/%.o: tests/%.c include/*.h
	mkdir -p testbin
	$(CC) $(CFLAGS) -c -o $@ $<

build: $(SOURCE)
	$(CC) -o bin/brightsouls $^ $(CFLAGS)

built_test: bin/xstring.o bin/graphics/terminal.o bin/graphics/pixel.o bin/graphics/ui.o bin/graphics/image.o bin/menus/splashscreen.o bin/menus/mainmenu.o bin/menus/newgame.o bin/map.o bin/point.o testbin/map_test.o
	$(CC) -o testbin/map_test $^ $(CFLAGS)
