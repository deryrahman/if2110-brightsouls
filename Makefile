CC=gcc
INCLUDE_DIR=include
SOURCE_DIR=src
CFLAGS=-I$(INCLUDE_DIR) -Wall -g -lm -std=c99
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
	bin/point.o
TEST=map_test string_test skilltree_test player_test gamestate_test

all: build

bin/%.o: src/%.c include/*.h
	mkdir -p bin/graphics
	mkdir -p bin/menus
	$(CC) $(CFLAGS) -c -o $@ $<

testbin/%.o: tests/%.c include/*.h
	mkdir -p testbin
	$(CC) $(CFLAGS) -c -o $@ $<

build: $(SOURCE) bin/main.o
	$(CC) -o bin/brightsouls $^ $(CFLAGS)

build_test: $(SOURCE)
	mkdir -p testbin
	$(foreach fn,$(TEST), $(CC) -o testbin/$(fn).o -c tests/$(fn).c $(CFLAGS);)
	$(foreach fn,$(TEST), $(CC) $^ testbin/$(fn).o -o testbin/$(fn) $(CFLAGS);)
