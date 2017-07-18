#include <iostream>

#include "GameManager.h"

int main() {
    GameManager gtp;
    gtp.listCmds();
    while (1)
        gtp.cmds();
}
