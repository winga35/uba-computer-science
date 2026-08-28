#pragma once 

#include "definiciones.h"

int minasAdyacentes(tablero& t, pos p);
void cambiarBanderita(tablero& t, jugadas& j, pos p, banderitas& b);
bool perdio(tablero& t, jugadas& j);
bool gano(tablero& t, jugadas& j);
void jugarPlus(tablero& t, banderitas& b, pos p, jugadas& j);
bool sugerirAutomatico121(tablero& t, banderitas& b, jugadas& j, pos& p);
