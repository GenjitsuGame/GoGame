/**
* @file main.cpp
* Projet GoGame
* @author LE Victor, LUTTGENS Pascal
* @version 1 - 08/03/2014
* @brief corps de la fonction main
*/

#include <iostream>

#include "gtp.h"
#include "go.h"

int main()
{
	GTP gtp;
	GTP::tester();
	gtp.list_command();
	while(1)
		gtp.commandes();
	return 0;
}
