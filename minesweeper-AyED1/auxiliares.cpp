#include <iostream>
#include <unordered_set>

#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"

using namespace std;

int minaEnPosicion(tablero t, pos p){ //  O(1)
    int res = 0;
    if(enRango(t,p)){
        if(t[p.first][p.second] == true){
            res = 1;
        }
    }
    return res;
}


int indice(banderitas b,pos x){ //  O(|b|)
    int res;
    for (int i = 0; i < b.size() ; ++i) {
        if (b[i] == x){
            res =i;
        }
    }
    return res;
}

bool enRango(tablero t, pos p){ //  O(1)
    bool res = false;
    if (p.first >= 0 && p.first < t.size() && p.second >= 0 && p.second < t.size()){
        res = true;
    }
    return res;
}

bool contieneJugada(jugadas j,tablero t,pos p) { //  O(|j|)
    bool res = false;
    if (enRango(t,p)) {
        for (int l = 0; l < j.size(); ++l) {
            if (p.first == j[l].first.first && p.second == j[l].first.second && t[p.first][p.second] == 0) {
                res = true;
            }
        }
    }
    return res;
}

bool contieneBanderita(banderitas b,pos p,tablero& t){ //  O(|b|)
    bool res=false;
    if(enRango(t,p)){
        for (int m = 0; m < b.size(); ++m) {
            if (b[m].first == p.first && b[m].second == p.second) {
                res = true;
            }
        }
    }
    return res;
}

bool es121Horizontal(tablero& t, jugadas& j, int i){ //  O(|j|)
    bool res = false;
    if (j[i].second == 2 && 
        (minasAdyacentes(t, {j[i].first.first, j[i].first.second - 1}) == 1 &&
         contieneJugada(j, t, {j[i].first.first, j[i].first.second - 1}) && //recorre longitud de jugada veces(Como maximo todas las minas libres)
         minasAdyacentes(t, {j[i].first.first, j[i].first.second + 1}) == 1 &&
         contieneJugada(j, t, {j[i].first.first, j[i].first.second + 1}))){
        res = true;
    }
    return res;
}

bool es121Vertical(tablero& t, jugadas& j, int i){ //  O(|j|)
    bool res = false;
    if (j[i].second == 2 && 
        (minasAdyacentes(t, {j[i].first.first - 1, j[i].first.second}) == 1 &&
         contieneJugada(j, t, {j[i].first.first - 1, j[i].first.second}) &&
         minasAdyacentes(t, {j[i].first.first + 1, j[i].first.second}) == 1 &&
         contieneJugada(j, t, {j[i].first.first + 1, j[i].first.second}))){
        res = true;
    }
    return res;
}