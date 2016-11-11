#include "map.h"
#include "graphics/terminal.h"

int main(int argc, char** argv) {
    Terminal terminal = TerminalCreateDefault();

    Map map = MapCreateEmpty();

    FILE *file_map1 = fopen("res/map1.map","r");
    if (file_map1)
        MapFillFromFile(&map, file_map1);

    MapPutOnTerminal(map, terminal, TerminalGetCenterX(terminal, MapWidth(map)), 10);

    TerminalRender(terminal);

    return 0;
}
