#include <iostream>

#include "gtp.h"

int main() {
    GTP gtp;
    gtp.list_command();
    while (1)
        gtp.commandes();
}
