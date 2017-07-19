#include <iostream>

#include "GameManager.h"

int main() {
    GameManager gtp;
    gtp.listCommands();
    while (1)
        gtp.cmds();
}
