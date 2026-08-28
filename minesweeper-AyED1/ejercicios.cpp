#include <stdio.h>
#include <iostream>

#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"

using namespace std;

/******++++**************************** minasAdyacentes ***********+++***********************/

int minasAdyacentes(tablero& t, pos p) { // O(1)
    int sumaMinas = 0;
    int minaCentral = minaEnPosicion(t,p);
    for (int i = p.first-1; i <= p.first+1 ; ++i) {
        for (int j = p.second-1; j <=p.second+1 ; ++j) { // recorre todos los casilleros adyacentes y el central, suma el total de minas
            pos pCiclo;
            pCiclo.first = i;
            pCiclo.second = j;
            sumaMinas += minaEnPosicion(t,pCiclo);
        }
    }
    return sumaMinas-minaCentral; // en caso de que hubiera una mina en la pos central, la resta.

}

/******++++**************************** plantarBanderita ***********+++***********************/

void cambiarBanderita(tablero& t, jugadas& j, pos p, banderitas& b) { // O(|b|)
    if (contieneBanderita(b,p,t)){
        b.erase(b.begin()+ indice(b,p));
    }
    else if (!contieneJugada(j,t,p)){
        b.push_back(p);
    }
}

/******++++**************************** perdio ***********+++***********************/

bool perdio(tablero& t, jugadas& j) { // O(|j|)
    bool res = false;
    int i = 0;
    while(i<j.size() && !res) {
        int row = j[i].first.first;
        int col = j[i].first.second;
        if(t[row][col] == true){
            res = true;
        }
        ++i;
    }
    return res;
}

/******++++**************************** gano ***********+++***********************/

// asumimos que no hay hechas jugadas repetidas. 

bool gano(tablero& t, jugadas& j) { // O(|t|^2) 
    bool res = false;
    int cantidadSinMinas=0;
    for (int i = 0; i < t.size(); ++i) {
        for (int h = 0; h < t[0].size(); ++h) { // contamos la cantidad de casillas sin minas en el tablero
            if (t[i][h] == false){
                cantidadSinMinas+=1;
            }
        }
    }
    if (j.size() == cantidadSinMinas && !perdio(t,j)) { // si la cantidad de casillas sin minas coincide con las de jugadas, gano.
        res = true;
    }
    return res;
}

/******++++**************************** jugarPlus ***********+++***********************/

 void jugarPlus(tablero& t, banderitas& b, pos p, jugadas& j) { // O((|j| + |b|)*|t|^2))
    if ( t[p.first][p.second]== 1 ){ // si hay una mina la agrega a jugadas y al pisar una mina termina el juego. O(1)
        j.push_back({{p.first,p.second}, minasAdyacentes(t,{p.first,p.second})});
    }
    else if(minasAdyacentes(t,p)>0 && t[p.first][p.second]==0 && !contieneBanderita(b,p,t)){ // O(|b|)
        j.push_back({{p.first,p.second}, minasAdyacentes(t,{p.first,p.second})}); // agrega la posicion a jugadas.
    }
    else{
        if (!contieneJugada(j,t,{p.first,p.second}) && !contieneBanderita(b,p,t) ){ // O(|j|+|b|)
            j.push_back({{p.first,p.second}, minasAdyacentes(t,{p.first,p.second})}); // agrega la posicion a jugadas.
        }
        for (int i = p.first -1; i <= p.first +1 ; ++i) {
            for (int k = p.second-1; k <= p.second +1 ; ++k) { // recorre 3*3
                if (enRango(t,{i,k}) && (i!= p.first || k!= p.second) && !contieneBanderita(b,p,t)){ // O(|b|) no se sale de rango, no considera la posicion central, ya que fue agregada antes.
                    if (t[i][k] == 0 && !contieneJugada(j, t, {i, k}) && !contieneBanderita(b,{i,k},t)) { // O(|j| + |b|)
                        j.push_back({{i, k}, minasAdyacentes(t, {i, k})}); // agrega la posicion a jugadas.
                        if(minasAdyacentes(t, {i, k})==0) {
                            jugarPlus(t, b, {i, k}, j); // recursion sobre la funcion en el caso de que no haya minas adyacentes.
                        }
                    }
                }
            }
        }
    }
}

/******++++**************************** sugerirAutomatico121 ***********+++***********************/

bool sugerirAutomatico121(tablero& t, banderitas& b, jugadas& j, pos& p) { // O(|j|^2 + |j| * |b|)
    bool res = false;
    for (int i = 0; i < j.size(); ++i) {
        if (es121Horizontal(t,j,i)) { //recorre longitud de 2 jugada veces en es121Horizontal, las vuelve a recorrer 2 veces mas si se cumple la condicion para chequear los proximos if.
            if (enRango(t,{j[i].first.first - 1, j[i].first.second})&&!(contieneJugada(j, t, {j[i].first.first - 1, j[i].first.second}))&&!(contieneBanderita(b,{j[i].first.first - 1, j[i].first.second},t))) { // por cada iteracion del for volvemos a recorrer toda la secuencia de jugadas.
                p = {j[i].first.first - 1, j[i].first.second};
                res = true;
            }
            if (enRango(t,{j[i].first.first + 1, j[i].first.second})&&!(contieneJugada(j, t, {j[i].first.first + 1, j[i].first.second}))&&!(contieneBanderita(b,{j[i].first.first + 1, j[i].first.second},t))) {
                p = {j[i].first.first + 1, j[i].first.second};
                res = true;
            }
        }

        if (es121Vertical(t,j,i)){ //recorre longitud de 2 jugada veces en es121Vertical, las vuelve a recorrer 2 veces mas si se cumple la condicion para chequear los proximos if.
            if (enRango(t,{j[i].first.first, j[i].first.second - 1})&&!(contieneJugada(j, t, {j[i].first.first, j[i].first.second - 1}))&&!(contieneBanderita(b,{j[i].first.first , j[i].first.second - 1},t))) {
                p = {j[i].first.first, j[i].first.second - 1};
                res= true;
            }
            if (enRango(t,{j[i].first.first, j[i].first.second + 1})&&!(contieneJugada(j, t, {j[i].first.first, j[i].first.second + 1}))&&!(contieneBanderita(b,{j[i].first.first , j[i].first.second + 1},t))) {
                p = {j[i].first.first, j[i].first.second + 1};
                res = true;
            }
        }
    }
    return res;
}